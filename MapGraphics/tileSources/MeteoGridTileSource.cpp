#include "MeteoGridTileSource.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QImage>
#include <QPainter>
#include <QtMath>
#include <QtDebug>

MeteoGridTileSource::MeteoGridTileSource(const QString& apiKey,
                                         Layer layer,
                                         QObject* parent)
    : GridTileSource()             // базовый класс НЕ принимает parent
    , m_network(new QNetworkAccessManager(this))
    , m_apiKey(apiKey)
    , m_layer(layer)
    , m_opacity(0.8)               // по умолчанию делаем полупрозрачный слой
{   
    this->setParent(parent);

    // Подписываемся на завершение всех сетевых запросов
    connect(m_network, &QNetworkAccessManager::finished, this, &MeteoGridTileSource::handleNetworkReply);

    // GridTileSource по умолчанию выключает кэш (NoCaching).
    // Для погодных данных это даже логично (они меняются).
}

QString MeteoGridTileSource::name() const
{
    QString layerName;
    switch (m_layer)
    {
        case Layer::Temperature:   layerName = QStringLiteral("temperature");   break;
        case Layer::Wind:          layerName = QStringLiteral("wind");          break;
        case Layer::Clouds:        layerName = QStringLiteral("clouds");        break;
        case Layer::Precipitation: layerName = QStringLiteral("precipitation"); break;
        case Layer::Pressure:      layerName = QStringLiteral("pressure");      break;
    }

    return QStringLiteral("Meteo (OpenWeather %1)").arg(layerName);
}

void MeteoGridTileSource::setApiKey(const QString& apiKey)
{
    m_apiKey = apiKey;
}

void MeteoGridTileSource::setLayer(MeteoGridTileSource::Layer layer)
{
    if (m_layer == layer)
        return;

    m_layer = layer;

    // Тут специально НИЧЕГО не делаем с кэшем:
    //  - у нас NoCaching, так что старые тайлы не переиспользуются;
    //  - новые запросы пойдут уже с другим layerId().
    // Если включить кэш - нужно будет продумать полную очистку.
}

void MeteoGridTileSource::setOpacity(qreal opacity)
{
    // Нормируем в диапазон [0; 1]
    if (opacity < 0.0)
        opacity = 0.0;
    else if (opacity > 1.0)
        opacity = 1.0;

    if (qFuzzyCompare(m_opacity, opacity))
        return;

    m_opacity = opacity;
    // Уже загруженные тайлы мы не перерисовываем, они останутся
    // со старой прозрачностью. При следующем движении/зуме карты
    // тайлы будут запрошены заново с новым значением.
}

QString MeteoGridTileSource::layerId(MeteoGridTileSource::Layer layer) const
{
    switch (layer)
    {
        case Layer::Temperature:   return QStringLiteral("temp_new");
        case Layer::Wind:          return QStringLiteral("wind_new");
        case Layer::Clouds:        return QStringLiteral("clouds_new");
        case Layer::Precipitation: return QStringLiteral("precipitation_new");
        case Layer::Pressure:      return QStringLiteral("pressure_new");
    }

    // температура по умолчанию
    return QStringLiteral("temp_new");
}

QUrl MeteoGridTileSource::buildTileUrl(quint32 x, quint32 y, quint8 z) const
{
    // Документация Weather Maps 1.0:
    //   https://tile.openweathermap.org/map/{layer}/{z}/{x}/{y}.png?appid={API key}
    // layerId(m_layer) уже содержит suffix "_new".
    const QString base =
            QStringLiteral("https://tile.openweathermap.org/map/%1/%2/%3/%4.png")
            .arg(layerId(m_layer))
            .arg(z)
            .arg(x)
            .arg(y);

    QUrl url(base);
    QUrlQuery query;

    if (!m_apiKey.isEmpty())
        query.addQueryItem(QStringLiteral("appid"), m_apiKey);
    else
        qWarning() << "[Meteo] API key is empty – layer will show only placeholder tiles";

    //   query.addQueryItem("opacity", QString::number(m_opacity));
    //   query.addQueryItem("date", QString::number(unixTime));
    url.setQuery(query);

    return url;
}

