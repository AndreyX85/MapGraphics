/****************************************************************************
** Meta object code from reading C++ file 'MapGraphicsObject.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MapGraphics/MapGraphicsObject.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapGraphicsObject.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17MapGraphicsObjectE_t {};
} // unnamed namespace

template <> constexpr inline auto MapGraphicsObject::qt_create_metaobjectdata<qt_meta_tag_ZN17MapGraphicsObjectE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MapGraphicsObject",
        "enabledChanged",
        "",
        "opacityChanged",
        "parentChanged",
        "posChanged",
        "rotationChanged",
        "visibleChanged",
        "zValueChanged",
        "toolTipChanged",
        "toolTip",
        "flagsChanged",
        "selectedChanged",
        "newObjectGenerated",
        "MapGraphicsObject*",
        "redrawRequested",
        "keyFocusRequested",
        "setConstructed"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'enabledChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'opacityChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'parentChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'posChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'rotationChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'visibleChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'zValueChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'toolTipChanged'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Signal 'flagsChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'newObjectGenerated'
        QtMocHelpers::SignalData<void(MapGraphicsObject *)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 2 },
        }}),
        // Signal 'redrawRequested'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'keyFocusRequested'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setConstructed'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MapGraphicsObject, qt_meta_tag_ZN17MapGraphicsObjectE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MapGraphicsObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17MapGraphicsObjectE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17MapGraphicsObjectE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17MapGraphicsObjectE_t>.metaTypes,
    nullptr
} };

void MapGraphicsObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MapGraphicsObject *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->enabledChanged(); break;
        case 1: _t->opacityChanged(); break;
        case 2: _t->parentChanged(); break;
        case 3: _t->posChanged(); break;
        case 4: _t->rotationChanged(); break;
        case 5: _t->visibleChanged(); break;
        case 6: _t->zValueChanged(); break;
        case 7: _t->toolTipChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->flagsChanged(); break;
        case 9: _t->selectedChanged(); break;
        case 10: _t->newObjectGenerated((*reinterpret_cast<std::add_pointer_t<MapGraphicsObject*>>(_a[1]))); break;
        case 11: _t->redrawRequested(); break;
        case 12: _t->keyFocusRequested(); break;
        case 13: _t->setConstructed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MapGraphicsObject* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::enabledChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::opacityChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::parentChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::posChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::rotationChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::visibleChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::zValueChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)(const QString & )>(_a, &MapGraphicsObject::toolTipChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::flagsChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::selectedChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)(MapGraphicsObject * )>(_a, &MapGraphicsObject::newObjectGenerated, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::redrawRequested, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (MapGraphicsObject::*)()>(_a, &MapGraphicsObject::keyFocusRequested, 12))
            return;
    }
}

const QMetaObject *MapGraphicsObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapGraphicsObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17MapGraphicsObjectE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapGraphicsObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MapGraphicsObject::enabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MapGraphicsObject::opacityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MapGraphicsObject::parentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MapGraphicsObject::posChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MapGraphicsObject::rotationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MapGraphicsObject::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MapGraphicsObject::zValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MapGraphicsObject::toolTipChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void MapGraphicsObject::flagsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MapGraphicsObject::selectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MapGraphicsObject::newObjectGenerated(MapGraphicsObject * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void MapGraphicsObject::redrawRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MapGraphicsObject::keyFocusRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
