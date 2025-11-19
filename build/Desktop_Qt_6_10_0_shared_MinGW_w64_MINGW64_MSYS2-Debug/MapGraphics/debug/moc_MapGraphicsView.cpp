/****************************************************************************
** Meta object code from reading C++ file 'MapGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MapGraphics/MapGraphicsView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15MapGraphicsViewE_t {};
} // unnamed namespace

template <> constexpr inline auto MapGraphicsView::qt_create_metaobjectdata<qt_meta_tag_ZN15MapGraphicsViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MapGraphicsView",
        "zoomLevelChanged",
        "",
        "nZoom",
        "mouseClickedLL",
        "QPointF",
        "ll",
        "QPoint",
        "globalPos",
        "handleChildMouseDoubleClick",
        "QMouseEvent*",
        "event",
        "handleChildMouseMove",
        "handleChildMousePress",
        "handleChildMouseRelease",
        "handleChildViewContextMenu",
        "QContextMenuEvent*",
        "handleChildViewScrollWheel",
        "QWheelEvent*",
        "renderTiles"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'zoomLevelChanged'
        QtMocHelpers::SignalData<void(quint8)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 3 },
        }}),
        // Signal 'mouseClickedLL'
        QtMocHelpers::SignalData<void(const QPointF &, const QPoint &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { 0x80000000 | 7, 8 },
        }}),
        // Slot 'handleChildMouseDoubleClick'
        QtMocHelpers::SlotData<void(QMouseEvent *)>(9, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'handleChildMouseMove'
        QtMocHelpers::SlotData<void(QMouseEvent *)>(12, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'handleChildMousePress'
        QtMocHelpers::SlotData<void(QMouseEvent *)>(13, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'handleChildMouseRelease'
        QtMocHelpers::SlotData<void(QMouseEvent *)>(14, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'handleChildViewContextMenu'
        QtMocHelpers::SlotData<void(QContextMenuEvent *)>(15, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 16, 11 },
        }}),
        // Slot 'handleChildViewScrollWheel'
        QtMocHelpers::SlotData<void(QWheelEvent *)>(17, 2, QMC::AccessProtected, QMetaType::Void, {{
            { 0x80000000 | 18, 11 },
        }}),
        // Slot 'renderTiles'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MapGraphicsView, qt_meta_tag_ZN15MapGraphicsViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MapGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15MapGraphicsViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15MapGraphicsViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15MapGraphicsViewE_t>.metaTypes,
    nullptr
} };

void MapGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MapGraphicsView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->zoomLevelChanged((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1]))); break;
        case 1: _t->mouseClickedLL((*reinterpret_cast<std::add_pointer_t<QPointF>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[2]))); break;
        case 2: _t->handleChildMouseDoubleClick((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->handleChildMouseMove((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->handleChildMousePress((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 5: _t->handleChildMouseRelease((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 6: _t->handleChildViewContextMenu((*reinterpret_cast<std::add_pointer_t<QContextMenuEvent*>>(_a[1]))); break;
        case 7: _t->handleChildViewScrollWheel((*reinterpret_cast<std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 8: _t->renderTiles(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsView::*)(quint8 )>(_a, &MapGraphicsView::zoomLevelChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsView::*)(const QPointF & , const QPoint & )>(_a, &MapGraphicsView::mouseClickedLL, 1))
            return;
    }
}

const QMetaObject *MapGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15MapGraphicsViewE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PrivateQGraphicsInfoSource"))
        return static_cast< PrivateQGraphicsInfoSource*>(this);
    return QWidget::qt_metacast(_clname);
}

int MapGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MapGraphicsView::zoomLevelChanged(quint8 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MapGraphicsView::mouseClickedLL(const QPointF & _t1, const QPoint & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