QImage* MeteoGridTileSource::makeEmptyTile() const
{
    // Тайловый размер берём из GridTileSource::tileSize()
    const int size = this->tileSize();

    QImage* tile = new QImage(size, size, QImage::Format_ARGB32_Premultiplied);
    tile->fill(qRgba(0, 0, 0, 0));   // полностью прозрачный

    return tile;
}

QImage* MeteoGridTileSource::applyOpacity(const QImage& src) const
{
    // Если прозрачность ~1.0 - можно просто склонировать изображение
    if (m_opacity >= 0.999)
        return new QImage(src.convertToFormat(QImage::Format_ARGB32_Premultiplied));

    QImage dst(src.size(), QImage::Format_ARGB32_Premultiplied);
    dst.fill(qRgba(0, 0, 0, 0));

    {
        QPainter p(&dst);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        p.setOpacity(m_opacity);   // глобальная прозрачность
        p.drawImage(0, 0, src);
    }

    return new QImage(dst);
}

void MeteoGridTileSource::fetchTile(quint32 x, quint32 y, quint8 z)
{
    // MapGraphics вызывает этот метод в отдельном «тайловом» потоке,
    // так что блокировки UI не боимся. Но всё равно делаем
    // асинхронный запрос, чтобы можно было параллельно качать много тайлов.

    if (m_apiKey.isEmpty())
    {
        // Без ключа не ходим в сеть, сразу рисуем простую заглушку.
        QImage* tile = makeEmptyTile();

        {
            QPainter p(tile);
            p.setPen(Qt::red);
            p.setBrush(Qt::NoBrush);
            p.drawRect(1, 1, tile->width() - 2, tile->height() - 2);
            p.drawText(4, 16, QStringLiteral("NO API KEY"));
        }

        this->prepareNewlyReceivedTile(x, y, z, tile);
        return;
    }

    const QUrl url = buildTileUrl(x, y, z);

    QNetworkRequest req(url);

    //req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Qt 5: старый атрибут
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#else
    // Qt 6: новая политика редиректов
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                     QNetworkRequest::NoLessSafeRedirectPolicy);
#endif

    QNetworkReply* reply = m_network->get(req);

    // Запоминаем, для каких координат этот reply ожидаем
    PendingTile info;
    info.x = x;
    info.y = y;
    info.z = z;
    m_pending.insert(reply, info);
}

void MeteoGridTileSource::handleNetworkReply(QNetworkReply* reply)
{
    // Вытащим координаты тайла, для которого это был запрос
    const auto it = m_pending.find(reply);
    if (it == m_pending.end())
    {
        reply->deleteLater();
        return;
    }

    const PendingTile info = it.value();
    m_pending.erase(it);

    // Обработка сетевой ошибки
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "[Meteo] Network error for tile"
                   << info.x << info.y << info.z << ":" << reply->errorString();

        QImage* tile = makeEmptyTile();
        this->prepareNewlyReceivedTile(info.x, info.y, info.z, tile);

        reply->deleteLater();
        return;
    }

    // Преобразуем байты PNG → QImage
    const QByteArray bytes = reply->readAll();
    QImage img;
    if (!img.loadFromData(bytes))
    {
        qWarning() << "[Meteo] Failed to decode PNG for tile"
                   << info.x << info.y << info.z;

        QImage* tile = makeEmptyTile();
        this->prepareNewlyReceivedTile(info.x, info.y, info.z, tile);

        reply->deleteLater();
        return;
    }

    //приведём размер к tileSize (обычно и так 256x256)
    const int size = this->tileSize();
    if (img.width() != size || img.height() != size)
    {
        img = img.scaled(size, size,
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
    }

    // Применяем глобальную прозрачность
    QImage* tile = applyOpacity(img);

    this->prepareNewlyReceivedTile(info.x, info.y, info.z, tile);

    reply->deleteLater();
}
