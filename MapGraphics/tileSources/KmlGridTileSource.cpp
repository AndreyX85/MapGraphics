#include "KmlGridTileSource.h"

#include <QFile>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QDebug>
#include <QXmlStreamReader>
#include <QRegularExpression>

#ifdef USE_QTKMLLIB
// libkml - движок, на котором базируется QtKMLLib
#include <kml/dom.h>
#include <string>
#endif

KmlGridTileSource::KmlGridTileSource(const QString& kmlFilePath,
                                     QObject* parent)
    : GridTileSource()              // базовый класс без parent
    , m_kmlPath(kmlFilePath)
    , m_pointRadius(4.0)
    , m_pointColor(Qt::red)
    , m_lineColor(Qt::yellow)
    , m_polygonFillColor(QColor(255, 165, 0, 80))   // полу-прозрачный оранжевый
{
    this->setParent(parent);

    // Сразу пробуем загрузить файл, если путь задан
    if (!m_kmlPath.isEmpty())
    {
        if (!parseKmlFile(m_kmlPath))
        {
            qWarning() << "[KML] Failed to parse file in ctor:" << m_kmlPath;
        }
    }
}

QString KmlGridTileSource::name() const
{
    return QStringLiteral("KML grid overlay");
}


bool KmlGridTileSource::reloadKml(const QString& path)
{
    const QString effectivePath = path.isEmpty() ? m_kmlPath : path;
    if (effectivePath.isEmpty())
    {
        qWarning() << "[KML] reloadKml(): no path specified";
        return false;
    }

    m_kmlPath = effectivePath;
    return parseKmlFile(m_kmlPath);
}

QImage* KmlGridTileSource::makeEmptyTile() const
{
    const int size = this->tileSize();

    QImage* tile = new QImage(size, size, QImage::Format_ARGB32_Premultiplied);
    // Полностью прозрачный фон - чтобы нижние слои просвечивали
    tile->fill(qRgba(0, 0, 0, 0));
    return tile;
}

void KmlGridTileSource::fetchTile(quint32 x, quint32 y, quint8 z)
{
    // MapGraphics вызывает этот метод обычно из рабочего потока.
    // m_features только читаем (без модификаций).
    QImage* tile = makeEmptyTile();

    if (m_features.isEmpty())
    {
        // Нет данных - отдаём пустой тайл
        this->prepareNewlyReceivedTile(x, y, z, tile);
        return;
    }

    QPainter p(tile);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    // Проходим по всем фичам и рисуем их поверх
    for (const Feature& f : m_features)
    {
        drawFeatureOnTile(p, f, x, y, z);
    }

    this->prepareNewlyReceivedTile(x, y, z, tile);
}

double KmlGridTileSource::lonToWorldX(double lonDeg, quint8 zoom, int tileSize)
{
    const double totalPixels = static_cast<double>(tileSize) * (1u << zoom);
    return (lonDeg + 180.0) / 360.0 * totalPixels;
}

double KmlGridTileSource::latToWorldY(double latDeg, quint8 zoom, int tileSize)
{
    // Стандартное ограничение WebMercator
    const double maxLat = 85.05112878;
    double clampedLat   = qBound(-maxLat, latDeg, maxLat);

    const double latRad = qDegreesToRadians(clampedLat);
    const double sinLat = qSin(latRad);

    const double totalPixels = static_cast<double>(tileSize) * (1u << zoom);

    // Формула из спецификации WebMercator
    double y = 0.5 - 0.25 * qLn((1.0 + sinLat) / (1.0 - sinLat)) / M_PI;
    return y * totalPixels;
}

void KmlGridTileSource::drawFeatureOnTile(QPainter& p,
                                          const Feature& feature,
                                          quint32 tileX,
                                          quint32 tileY,
                                          quint8  zoom) const
{
    const int tileSizePx = this->tileSize();

    // Преобразуем все точки фичи в локальные пиксели тайла [0..tileSizePx)
    QVector<QPointF> pts;
    pts.reserve(feature.coords.size());

    for (const QPointF& wgs : feature.coords)
    {
        const double lon = wgs.x();
        const double lat = wgs.y();

        const double worldX = lonToWorldX(lon, zoom, tileSizePx);
        const double worldY = latToWorldY(lat, zoom, tileSizePx);

        const double localX = worldX - static_cast<double>(tileX * tileSizePx);
        const double localY = worldY - static_cast<double>(tileY * tileSizePx);

        pts.append(QPointF(localX, localY));
    }

    if (pts.isEmpty())
        return;

    switch (feature.type)
    {
    case GeometryPoint:
    {
        const QPointF& center = pts.first();
        p.setPen(Qt::NoPen);
        p.setBrush(m_pointColor);
        p.drawEllipse(center, m_pointRadius, m_pointRadius);
        break;
    }

    case GeometryPolyline:
    {
        if (pts.size() < 2)
            return;

        QPen pen(m_lineColor);
        pen.setWidthF(2.0);
        pen.setCosmetic(true);  // толщина в пикселях, не зависит от масштаба
        p.setPen(pen);
        p.setBrush(Qt::NoBrush);

        p.drawPolyline(pts.constData(), pts.size());
        break;
    }

    case GeometryPolygon:
    {
        if (pts.size() < 3)
            return;

        QPainterPath path;
        path.moveTo(pts.first());
        for (int i = 1; i < pts.size(); ++i)
            path.lineTo(pts.at(i));
        path.closeSubpath();

        QPen pen(m_lineColor);
        pen.setWidthF(1.5);
        pen.setCosmetic(true);

        p.setPen(pen);
        p.setBrush(m_polygonFillColor);
        p.drawPath(path);
        break;
    }
    }
}

