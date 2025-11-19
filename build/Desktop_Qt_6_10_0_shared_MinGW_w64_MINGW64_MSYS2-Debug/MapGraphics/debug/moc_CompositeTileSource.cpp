/****************************************************************************
** Meta object code from reading C++ file 'CompositeTileSource.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../MapGraphics/tileSources/CompositeTileSource.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CompositeTileSource.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19CompositeTileSourceE_t {};
} // unnamed namespace

template <> constexpr inline auto CompositeTileSource::qt_create_metaobjectdata<qt_meta_tag_ZN19CompositeTileSourceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CompositeTileSource",
        "sourcesChanged",
        "",
        "sourceAdded",
        "index",
        "sourceRemoved",
        "sourcesReordered",
        "handleTileRetrieved",
        "x",
        "y",
        "z",
        "clearPendingTiles"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sourcesChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sourceAdded'
        QtMocHelpers::SignalData<void(int)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Signal 'sourceRemoved'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 },
        }}),
        // Signal 'sourcesReordered'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleTileRetrieved'
        QtMocHelpers::SlotData<void(quint32, quint32, quint8)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::UInt, 8 }, { QMetaType::UInt, 9 }, { QMetaType::UChar, 10 },
        }}),
        // Slot 'clearPendingTiles'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CompositeTileSource, qt_meta_tag_ZN19CompositeTileSourceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CompositeTileSource::staticMetaObject = { {
    QMetaObject::SuperData::link<MapTileSource::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CompositeTileSourceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CompositeTileSourceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19CompositeTileSourceE_t>.metaTypes,
    nullptr
} };

void CompositeTileSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CompositeTileSource *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sourcesChanged(); break;
        case 1: _t->sourceAdded((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->sourceRemoved((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->sourcesReordered(); break;
        case 4: _t->handleTileRetrieved((*reinterpret_cast<std::add_pointer_t<quint32>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[3]))); break;
        case 5: _t->clearPendingTiles(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CompositeTileSource::*)()>(_a, &CompositeTileSource::sourcesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompositeTileSource::*)(int )>(_a, &CompositeTileSource::sourceAdded, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompositeTileSource::*)(int )>(_a, &CompositeTileSource::sourceRemoved, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompositeTileSource::*)()>(_a, &CompositeTileSource::sourcesReordered, 3))
            return;
    }
}

const QMetaObject *CompositeTileSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompositeTileSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19CompositeTileSourceE_t>.strings))
        return static_cast<void*>(this);
    return MapTileSource::qt_metacast(_clname);
}

int CompositeTileSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MapTileSource::qt_metacall(_c, _id, _a);
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
void CompositeTileSource::sourcesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CompositeTileSource::sourceAdded(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void CompositeTileSource::sourceRemoved(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void CompositeTileSource::sourcesReordered()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
