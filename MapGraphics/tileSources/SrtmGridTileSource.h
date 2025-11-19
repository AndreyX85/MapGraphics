#ifndef SRTMGRIDTILESOURCE_H
#define SRTMGRIDTILESOURCE_H

#include "GridTileSource.h"

#include <QVector>
#include <QDir>
#include <QMutex>
#include <QStringList>
#include <QRectF>

/**
 * @brief SrtmGridTileSource
 * Источник тайлов, который:
 *  - поверх базовой карты рисует прямоугольники SRTM/DTED-плиток;
 *  - умеет по клику (lat, lon) вернуть высоту по данным .hgt.
 *
 * Наследуемся от GridTileSource, чтобы:
 *  - использовать уже готовую геометрию (ll2qgs, qgs2ll, tileSize, ...);
 */
class MAPGRAPHICSSHARED_EXPORT SrtmGridTileSource : public GridTileSource
{
    Q_OBJECT
public:
    /**
     * @brief SrtmGridTileSource
     * @param rootDirs список корневых каталогов, где лежат SRTM/DTED-файлы
     * @param parent   родитель по Qt (сейчас не используется, но оставлен для совместимости)
     */
    explicit SrtmGridTileSource(const QStringList& rootDirs,
                                QObject *parent = nullptr);

    /// Имя источника, которое будет видно в списке слоёв (Layers)
    QString name() const override;

    /**
     * @brief sampleHeight
     * @param latDeg    широта точки, градусы
     * @param lonDeg    долгота точки, градусы
     * @param outMeters [out] высота в метрах над уровнем моря
     * @return true  - если нашли подходящую плитку и корректное значение;
     *         false - если плитки нет или данные отсутствуют (NO_DATA).
     *
     * ВАЖНО: //TODO реализовать кеширование
     *  - сейчас поддерживаются только файлы формата .hgt (SRTM);
     *  - чтение синхронное, с диска, без кэша - не дергать слишком часто
     *    из GUI-потока в цикле по траектории.
     *
     * Типичный сценарий:
     *  1) Обрабатываем клик мышью в MapGraphicsView;
     *  2) конвертируем координаты клика в lat/lon через qgs2ll();
     *  3) вызываем sampleHeight(lat, lon, h);
     *  4) показываем QToolTip с высотой.
     */
    bool sampleHeight(double latDeg, double lonDeg, double &outMeters) const;

protected:
    /// Рисуем один тайл (x, y, z), накладывая на него прямоугольники SRTM-плиток
    void fetchTile(quint32 x,
                   quint32 y,
                   quint8 z) override;

private:
    /// Описание одной SRTM/DTED-плитки
    struct SrtmCell
    {
        double  minLat;    //!< южная граница, градусы
        double  maxLat;    //!< северная граница, градусы
        double  minLon;    //!< западная граница, градусы
        double  maxLon;    //!< восточная граница, градусы
        QString filePath;  //!< полный путь к файлу
    };

    QVector<SrtmCell>   m_cells;          //!< индекс всех найденных плиток
    mutable QMutex      m_mutex;          //!< защита при доступе к m_cells, mutable для const-методов

    /// Построение индекса по списку корневых каталогов
    void buildIndex(const QStringList& rootDirs);

    /// Рекурсивный обход одного каталога
    void scanDir(const QDir& dir);

    //TODO взял старую свою наработку, нужно проверить все покрытие
    /// Разбор имени файла вида N55E037.hgt -> bbox 1x1 градус
    bool parseSrtmName(const QString& fileName,
                       double& minLat, double& maxLat,
                       double& minLon, double& maxLon) const;

    /// Найти плитку, которая покрывает заданную точку (lat, lon)
    const SrtmCell* findCell(double latDeg, double lonDeg) const;

    /// Выборка высоты из .hgt-файла для точки внутри данной плитки
    bool sampleFromHgt(const SrtmCell &cell,
                       double latDeg, double lonDeg,
                       double &outMeters) const;
};

#endif // SRTMGRIDTILESOURCE_H
