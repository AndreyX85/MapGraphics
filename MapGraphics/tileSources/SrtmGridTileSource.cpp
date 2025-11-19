#include "SrtmGridTileSource.h"

#include <QImage>
#include <QPainter>
#include <QFileInfo>
#include <QFile>
#include <QDataStream>
#include <QtDebug>
#include <QtMath>
#include <QtGlobal>

SrtmGridTileSource::SrtmGridTileSource(const QStringList& rootDirs,
                                       QObject *parent) :
    GridTileSource()          // У GridTileSource НЕТ конструктора с parent
{
    Q_UNUSED(parent);         // parent пока не используем

    // Собираем список всех SRTM/DTED-плиток
    buildIndex(rootDirs);
}

QString SrtmGridTileSource::name() const
{
    return QStringLiteral("SRTM grid overlay");
}

void SrtmGridTileSource::buildIndex(const QStringList& rootDirs)
{
    QMutexLocker locker(&m_mutex);

    m_cells.clear();

    for (const QString &root : rootDirs)
    {
        QDir dir(root);
        if (!dir.exists())
        {
            qWarning() << "[SRTM] Каталог не существует:" << root;
            continue;
        }

        scanDir(dir);
    }

    qDebug() << "[SRTM] Найдено плиток:" << m_cells.size();
}

void SrtmGridTileSource::scanDir(const QDir& dir)
{
    QFileInfoList entries =
        dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &fi : entries)
    {
        if (fi.isDir())
        {
            scanDir(QDir(fi.absoluteFilePath()));
            continue;
        }

        const QString fileName = fi.fileName().toLower();

        // Простейший фильтр по расширению
        if (fileName.endsWith(".hgt")  ||
            fileName.endsWith(".tif")  ||
            fileName.endsWith(".tiff") ||
            fileName.endsWith(".dt0")  ||
            fileName.endsWith(".dt1"))
        {
            double minLat, maxLat, minLon, maxLon;
            if (parseSrtmName(fileName, minLat, maxLat, minLon, maxLon))
            {
                SrtmCell cell;
                cell.minLat   = minLat;
                cell.maxLat   = maxLat;
                cell.minLon   = minLon;
                cell.maxLon   = maxLon;
                cell.filePath = fi.absoluteFilePath();
                m_cells.push_back(cell);
            }
            else
            {
                // GeoTIFF’ы/DT0/DT1 с произвольным именем пока пропускаем
                qWarning() << "[SRTM] Не удалось распознать имя файла по шаблону NxxEyyy:" << fi.absoluteFilePath();
            }
        }
    }
}


// Разбор имени SRTM-файла (N55E037.hgt -> bbox 1x1 градус)
bool SrtmGridTileSource::parseSrtmName(const QString& fileName,
                                       double& minLat, double& maxLat,
                                       double& minLon, double& maxLon) const
{
    // только классический формат: N55E037.hgt, S10W123.hgt и т.п.
    if (fileName.length() < 7)
        return false;

    // Первый символ - N или S (север/юг)
    const QChar ns = fileName.at(0).toUpper();
    if (ns != 'N' && ns != 'S')
        return false;

    // Ищем 'E' или 'W' (восток/запад)
    int posLonLetter = fileName.indexOf('E', 1, Qt::CaseInsensitive);
    if (posLonLetter < 0)
        posLonLetter = fileName.indexOf('W', 1, Qt::CaseInsensitive);
    if (posLonLetter < 0)
        return false;

    // Широта – всё между [1; posLonLetter)
    const QString latStr = fileName.mid(1, posLonLetter - 1);
    bool okLat = false;
    int latDeg = latStr.toInt(&okLat);
    if (!okLat)
        return false;

    // Долгота – 3 цифры после буквы E/W
    const QString lonStr = fileName.mid(posLonLetter + 1, 3);
    bool okLon = false;
    int lonDeg = lonStr.toInt(&okLon);
    if (!okLon)
        return false;

    double lat = static_cast<double>(latDeg);
    double lon = static_cast<double>(lonDeg);

    if (ns == 'S')
        lat = -lat;

    const QChar ew = fileName.at(posLonLetter).toUpper();
    if (ew == 'W')
        lon = -lon;

    // SRTM-тайл 1x1 градус, имя задаёт юго-западный угол
    minLat = lat;
    maxLat = lat + 1.0;
    minLon = lon;
    maxLon = lon + 1.0;

    return true;
}

