/****************************************************************************
** Meta object code from reading C++ file 'echelle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Sources/VAE/Dessin/echelle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'echelle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Echelle_t {
    QByteArrayData data[6];
    char stringdata[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Echelle_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Echelle_t qt_meta_stringdata_Echelle = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 9),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 10),
QT_MOC_LITERAL(4, 30, 4),
QT_MOC_LITERAL(5, 35, 10)
    },
    "Echelle\0onRepeint\0\0majEchelle\0coef\0"
    "getEchelle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Echelle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a,
       5,    0,   33,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    4,
    QMetaType::QReal,

       0        // eod
};

void Echelle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Echelle *_t = static_cast<Echelle *>(_o);
        switch (_id) {
        case 0: _t->onRepeint(); break;
        case 1: _t->majEchelle((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: { qreal _r = _t->getEchelle();
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Echelle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Echelle::onRepeint)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Echelle::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Echelle.data,
      qt_meta_data_Echelle,  qt_static_metacall, 0, 0}
};


const QMetaObject *Echelle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Echelle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Echelle.stringdata))
        return static_cast<void*>(const_cast< Echelle*>(this));
    return QWidget::qt_metacast(_clname);
}

int Echelle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Echelle::onRepeint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
