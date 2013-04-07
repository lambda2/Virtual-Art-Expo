/****************************************************************************
** Meta object code from reading C++ file 'paramsalledial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Sources/VAE/Dessin/paramsalledial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paramsalledial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ParamSalleDial_t {
    QByteArrayData data[27];
    char stringdata[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ParamSalleDial_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ParamSalleDial_t qt_meta_stringdata_ParamSalleDial = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 14),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 7),
QT_MOC_LITERAL(4, 39, 15),
QT_MOC_LITERAL(5, 55, 3),
QT_MOC_LITERAL(6, 59, 3),
QT_MOC_LITERAL(7, 63, 23),
QT_MOC_LITERAL(8, 87, 20),
QT_MOC_LITERAL(9, 108, 5),
QT_MOC_LITERAL(10, 114, 25),
QT_MOC_LITERAL(11, 140, 6),
QT_MOC_LITERAL(12, 147, 25),
QT_MOC_LITERAL(13, 173, 6),
QT_MOC_LITERAL(14, 180, 14),
QT_MOC_LITERAL(15, 195, 3),
QT_MOC_LITERAL(16, 199, 12),
QT_MOC_LITERAL(17, 212, 5),
QT_MOC_LITERAL(18, 218, 12),
QT_MOC_LITERAL(19, 231, 13),
QT_MOC_LITERAL(20, 245, 3),
QT_MOC_LITERAL(21, 249, 14),
QT_MOC_LITERAL(22, 264, 6),
QT_MOC_LITERAL(23, 271, 20),
QT_MOC_LITERAL(24, 292, 23),
QT_MOC_LITERAL(25, 316, 21),
QT_MOC_LITERAL(26, 338, 20)
    },
    "ParamSalleDial\0hauteurChangee\0\0hauteur\0"
    "sigListeChangee\0Sol\0ind\0sigActualiserMiniatures\0"
    "sigCheckAffImgChange\0check\0"
    "cheminTextureImageChangee\0chemin\0"
    "tailleTextureImageChangee\0taille\0"
    "spinboxChangee\0val\0listeChangee\0index\0"
    "reconfigurer\0afficherBarre\0aff\0"
    "setValeurBarre\0valeur\0actualiserMiniatures\0"
    "checkAffichageTabChange\0boutonParcourirPresse\0"
    "tailleTextureChangee\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParamSalleDial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x05,
       4,    1,   97,    2, 0x05,
       7,    0,  100,    2, 0x05,
       8,    1,  101,    2, 0x05,
      10,    1,  104,    2, 0x05,
      12,    1,  107,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      14,    1,  110,    2, 0x0a,
      16,    1,  113,    2, 0x0a,
      18,    0,  116,    2, 0x0a,
      19,    1,  117,    2, 0x0a,
      19,    0,  120,    2, 0x2a,
      21,    1,  121,    2, 0x0a,
      23,    0,  124,    2, 0x0a,
      24,    1,  125,    2, 0x0a,
      25,    0,  128,    2, 0x0a,
      26,    1,  129,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Double,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   13,

       0        // eod
};

void ParamSalleDial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParamSalleDial *_t = static_cast<ParamSalleDial *>(_o);
        switch (_id) {
        case 0: _t->hauteurChangee((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->sigListeChangee((*reinterpret_cast< Sol(*)>(_a[1]))); break;
        case 2: _t->sigActualiserMiniatures(); break;
        case 3: _t->sigCheckAffImgChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->cheminTextureImageChangee((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->tailleTextureImageChangee((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->spinboxChangee((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->listeChangee((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->reconfigurer(); break;
        case 9: _t->afficherBarre((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->afficherBarre(); break;
        case 11: _t->setValeurBarre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->actualiserMiniatures(); break;
        case 13: _t->checkAffichageTabChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->boutonParcourirPresse(); break;
        case 15: _t->tailleTextureChangee((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParamSalleDial::*_t)(qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::hauteurChangee)) {
                *result = 0;
            }
        }
        {
            typedef void (ParamSalleDial::*_t)(Sol );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::sigListeChangee)) {
                *result = 1;
            }
        }
        {
            typedef void (ParamSalleDial::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::sigActualiserMiniatures)) {
                *result = 2;
            }
        }
        {
            typedef void (ParamSalleDial::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::sigCheckAffImgChange)) {
                *result = 3;
            }
        }
        {
            typedef void (ParamSalleDial::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::cheminTextureImageChangee)) {
                *result = 4;
            }
        }
        {
            typedef void (ParamSalleDial::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParamSalleDial::tailleTextureImageChangee)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject ParamSalleDial::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParamSalleDial.data,
      qt_meta_data_ParamSalleDial,  qt_static_metacall, 0, 0}
};


const QMetaObject *ParamSalleDial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParamSalleDial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParamSalleDial.stringdata))
        return static_cast<void*>(const_cast< ParamSalleDial*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParamSalleDial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ParamSalleDial::hauteurChangee(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParamSalleDial::sigListeChangee(Sol _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParamSalleDial::sigActualiserMiniatures()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ParamSalleDial::sigCheckAffImgChange(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ParamSalleDial::cheminTextureImageChangee(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ParamSalleDial::tailleTextureImageChangee(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
