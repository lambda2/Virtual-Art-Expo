/****************************************************************************
** Meta object code from reading C++ file 'vueface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Sources/VAE/Dessin/vueface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vueface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VueFace_t {
    QByteArrayData data[27];
    char stringdata[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VueFace_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VueFace_t qt_meta_stringdata_VueFace = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 13),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 15),
QT_MOC_LITERAL(4, 39, 10),
QT_MOC_LITERAL(5, 50, 8),
QT_MOC_LITERAL(6, 59, 14),
QT_MOC_LITERAL(7, 74, 13),
QT_MOC_LITERAL(8, 88, 4),
QT_MOC_LITERAL(9, 93, 3),
QT_MOC_LITERAL(10, 97, 17),
QT_MOC_LITERAL(11, 115, 7),
QT_MOC_LITERAL(12, 123, 4),
QT_MOC_LITERAL(13, 128, 4),
QT_MOC_LITERAL(14, 133, 7),
QT_MOC_LITERAL(15, 141, 7),
QT_MOC_LITERAL(16, 149, 23),
QT_MOC_LITERAL(17, 173, 10),
QT_MOC_LITERAL(18, 184, 7),
QT_MOC_LITERAL(19, 192, 10),
QT_MOC_LITERAL(20, 203, 7),
QT_MOC_LITERAL(21, 211, 9),
QT_MOC_LITERAL(22, 221, 6),
QT_MOC_LITERAL(23, 228, 8),
QT_MOC_LITERAL(24, 237, 5),
QT_MOC_LITERAL(25, 243, 23),
QT_MOC_LITERAL(26, 267, 23)
    },
    "VueFace\0rouletteAvant\0\0rouletteArriere\0"
    "emitheight\0Tableau*\0tableauModifie\0"
    "setMurCourant\0Mur*\0mur\0enleverMurCourant\0"
    "setMode\0Mode\0mode\0setCoin\0CoinTab\0"
    "supprimerTableauxSelect\0setHauteur\0"
    "hauteur\0setLargeur\0largeur\0setHeight\0"
    "height\0setWidth\0width\0unTableauEstSelectionne\0"
    "aucunTableauSelectionne\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VueFace[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x05,
       3,    0,   95,    2, 0x05,
       4,    2,   96,    2, 0x05,
       6,    0,  101,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    1,  102,    2, 0x0a,
       7,    0,  105,    2, 0x2a,
      10,    0,  106,    2, 0x0a,
      11,    1,  107,    2, 0x0a,
      14,    1,  110,    2, 0x0a,
      16,    0,  113,    2, 0x0a,
      17,    1,  114,    2, 0x08,
      19,    1,  117,    2, 0x08,
      21,    1,  120,    2, 0x08,
      23,    1,  123,    2, 0x08,
      25,    0,  126,    2, 0x08,
      26,    0,  127,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Double,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Double,   20,
    QMetaType::Void, QMetaType::Double,   22,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VueFace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VueFace *_t = static_cast<VueFace *>(_o);
        switch (_id) {
        case 0: _t->rouletteAvant(); break;
        case 1: _t->rouletteArriere(); break;
        case 2: _t->emitheight((*reinterpret_cast< Tableau*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->tableauModifie(); break;
        case 4: _t->setMurCourant((*reinterpret_cast< Mur*(*)>(_a[1]))); break;
        case 5: _t->setMurCourant(); break;
        case 6: _t->enleverMurCourant(); break;
        case 7: _t->setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 8: _t->setCoin((*reinterpret_cast< CoinTab(*)>(_a[1]))); break;
        case 9: _t->supprimerTableauxSelect(); break;
        case 10: _t->setHauteur((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setLargeur((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setHeight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setWidth((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->unTableauEstSelectionne(); break;
        case 15: _t->aucunTableauSelectionne(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VueFace::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VueFace::rouletteAvant)) {
                *result = 0;
            }
        }
        {
            typedef void (VueFace::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VueFace::rouletteArriere)) {
                *result = 1;
            }
        }
        {
            typedef void (VueFace::*_t)(Tableau * , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VueFace::emitheight)) {
                *result = 2;
            }
        }
        {
            typedef void (VueFace::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VueFace::tableauModifie)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject VueFace::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_VueFace.data,
      qt_meta_data_VueFace,  qt_static_metacall, 0, 0}
};


const QMetaObject *VueFace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VueFace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VueFace.stringdata))
        return static_cast<void*>(const_cast< VueFace*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int VueFace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void VueFace::rouletteAvant()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VueFace::rouletteArriere()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VueFace::emitheight(Tableau * _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VueFace::tableauModifie()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
