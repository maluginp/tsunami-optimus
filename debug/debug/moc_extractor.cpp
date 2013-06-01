/****************************************************************************
** Meta object code from reading C++ file 'extractor.h'
**
** Created: Sun 2. Jun 01:48:01 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../core/extractor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extractor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Extractor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   11,   10,   10, 0x05,
      53,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Extractor[] = {
    "Extractor\0\0iteration,error\0"
    "doneIteration(int,double)\0doneMinimisation()\0"
    "Stop()\0"
};

void Extractor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Extractor *_t = static_cast<Extractor *>(_o);
        switch (_id) {
        case 0: _t->doneIteration((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->doneMinimisation(); break;
        case 2: _t->Stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Extractor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Extractor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Extractor,
      qt_meta_data_Extractor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Extractor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Extractor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Extractor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Extractor))
        return static_cast<void*>(const_cast< Extractor*>(this));
    return QObject::qt_metacast(_clname);
}

int Extractor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Extractor::doneIteration(int _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Extractor::doneMinimisation()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
