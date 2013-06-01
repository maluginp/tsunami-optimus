/****************************************************************************
** Meta object code from reading C++ file 'formmeasures.h'
**
** Created: Sun 2. Jun 01:47:59 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formmeasures.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formmeasures.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormMeasures[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   13,   13,   13, 0x08,
      57,   13,   13,   13, 0x08,
      83,   77,   13,   13, 0x08,
     110,   77,   13,   13, 0x08,
     137,   13,   13,   13, 0x08,
     151,   13,   13,   13, 0x08,
     169,   13,   13,   13, 0x08,
     188,   13,   13,   13, 0x08,
     205,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormMeasures[] = {
    "FormMeasures\0\0id\0acceptDataset(int)\0"
    "showEditorMeasures()\0updateDatasetList()\0"
    "index\0selectDataset(QModelIndex)\0"
    "selectMeasure(QModelIndex)\0clickAddSet()\0"
    "clickAddMeasure()\0clickEditMeasure()\0"
    "updateMeasures()\0clickAccept()\0"
};

void FormMeasures::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormMeasures *_t = static_cast<FormMeasures *>(_o);
        switch (_id) {
        case 0: _t->acceptDataset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->showEditorMeasures(); break;
        case 2: _t->updateDatasetList(); break;
        case 3: _t->selectDataset((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->selectMeasure((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->clickAddSet(); break;
        case 6: _t->clickAddMeasure(); break;
        case 7: _t->clickEditMeasure(); break;
        case 8: _t->updateMeasures(); break;
        case 9: _t->clickAccept(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormMeasures::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormMeasures::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FormMeasures,
      qt_meta_data_FormMeasures, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormMeasures::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormMeasures::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormMeasures::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormMeasures))
        return static_cast<void*>(const_cast< FormMeasures*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FormMeasures::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FormMeasures::acceptDataset(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