#ifndef USE_QTKMLLIB
// =================================================================
// ВАРИАНТ 1: ручной парсер через QXmlStreamReader (старый рабочий)
// =================================================================

QVector<QPointF> KmlGridTileSource::parseCoordinates(const QString& text)
{
    QVector<QPointF> result;

    const QString trimmed = text.trimmed();
    const QRegularExpression wsRe(QStringLiteral("\\s+"));
    const QStringList tokens = trimmed.split(wsRe, Qt::SkipEmptyParts);

    for (const QString& t : tokens)
    {
        // Формат: lon,lat[,alt]
        const QStringList parts = t.split(QLatin1Char(','), Qt::SkipEmptyParts);
        if (parts.size() < 2)
            continue;

        bool okLon = false;
        bool okLat = false;
        const double lon = parts.at(0).toDouble(&okLon);
        const double lat = parts.at(1).toDouble(&okLat);
        if (!okLon || !okLat)
            continue;

        result.append(QPointF(lon, lat));
    }

    return result;
}

bool KmlGridTileSource::parseKmlFile(const QString& path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "[KML] Cannot open file" << path << ":" << f.errorString();
        m_features.clear();
        return false;
    }

    QXmlStreamReader xml(&f);
    QVector<Feature> newFeatures;

    while (!xml.atEnd())
    {
        xml.readNext();

        if (!xml.isStartElement())
            continue;

        if (xml.name() == QLatin1String("Placemark"))
        {
            Feature feature;
            feature.type = GeometryPoint;    // по умолчанию

            QString name;
            QVector<QPointF> coords;
            GeometryType geomType = GeometryPoint;

            // Читаем до конца текущего Placemark
            while (!(xml.isEndElement() &&
                     xml.name() == QLatin1String("Placemark")) &&
                   !xml.atEnd())
            {
                xml.readNext();

                if (!xml.isStartElement())
                    continue;

                const QString tag = xml.name().toString();

                if (tag == QLatin1String("name"))
                {
                    name = xml.readElementText().trimmed();
                }
                else if (tag == QLatin1String("Point"))
                {
                    geomType = GeometryPoint;

                    while (!(xml.isEndElement() &&
                             xml.name() == QLatin1String("Point")) &&
                           !xml.atEnd())
                    {
                        xml.readNext();
                        if (xml.isStartElement() &&
                            xml.name() == QLatin1String("coordinates"))
                        {
                            const QString coordsText = xml.readElementText();
                            coords = parseCoordinates(coordsText);
                        }
                    }
                }
                else if (tag == QLatin1String("LineString"))
                {
                    geomType = GeometryPolyline;

                    while (!(xml.isEndElement() &&
                             xml.name() == QLatin1String("LineString")) &&
                           !xml.atEnd())
                    {
                        xml.readNext();
                        if (xml.isStartElement() &&
                            xml.name() == QLatin1String("coordinates"))
                        {
                            const QString coordsText = xml.readElementText();
                            coords = parseCoordinates(coordsText);
                        }
                    }
                }
                else if (tag == QLatin1String("Polygon"))
                {
                    geomType = GeometryPolygon;

                    while (!(xml.isEndElement() &&
                             xml.name() == QLatin1String("Polygon")) &&
                           !xml.atEnd())
                    {
                        xml.readNext();
                        if (xml.isStartElement() &&
                            xml.name() == QLatin1String("coordinates"))
                        {
                            const QString coordsText = xml.readElementText();
                            coords = parseCoordinates(coordsText);
                        }
                    }
                }
            } // while внутри Placemark

            if (!coords.isEmpty())
            {
                feature.name   = name;
                feature.type   = geomType;
                feature.coords = coords;
                newFeatures.append(feature);
            }
        }
    }

    if (xml.hasError())
    {
        qWarning() << "[KML] XML parse error in" << path
                   << ":" << xml.errorString();
    }

    m_features.swap(newFeatures);
    qDebug() << "[KML] Loaded features (QXml):" << m_features.size()
             << "from" << path;

    return !m_features.isEmpty();
}