const SrtmGridTileSource::SrtmCell* SrtmGridTileSource::findCell(double latDeg,
                                                                 double lonDeg) const
{
    QMutexLocker locker(&m_mutex);

    for (const SrtmCell &cell : m_cells)
    {
        // запас по верхним границам, чтобы не терять точку на стыке
        if (latDeg >= cell.minLat && latDeg <= cell.maxLat &&
            lonDeg >= cell.minLon && lonDeg <= cell.maxLon)
        {
            return &cell;
        }
    }

    return nullptr;
}

bool SrtmGridTileSource::sampleFromHgt(const SrtmCell &cell,
                                       double latDeg, double lonDeg,
                                       double &outMeters) const
{
    QFile f(cell.filePath);
    if (!f.open(QIODevice::ReadOnly))
    {
        qWarning() << "[SRTM] Не удалось открыть" << cell.filePath;
        return false;
    }

    const qint64 fileSize = f.size();
    if (fileSize <= 0 || (fileSize % 2) != 0)
    {
        qWarning() << "[SRTM] Некорректный размер файла" << cell.filePath << fileSize;
        return false;
    }

    const qint64 samplesCount = fileSize / 2;  // int16
    const int side = static_cast<int>(qRound(qSqrt(static_cast<double>(samplesCount))));
    if (side * side != samplesCount)
    {
        qWarning() << "[SRTM] Не квадратный массив в" << cell.filePath
                   << "samplesCount=" << samplesCount
                   << "side^2=" << (side * side);
        return false;
    }

    // Нормирую lat/lon в [0..1] внутри этой плитки:
    //   latFrac: 0 на севере (maxLat), 1 на юге (minLat)
    //   lonFrac: 0 на западе (minLon), 1 на востоке (maxLon)
    const double latSpan = cell.maxLat - cell.minLat;
    const double lonSpan = cell.maxLon - cell.minLon;
    if (latSpan == 0.0 || lonSpan == 0.0)
        return false;

    double latFrac = (cell.maxLat - latDeg) / latSpan;
    double lonFrac = (lonDeg - cell.minLon) / lonSpan;

    latFrac = qBound(0.0, latFrac, 1.0);
    lonFrac = qBound(0.0, lonFrac, 1.0);

    const double rowF = latFrac * (side - 1);
    const double colF = lonFrac * (side - 1);

    int row = static_cast<int>(qRound(rowF));
    int col = static_cast<int>(qRound(colF));

    row = qBound(0, row, side - 1);
    col = qBound(0, col, side - 1);

    const qint64 index      = static_cast<qint64>(row) * side + col;
    const qint64 byteOffset = index * 2;

    if (!f.seek(byteOffset))
    {
        qWarning() << "[SRTM] Не удалось seek() в" << cell.filePath
                   << "offset=" << byteOffset;
        return false;
    }

    QDataStream ds(&f);
    ds.setByteOrder(QDataStream::BigEndian);   // SRTM: Big-Endian int16

    qint16 value = 0;
    ds >> value;
    if (ds.status() != QDataStream::Ok)
    {
        qWarning() << "[SRTM] Ошибка чтения значения из" << cell.filePath;
        return false;
    }

    // -32768 - "no data"
    if (value == -32768)
    {
        qWarning() << "[SRTM] NO_DATA в точке" << latDeg << lonDeg
                   << "файл" << cell.filePath;
        return false;
    }

    outMeters = static_cast<double>(value);
    return true;
}

