/****************************************************************************
** Meta object code from reading C++ file 'cltransudp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cltransudp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cltransudp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_clTransUDP_t {
    QByteArrayData data[5];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_clTransUDP_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_clTransUDP_t qt_meta_stringdata_clTransUDP = {
    {
QT_MOC_LITERAL(0, 0, 10), // "clTransUDP"
QT_MOC_LITERAL(1, 11, 10), // "readAnswer"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "readTransaction"
QT_MOC_LITERAL(4, 39, 5) // "lauch"

    },
    "clTransUDP\0readAnswer\0\0readTransaction\0"
    "lauch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_clTransUDP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       4,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,

       0        // eod
};

void clTransUDP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        clTransUDP *_t = static_cast<clTransUDP *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readAnswer(); break;
        case 1: _t->readTransaction((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->lauch(); break;
        default: ;
        }
    }
}

const QMetaObject clTransUDP::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_clTransUDP.data,
      qt_meta_data_clTransUDP,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *clTransUDP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clTransUDP::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_clTransUDP.stringdata0))
        return static_cast<void*>(const_cast< clTransUDP*>(this));
    return QThread::qt_metacast(_clname);
}

int clTransUDP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
