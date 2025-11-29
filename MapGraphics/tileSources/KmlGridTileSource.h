#ifndef KMLGRIDTILESOURCE_H
#define KMLGRIDTILESOURCE_H

#include "GridTileSource.h"
#include "MapGraphics_global.h"

#include <QVector>
#include <QPointF>
#include <QColor>
#include <QString>

class QPainter;

/// Если хотим использовать QtKMLLib / libkml, достаточно определить этот макрос
/// DEFINES += USE_QTKMLLIB
/// можешь включать/выключать по вкусу.
/// #define USE_QTKMLLIB 1

class MAPGRAPHICSSHARED_EXPORT KmlGridTileSource : public GridTileSource
{
    Q_OBJECT
public:
    /// Тип геометрии KML-фичи
    enum GeometryType
    {
        GeometryPoint,
        GeometryPolyline,
        GeometryPolygon
    };

    /// Одна фича, которую позже рисуем на тайле
    struct Feature
    {
        QString          name;    ///< <name> из KML (может быть пустым)
        GeometryType     type;    ///< тип геометрии
        QVector<QPointF> coords;  ///< набор точек в WGS-84 (lon, lat)
    };

public:
    explicit KmlGridTileSource(const QString& kmlFilePath,
                               QObject* parent = nullptr);

    /// Перечитать файл KML (если path пустой — используем сохранённый m_kmlPath)
    bool reloadKml(const QString& path = QString());

    /// Имя источника, которое будет видно в списке слоёв (Layers)
    QString name() const override;

protected:
    /// Реализация виртуального метода GridTileSource:
    /// MapGraphics вызывает его, когда нужен тайл (x,y,z)
    void fetchTile(quint32 x, quint32 y, quint8 z) override;

private:
    /// Создаём пустой "прозрачный" тайл (не override)
    QImage* makeEmptyTile() const;

    /// Нарисовать одну фичу на конкретном тайле
    void drawFeatureOnTile(QPainter& p,
                           const Feature& feature,
                           quint32 tileX,
                           quint32 tileY,
                           quint8  zoom) const;

    /// Геопривязка: lon/lat → "мировые" пиксели WebMercator
    static double lonToWorldX(double lonDeg, quint8 zoom, int tileSize);
    static double latToWorldY(double latDeg, quint8 zoom, int tileSize);

#ifndef USE_QTKMLLIB
    // -----------------------------
    // ВАРИАНТ 1: ручной парсер KML
    // -----------------------------

    /// Разбор содержимого <coordinates>...</coordinates> в вектор (lon,lat)
    static QVector<QPointF> parseCoordinates(const QString& text);

    /// Разбор KML-файла через QXmlStreamReader (старый, но уже отлаженный)
    bool parseKmlFile(const QString& path);

#else
    // -----------------------------
    // ВАРИАНТ 2: через QtKMLLib/libkml
    // -----------------------------

    /// Общий вход для разбора KML — вызывается из конструктора и reloadKml()
    bool parseKmlFile(const QString& path);

    /// Реальная реализация через libkml (QtKMLLib поверх него)
    bool parseKmlFileQtKmlLib(const QString& path);
#endif

private:
    /// Путь к файлу KML
    QString          m_kmlPath;

    /// Все найденные фичи из KML (точки, линии, полигоны)
    QVector<Feature> m_features;

    /// Параметры отрисовки
    double m_pointRadius;
    QColor m_pointColor;
    QColor m_lineColor;
    QColor m_polygonFillColor;
};

#endif // KMLGRIDTILESOURCE_H
