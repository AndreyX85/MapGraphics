#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T10:50:47
#
#-------------------------------------------------
CONFIG += c++17        # включаем C++17, Qt6 его всё равно требует
CONFIG += warn_on      # хотим максимум предупреждений

QT       += network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#pacman -S mingw-w64-x86_64-boost
#pacman -S mingw-w64-x86_64-libkml
DEFINES += USE_QTKMLLIB
LIBS    += -lkmldom -lkmlengine -lkmlbase

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050F00

TARGET = MapGraphics
TEMPLATE = lib

DEFINES += MAPGRAPHICS_LIBRARY

INCLUDEPATH += .

SOURCES += MapGraphicsScene.cpp \
    MapGraphicsObject.cpp \
    MapGraphicsView.cpp \
    guts/PrivateQGraphicsScene.cpp \
    guts/PrivateQGraphicsObject.cpp \
    guts/Conversions.cpp \
    MapTileSource.cpp \
    tileSources/GridTileSource.cpp \
    guts/MapTileGraphicsObject.cpp \
    guts/PrivateQGraphicsView.cpp \
    tileSources/MeteoGridTileSource.cpp \
    tileSources/OSMTileSource.cpp \
    guts/MapGraphicsNetwork.cpp \
    tileSources/CompositeTileSource.cpp \
    guts/MapTileLayerListModel.cpp \
    guts/MapTileSourceDelegate.cpp \
    guts/CompositeTileSourceConfigurationWidget.cpp \
    CircleObject.cpp \
    guts/PrivateQGraphicsInfoSource.cpp \
    PolygonObject.cpp \
    Position.cpp \
    LineObject.cpp \
    tileSources/SrtmGridTileSource.cpp \
    tileSources/KmlGridTileSource.cpp

HEADERS += MapGraphicsScene.h\
        MapGraphics_global.h \
    MapGraphicsObject.h \
    MapGraphicsView.h \
    guts/PrivateQGraphicsScene.h \
    guts/PrivateQGraphicsObject.h \
    guts/Conversions.h \
    MapTileSource.h \
    tileSources/GridTileSource.h \
    guts/MapTileGraphicsObject.h \
    guts/PrivateQGraphicsView.h \
    tileSources/MeteoGridTileSource.h \
    tileSources/OSMTileSource.h \
    guts/MapGraphicsNetwork.h \
    tileSources/CompositeTileSource.h \
    guts/MapTileLayerListModel.h \
    guts/MapTileSourceDelegate.h \
    guts/CompositeTileSourceConfigurationWidget.h \
    CircleObject.h \
    guts/PrivateQGraphicsInfoSource.h \
    PolygonObject.h \
    Position.h \
    LineObject.h \
    tileSources/SrtmGridTileSource.h \
    tileSources/KmlGridTileSource.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4F7F973
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MapGraphics.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    guts/CompositeTileSourceConfigurationWidget.ui

RESOURCES += \
    resources.qrc
