/****************************************************************************
** Meta object code from reading C++ file 'editormeasures.h'
**
** Created: Sun 2. Jun 02:25:08 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/editormeasures.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editormeasures.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditorMeasures[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   15,   15,   15, 0x08,
      50,   15,   15,   15, 0x08,
      70,   64,   15,   15, 0x08,
     118,  113,   15,   15, 0x08,
     153,   15,   15,   15, 0x08,
     170,   15,   15,   15, 0x08,
     191,   15,   15,   15, 0x08,
     210,  205,   15,   15, 0x08,
     240,  234,   15,   15, 0x08,
     270,   15,   15,   15, 0x08,
     287,   15,   15,   15, 0x08,
     311,  305,   15,   15, 0x08,
     349,  338,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditorMeasures[] = {
    "EditorMeasures\0\0changeMeasures()\0"
    "clickAddColumn()\0clickAddRow()\0i1,i2\0"
    "changeDataMeasure(QModelIndex,QModelIndex)\0"
    "item\0changeDataConstant(QStandardItem*)\0"
    "replotGraphics()\0clickAddConstValue()\0"
    "saveMeasure()\0name\0changePlotType(QString)\0"
    "index\0selectConstValue(QModelIndex)\0"
    "importMeasures()\0copyToClipboard()\0"
    "event\0clickPlotter(QMouseEvent*)\0"
    "plot,mouse\0"
    "plottableClick(QCPAbstractPlottable*,QMouseEvent*)\0"
};

void EditorMeasures::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EditorMeasures *_t = static_cast<EditorMeasures *>(_o);
        switch (_id) {
        case 0: _t->changeMeasures(); break;
        case 1: _t->clickAddColumn(); break;
        case 2: _t->clickAddRow(); break;
        case 3: _t->changeDataMeasure((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 4: _t->changeDataConstant((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 5: _t->replotGraphics(); break;
        case 6: _t->clickAddConstValue(); break;
        case 7: _t->saveMeasure(); break;
        case 8: _t->changePlotType((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->selectConstValue((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 10: _t->importMeasures(); break;
        case 11: _t->copyToClipboard(); break;
        case 12: _t->clickPlotter((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 13: _t->plottableClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EditorMeasures::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EditorMeasures::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditorMeasures,
      qt_meta_data_EditorMeasures, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditorMeasures::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditorMeasures::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditorMeasures::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditorMeasures))
        return static_cast<void*>(const_cast< EditorMeasures*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditorMeasures::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void EditorMeasures::changeMeasures()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
