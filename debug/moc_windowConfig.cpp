/****************************************************************************
** Meta object code from reading C++ file 'windowConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../windowConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_windowConfig_t {
    QByteArrayData data[8];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_windowConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_windowConfig_t qt_meta_stringdata_windowConfig = {
    {
QT_MOC_LITERAL(0, 0, 12), // "windowConfig"
QT_MOC_LITERAL(1, 13, 14), // "CDCONF_network"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "LoadConf"
QT_MOC_LITERAL(4, 38, 25), // "createDefaultCONF_network"
QT_MOC_LITERAL(5, 64, 24), // "createDefaultCONF_system"
QT_MOC_LITERAL(6, 89, 12), // "loadCONF_net"
QT_MOC_LITERAL(7, 102, 12) // "saveCONF_net"

    },
    "windowConfig\0CDCONF_network\0\0LoadConf\0"
    "createDefaultCONF_network\0"
    "createDefaultCONF_system\0loadCONF_net\0"
    "saveCONF_net"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_windowConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void windowConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        windowConfig *_t = static_cast<windowConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CDCONF_network(); break;
        case 1: _t->LoadConf(); break;
        case 2: _t->createDefaultCONF_network(); break;
        case 3: _t->createDefaultCONF_system(); break;
        case 4: _t->loadCONF_net(); break;
        case 5: _t->saveCONF_net(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (windowConfig::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&windowConfig::CDCONF_network)) {
                *result = 0;
            }
        }
        {
            typedef void (windowConfig::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&windowConfig::LoadConf)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject windowConfig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_windowConfig.data,
      qt_meta_data_windowConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *windowConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *windowConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_windowConfig.stringdata0))
        return static_cast<void*>(const_cast< windowConfig*>(this));
    return QWidget::qt_metacast(_clname);
}

int windowConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void windowConfig::CDCONF_network()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void windowConfig::LoadConf()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
