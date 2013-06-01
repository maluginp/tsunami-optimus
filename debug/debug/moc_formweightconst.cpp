/****************************************************************************
** Meta object code from reading C++ file 'formweightconst.h'
**
** Created: Sun 2. Jun 01:48:02 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formweightconst.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formweightconst.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormWeightConst[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   17,   16,   16, 0x08,
      90,   79,   16,   16, 0x08,
     137,  131,   16,   16, 0x08,
     168,   16,   16,   16, 0x08,
     186,  180,   16,   16, 0x08,
     218,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormWeightConst[] = {
    "FormWeightConst\0\0plot,mouse\0"
    "plottableClick(QCPAbstractPlottable*,QMouseEvent*)\0"
    "item,event\0itemClick(QCPAbstractItem*,QMouseEvent*)\0"
    "index\0weightsTableClick(QModelIndex)\0"
    "SaveGraph()\0point\0weightsTableContextMenu(QPoint)\0"
    "weightsTableSetValueAction()\0"
};

void FormWeightConst::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormWeightConst *_t = static_cast<FormWeightConst *>(_o);
        switch (_id) {
        case 0: _t->plottableClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 1: _t->itemClick((*reinterpret_cast< QCPAbstractItem*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 2: _t->weightsTableClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->SaveGraph(); break;
        case 4: _t->weightsTableContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->weightsTableSetValueAction(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormWeightConst::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormWeightConst::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormWeightConst,
      qt_meta_data_FormWeightConst, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormWeightConst::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormWeightConst::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormWeightConst::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormWeightConst))
        return static_cast<void*>(const_cast< FormWeightConst*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormWeightConst::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
