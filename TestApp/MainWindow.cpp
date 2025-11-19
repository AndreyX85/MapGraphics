#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MapGraphicsView.h"
#include "MapGraphicsScene.h"
#include "tileSources/GridTileSource.h"
#include "tileSources/OSMTileSource.h"
#include "tileSources/CompositeTileSource.h"
#include "guts/CompositeTileSourceConfigurationWidget.h"
#include "CircleObject.h"
#include "PolygonObject.h"

#include <QSharedPointer>
#include <QtDebug>
#include <QThread>
#include <QImage>
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Создаём сцену и вид
    MapGraphicsScene *scene = new MapGraphicsScene(this);
    MapGraphicsView  *view  = new MapGraphicsView(scene, this);
    this->setCentralWidget(view);

    // Сохраняем в поле, чтобы дальше было проще работать
    m_view = view;

    // Базовые источники тайлов
    QSharedPointer<OSMTileSource> osmTiles(
        new OSMTileSource(OSMTileSource::OSMTiles),
        &QObject::deleteLater);

    QSharedPointer<GridTileSource> gridTiles(
        new GridTileSource(),
        &QObject::deleteLater);

    // Настраиваем, где лежат SRTM/DTED файлы
    QStringList srtmDirs;
    // ВНИМАНИЕ: здесь нужны реальные пути до каталогов SRTM (.hgt и т.п.)
    srtmDirs << "C:/SRTM";

    // Создаём слой SRTM
    m_srtmTiles = QSharedPointer<SrtmGridTileSource>(new SrtmGridTileSource(srtmDirs), &QObject::deleteLater);

    // Собираем CompositeTileSource
    QSharedPointer<CompositeTileSource> composite(
        new CompositeTileSource(),
        &QObject::deleteLater);

    // ВНИМАНИЕ: здесь нужны реальные ключи
    const QString owmApiKey = QStringLiteral("YOU KEY");

    QSharedPointer<MeteoGridTileSource> meteoTiles(new MeteoGridTileSource(owmApiKey, MeteoGridTileSource::Layer::Temperature), &QObject::deleteLater);

    //уменьшаем/увеличиваем прозрачность, или через инструментарий
    //meteoTiles->setOpacity(0.7);

    composite->addSourceBottom(osmTiles);     // внизу - OSM
    composite->addSourceTop(gridTiles);       // поверх - обычная сетка
    composite->addSourceTop(meteoTiles);      // метео
    composite->addSourceTop(m_srtmTiles);     // зоны SRTM

    m_view->setTileSource(composite);

    // Док с конфигуратором слоёв
    CompositeTileSourceConfigurationWidget *tileConfigWidget =
        new CompositeTileSourceConfigurationWidget(composite.toWeakRef(),
                                                   this->ui->dockWidget);
    this->ui->dockWidget->setWidget(tileConfigWidget);
    delete this->ui->dockWidgetContents;

    this->ui->menuWindow->addAction(this->ui->dockWidget->toggleViewAction());
    this->ui->dockWidget->toggleViewAction()->setText("&Layers");

    // Начальный zoom/центр
    m_view->setZoomLevel(10);
    // центрируем
    m_view->centerOn(55.9936234, 37.202442); // (lon, lat)

    // Пример объекта
    MapGraphicsObject *circle = new CircleObject(5000, false, QColor(255, 0, 0, 100));
    circle->setLatitude(55.9936234);
    circle->setLongitude(37.202442);
    scene->addObject(circle);

    // Подписываемся на клик по карте (сигнал от MapGraphicsView)
    connect(m_view, &MapGraphicsView::mouseClickedLL, this, &MainWindow::onMapClickedLL);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::onMapClickedLL(const QPointF& ll, const QPoint& globalPos)
{
    if (m_srtmTiles.isNull())
        return;

    const double lon = ll.x();
    const double lat = ll.y();

    double h = 0.0;
    if (m_srtmTiles->sampleHeight(lat, lon, h))
    {
        // Успешно получили высоту - показываем всплывающую подсказку
        const QString text =
            QStringLiteral("Широта: %1\nДолгота: %2\nВысота: %3 м")
                .arg(lat, 0, 'f', 6)
                .arg(lon, 0, 'f', 6)
                .arg(h,   0, 'f', 1);

        QToolTip::showText(globalPos, text, this);
    }
    else
    {
        // можно показывать и "нет данных":
        // QToolTip::showText(globalPos,
        //                    QStringLiteral("Нет данных SRTM"),
        //                    this);
    }
}