bool SrtmGridTileSource::sampleHeight(double latDeg, double lonDeg, double &outMeters) const
{
    const SrtmCell *cell = findCell(latDeg, lonDeg);
    if (!cell)
    {
        // В этой области нет ни одной плитки из индекса
        return false;
    }

    const QString lower = cell->filePath.toLower();
    if (lower.endsWith(".hgt"))
    {
        // Поддерживаю .hgt напрямую
        return sampleFromHgt(*cell, latDeg, lonDeg, outMeters);
    }

    // TODO: для .tif/.tiff/.dt0/.dt1 нужен GDAL, прикручу позже, чтобы не навешивать на движок много задача, наверное внешний сервис будет
    qWarning() << "[SRTM] sampleHeight: формат пока не поддерживается" << cell->filePath;
    return false;
}

void SrtmGridTileSource::fetchTile(quint32 x,
                                   quint32 y,
                                   quint8 z)
{
    const quint16 ts = this->tileSize();

    // Сценовые координаты границ тайла (как в GridTileSource::fetchTile)
    const quint64 leftScenePixel   = static_cast<quint64>(x) * ts;
    const quint64 topScenePixel    = static_cast<quint64>(y) * ts;
    const quint64 rightScenePixel  = leftScenePixel  + ts;
    const quint64 bottomScenePixel = topScenePixel   + ts;

    //Создаём тайл в куче, как это делает GridTileSource
    QImage *toRet = new QImage(ts,
                               ts,
                               QImage::Format_ARGB32_Premultiplied);
    // Прозрачный фон - чтобы подложка OSM была видна под сеткой
    toRet->fill(qRgba(0, 0, 0, 0));

    QPainter painter(toRet);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Стиль SRTM-плиток: красная полупрозрачная заливка + рамка
    QPen pen(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);

    QColor fillColor(255, 0, 0, 40); // красный с небольшой альфой
    painter.setBrush(fillColor);

    {
        QMutexLocker locker(&m_mutex);

        for (const SrtmCell &cell : m_cells)
        {
            //Проецируем углы SRTM-плитки в "сценовые" координаты (пиксели)
            //В ll2qgs: x = longitude, y = latitude.
            QPointF nwScene = this->ll2qgs(QPointF(cell.minLon, cell.maxLat), z); // NW
            QPointF seScene = this->ll2qgs(QPointF(cell.maxLon, cell.minLat), z); // SE

            QRectF sceneRect(nwScene, seScene);
            sceneRect = sceneRect.normalized();

            //Быстрый отсев: пересекается ли плитка SRTM с текущим тайлом
            if (sceneRect.right()  < static_cast<qreal>(leftScenePixel)   ||
                sceneRect.left()   > static_cast<qreal>(rightScenePixel)  ||
                sceneRect.bottom() < static_cast<qreal>(topScenePixel)    ||
                sceneRect.top()    > static_cast<qreal>(bottomScenePixel))
            {
                continue;
            }

            //Переводим в локальные координаты тайла (0..ts)
            QRectF localRect(sceneRect.left()   - static_cast<qreal>(leftScenePixel),
                             sceneRect.top()    - static_cast<qreal>(topScenePixel),
                             sceneRect.width(),
                             sceneRect.height());

            painter.drawRect(localRect);

            // При желании можно включить подписи, но тут нужно поиграть с зумом:
            // painter.setPen(Qt::white);
            // painter.setBrush(Qt::NoBrush);
            // painter.drawText(localRect.topLeft() + QPointF(2, 12),
            //                  QFileInfo(cell.filePath).baseName());
            // painter.setPen(pen);
            // painter.setBrush(fillColor);
        }
    }

    painter.end();

    //    MapTileSource сам пробросит сигнал tileRetrieved(x,y,z)
    this->prepareNewlyReceivedTile(x, y, z, toRet);
}
