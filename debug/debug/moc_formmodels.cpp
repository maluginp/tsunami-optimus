/****************************************************************************
** Meta object code from reading C++ file 'formmodels.h'
**
** Created: Sun 2. Jun 00:26:20 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formmodels.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formmodels.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormModels[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   11,   11,   11, 0x08,
      56,   51,   11,   11, 0x08,
      83,   77,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormModels[] = {
    "FormModels\0\0id\0acceptModel(int)\0"
    "updateListModels()\0name\0applyFilter(QString)\0"
    "index\0changeIndexListModels(QModelIndex)\0"
    "clickAccept()\0"
};

void FormModels::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormModels *_t = static_cast<FormModels *>(_o);
        switch (_id) {
        case 0: _t->acceptModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateListModels(); break;
        case 2: _t->applyFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changeIndexListModels((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->clickAccept(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormModels::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormModels::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FormModels,
      qt_meta_data_FormModels, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormModels::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormModels::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormModels::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormModels))
        return static_cast<void*>(const_cast< FormModels*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FormModels::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FormModels::acceptModel(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
