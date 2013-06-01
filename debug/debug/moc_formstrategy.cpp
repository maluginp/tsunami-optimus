/****************************************************************************
** Meta object code from reading C++ file 'formstrategy.h'
**
** Created: Sun 2. Jun 01:48:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formstrategy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formstrategy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormStrategy[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   13,   13,   13, 0x08,
      57,   51,   13,   13, 0x08,
      85,   13,   13,   13, 0x08,
      99,   13,   13,   13, 0x08,
     117,   13,   13,   13, 0x08,
     138,   51,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormStrategy[] = {
    "FormStrategy\0\0id\0acceptStrategy(int)\0"
    "newStrategy()\0index\0selectStrategy(QModelIndex)\0"
    "clickAccept()\0setWeightsCoeff()\0"
    "updateStrategyList()\0selectMeasure(QModelIndex)\0"
};

void FormStrategy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormStrategy *_t = static_cast<FormStrategy *>(_o);
        switch (_id) {
        case 0: _t->acceptStrategy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->newStrategy(); break;
        case 2: _t->selectStrategy((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->clickAccept(); break;
        case 4: _t->setWeightsCoeff(); break;
        case 5: _t->updateStrategyList(); break;
        case 6: _t->selectMeasure((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormStrategy::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormStrategy::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FormStrategy,
      qt_meta_data_FormStrategy, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormStrategy::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormStrategy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormStrategy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormStrategy))
        return static_cast<void*>(const_cast< FormStrategy*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FormStrategy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FormStrategy::acceptStrategy(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