#else // USE_QTKMLLIB
// ========================================================================
// ВАРИАНТ 2: разбор через libkml (движок QtKMLLib)
// ========================================================================

using namespace kmldom;

namespace
{

/// Вытянуть координаты из libkml::Coordinates в QVector<QPointF>(lon,lat)
static void appendCoordsFromLibKmlCoordinates(const CoordinatesPtr& coords,
                                              QVector<QPointF>& out)
{
    if (!coords)
        return;

    const int n = coords->get_coordinates_array_size();
    out.reserve(out.size() + n);

    for (int i = 0; i < n; ++i)
    {
        // coords->get_coordinates_array_at(i) возвращает объект,
        // у которого есть методы get_longitude()/get_latitude().
        const auto& v = coords->get_coordinates_array_at(i);

        const double lon = v.get_longitude();
        const double lat = v.get_latitude();

        out.append(QPointF(lon, lat));
    }
}

static void collectFeaturesFromDomFeature(const FeaturePtr& f,
                                          QVector<KmlGridTileSource::Feature>& out)
{
    if (!f)
        return;

    // Если это Container (Document/Folder) - рекурсивно обходим детей
    if (const ContainerPtr container = AsContainer(f))
    {
        const size_t n = container->get_feature_array_size();
        for (size_t i = 0; i < n; ++i)
        {
            FeaturePtr child = container->get_feature_array_at(i);
            collectFeaturesFromDomFeature(child, out);
        }
    }

    if (const PlacemarkPtr pm = AsPlacemark(f))
    {
        KmlGridTileSource::Feature feat;

        if (pm->has_name())
            feat.name = QString::fromStdString(pm->get_name());

        GeometryPtr geom = pm->get_geometry();
        if (!geom)
            return;

        QVector<QPointF> coords;
        KmlGridTileSource::GeometryType geomType = KmlGridTileSource::GeometryPoint;

        if (const PointPtr point = AsPoint(geom))
        {
            geomType = KmlGridTileSource::GeometryPoint;
            CoordinatesPtr c = point->get_coordinates();
            appendCoordsFromLibKmlCoordinates(c, coords);
        }
        else if (const LineStringPtr ls = AsLineString(geom))
        {
            geomType = KmlGridTileSource::GeometryPolyline;
            CoordinatesPtr c = ls->get_coordinates();
            appendCoordsFromLibKmlCoordinates(c, coords);
        }
        else if (const PolygonPtr poly = AsPolygon(geom))
        {
            geomType = KmlGridTileSource::GeometryPolygon;

            if (poly->has_outerboundaryis())
            {
                OuterBoundaryIsPtr ob = poly->get_outerboundaryis();
                if (ob && ob->has_linearring())
                {
                    LinearRingPtr ring = ob->get_linearring();
                    if (ring)
                    {
                        CoordinatesPtr c = ring->get_coordinates();
                        appendCoordsFromLibKmlCoordinates(c, coords);
                    }
                }
            }
        }
        else
        {
            // MultiGeometry и прочее пока игнорируем
            return;
        }

        if (!coords.isEmpty())
        {
            feat.type   = geomType;
            feat.coords = coords;
            out.append(feat);
        }
    }
}

} //end namespace

bool KmlGridTileSource::parseKmlFileQtKmlLib(const QString& path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "[KML/libkml] Cannot open file" << path << ":" << f.errorString();
        m_features.clear();
        return false;
    }

    const QByteArray data = f.readAll();
    const std::string xmlStr(data.constData(), static_cast<size_t>(data.size()));

    // Разбор KML
    ElementPtr root = ParseKml(xmlStr);
    if (!root)
    {
        qWarning() << "[KML/libkml] ParseKml() returned null for" << path;
        m_features.clear();
        return false;
    }

    QVector<Feature> newFeatures;

    if (const KmlPtr kml = AsKml(root))
    {
        if (const FeaturePtr feat = kml->get_feature())
            collectFeaturesFromDomFeature(feat, newFeatures);
    }
    else if (const FeaturePtr feat = AsFeature(root))
    {
        collectFeaturesFromDomFeature(feat, newFeatures);
    }

    m_features.swap(newFeatures);

    qDebug() << "[KML/libkml] Loaded features:" << m_features.size()
             << "from" << path;

    return !m_features.isEmpty();
}


bool KmlGridTileSource::parseKmlFile(const QString& path)
{
    return parseKmlFileQtKmlLib(path);
}

#endif // USE_QTKMLLIB
