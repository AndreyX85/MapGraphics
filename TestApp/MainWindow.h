#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QPointF>
#include <QPoint>

#include "tileSources/SrtmGridTileSource.h"
#include "tileSources/MeteoGridTileSource.h"
#include "tileSources/KmlGridTileSource.h"

class MapGraphicsView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    /// Слот, вызываемый при клике по карте (сигнал от MapGraphicsView)
    void onMapClickedLL(const QPointF& ll, const QPoint& globalPos);

private:
    Ui::MainWindow *ui;

    /// Вид карты
    MapGraphicsView *m_view = nullptr;

    /// Источник SRTM-данных (индекс плиток + sampleHeight())
    QSharedPointer<SrtmGridTileSource> m_srtmTiles;

    /// Источник данных KML (векторные объекты поверх карты)
    QSharedPointer<KmlGridTileSource> m_kmlTiles;
};

#endif // MAINWINDOW_H
