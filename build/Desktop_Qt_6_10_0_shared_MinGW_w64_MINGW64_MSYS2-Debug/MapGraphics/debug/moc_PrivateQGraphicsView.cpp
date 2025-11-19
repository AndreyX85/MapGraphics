/****************************************************************************
** Meta object code from reading C++ file 'PrivateQGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MapGraphics/guts/PrivateQGraphicsView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrivateQGraphicsView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20PrivateQGraphicsViewE_t {};
} // unnamed namespace

template <> constexpr inline auto PrivateQGraphicsView::qt_create_metaobjectdata<qt_meta_tag_ZN20PrivateQGraphicsViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PrivateQGraphicsView",
        "hadMouseDoubleClickEvent",
        "",
        "QMouseEvent*",
        "event",
        "hadMouseMoveEvent",
        "hadMousePressEvent",
        "hadMouseReleaseEvent",
        "hadContextMenuEvent",
        "QContextMenuEvent*",
        "hadWheelEvent",
        "QWheelEvent*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'hadMouseDoubleClickEvent'
        QtMocHelpers::SignalData<void(QMouseEvent *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'hadMouseMoveEvent'
        QtMocHelpers::SignalData<void(QMouseEvent *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'hadMousePressEvent'
        QtMocHelpers::SignalData<void(QMouseEvent *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'hadMouseReleaseEvent'
        QtMocHelpers::SignalData<void(QMouseEvent *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'hadContextMenuEvent'
        QtMocHelpers::SignalData<void(QContextMenuEvent *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 2 },
        }}),
        // Signal 'hadWheelEvent'
        QtMocHelpers::SignalData<void(QWheelEvent *)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PrivateQGraphicsView, qt_meta_tag_ZN20PrivateQGraphicsViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PrivateQGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PrivateQGraphicsViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PrivateQGraphicsViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20PrivateQGraphicsViewE_t>.metaTypes,
    nullptr
} };

void PrivateQGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PrivateQGraphicsView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->hadMouseDoubleClickEvent((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 1: _t->hadMouseMoveEvent((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 2: _t->hadMousePressEvent((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->hadMouseReleaseEvent((*reinterpret_cast<std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->hadContextMenuEvent((*reinterpret_cast<std::add_pointer_t<QContextMenuEvent*>>(_a[1]))); break;
        case 5: _t->hadWheelEvent((*reinterpret_cast<std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QMouseEvent * )>(_a, &PrivateQGraphicsView::hadMouseDoubleClickEvent, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QMouseEvent * )>(_a, &PrivateQGraphicsView::hadMouseMoveEvent, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QMouseEvent * )>(_a, &PrivateQGraphicsView::hadMousePressEvent, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QMouseEvent * )>(_a, &PrivateQGraphicsView::hadMouseReleaseEvent, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QContextMenuEvent * )>(_a, &PrivateQGraphicsView::hadContextMenuEvent, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PrivateQGraphicsView::*)(QWheelEvent * )>(_a, &PrivateQGraphicsView::hadWheelEvent, 5))
            return;
    }
}

const QMetaObject *PrivateQGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrivateQGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20PrivateQGraphicsViewE_t>.strings))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int PrivateQGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PrivateQGraphicsView::hadMouseDoubleClickEvent(QMouseEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void PrivateQGraphicsView::hadMouseMoveEvent(QMouseEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void PrivateQGraphicsView::hadMousePressEvent(QMouseEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PrivateQGraphicsView::hadMouseReleaseEvent(QMouseEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PrivateQGraphicsView::hadContextMenuEvent(QContextMenuEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void PrivateQGraphicsView::hadWheelEvent(QWheelEvent * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
