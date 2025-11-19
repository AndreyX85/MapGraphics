#ifndef METEOGRIDTILESOURCE_H
#define METEOGRIDTILESOURCE_H

#include "GridTileSource.h"
#include "MapGraphics_global.h"

#include <QHash>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QNetworkReply;
QT_END_NAMESPACE

/**
 * @brief MeteoGridTileSource
 * Источник тайлов, который поверх базовой карты рисует метеослои
 * с сервиса OpenWeather (Weather Maps 1.0).
 */
class MAPGRAPHICSSHARED_EXPORT MeteoGridTileSource : public GridTileSource
{
    Q_OBJECT
public:
    /**
     * @brief Тип метеослоя.
     *
     * Привязан к layer'ам OpenWeather Weather Maps 1.0:
     *   - Temperature   → "temp_new"
     *   - Wind          → "wind_new"
     *   - Clouds        → "clouds_new"
     *   - Precipitation → "precipitation_new"
     *   - Pressure      → "pressure_new"
     */
    enum class Layer
    {
        Temperature,
        Wind,
        Clouds,
        Precipitation,
        Pressure
    };
    Q_ENUM(Layer)

    /**
     * @brief MeteoGridTileSource
     * @param apiKey API-ключ OpenWeather (https://openweathermap.org/)
     * @param layer  какой метеослой рисуем по умолчанию
     * @param parent родитель по Qt (для удобства владения, не используется в base ctor)
     */
    explicit MeteoGridTileSource(const QString& apiKey,
                                 Layer layer = Layer::Temperature,
                                 QObject* parent = nullptr);

    /// Имя источника, которое видно в окне Layers
    QString name() const override;

    /// Установить/получить API-ключ (если меняешь во время работы)
    void setApiKey(const QString& apiKey);
    QString apiKey() const { return m_apiKey; }

    /// Установить/получить используемый слой (Temperature/Wind/...)
    void setLayer(Layer layer);
    Layer layer() const { return m_layer; }

    /**
     * @brief setOpacity
     * Глобальная прозрачность для метеослоя (0.0 - полностью
     * прозрачный, 1.0 - полностью непрозрачный).
     *
     * Фактически мы рендерим PNG в новый QImage с заданной opacity.
     */
    void setOpacity(qreal opacity);
    qreal opacity() const { return m_opacity; }

protected:
    /**
     * @brief fetchTile
     * Запрос одного тайла (x, y, z).
     *
     * Здесь мы:
     *  - строим URL к тайлу OpenWeather;
     *  - запускаем асинхронный HTTP-запрос;
     *  - по завершении в слоте handleNetworkReply() вызываем
     *    prepareNewlyReceivedTile(...).
     */
    void fetchTile(quint32 x,
                   quint32 y,
                   quint8  z) override;

private slots:
    /// Слот, вызываемый по завершении любого сетевого запроса
    void handleNetworkReply(QNetworkReply* reply);

private:
    /// Ключ: слой → строковый идентификатор слоя OpenWeather
    QString layerId(Layer layer) const;

    /// Построение полного URL к тайлу OpenWeather по координатам x/y/z
    QUrl buildTileUrl(quint32 x, quint32 y, quint8 z) const;

    /// Создаёт пустой (полностью прозрачный) тайл нужного размера
    QImage* makeEmptyTile() const;

    /// Возвращает новый QImage с применённой прозрачностью m_opacity
    QImage* applyOpacity(const QImage& src) const;

    /// Описание ожидаемого тайла, пока он качается из сети
    struct PendingTile
    {
        quint32 x;
        quint32 y;
        quint8  z;
    };

    QNetworkAccessManager*             m_network;  //!< один менеджер на весь источник
    QString                            m_apiKey;   //!< API-ключ OpenWeather
    Layer                              m_layer;    //!< текущий тип слоя
    qreal                              m_opacity;  //!< глобальная прозрачность [0..1]
    QHash<QNetworkReply*, PendingTile> m_pending;  //!< соответствие reply → координаты тайла
};

#endif // METEOGRIDTILESOURCE_H
