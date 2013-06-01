/****************************************************************************
** Meta object code from reading C++ file 'deviceworkspace.h'
**
** Created: Sun 2. Jun 01:47:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../deviceworkspace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceworkspace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeviceWorkspace[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   16,   16,   16, 0x08,
      49,   16,   16,   16, 0x08,
      71,   16,   16,   16, 0x08,
      96,   16,   16,   16, 0x08,
     110,   16,   16,   16, 0x08,
     127,   16,   16,   16, 0x08,
     146,   16,   16,   16, 0x08,
     167,   16,   16,   16, 0x08,
     186,   16,   16,   16, 0x08,
     205,   16,   16,   16, 0x08,
     223,   16,   16,   16, 0x08,
     239,   16,   16,   16, 0x08,
     260,  257,   16,   16, 0x08,
     280,  257,   16,   16, 0x08,
     303,  257,   16,   16, 0x08,
     330,  257,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DeviceWorkspace[] = {
    "DeviceWorkspace\0\0reload()\0"
    "showDialogOpenDevice()\0showDialogNewDevice()\0"
    "showDialogRemoveDevice()\0closeDevice()\0"
    "showFormModels()\0showFormGraphics()\0"
    "showFormParameters()\0showFormMeasures()\0"
    "showFormStrategy()\0showFormSetting()\0"
    "runExtraction()\0reloadWorkspace()\0id\0"
    "slotSetModelID(int)\0slotSetStrategyID(int)\0"
    "slotSetParameterSetID(int)\0"
    "slotSetDataset(int)\0"
};

void DeviceWorkspace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DeviceWorkspace *_t = static_cast<DeviceWorkspace *>(_o);
        switch (_id) {
        case 0: _t->reload(); break;
        case 1: _t->showDialogOpenDevice(); break;
        case 2: _t->showDialogNewDevice(); break;
        case 3: _t->showDialogRemoveDevice(); break;
        case 4: _t->closeDevice(); break;
        case 5: _t->showFormModels(); break;
        case 6: _t->showFormGraphics(); break;
        case 7: _t->showFormParameters(); break;
        case 8: _t->showFormMeasures(); break;
        case 9: _t->showFormStrategy(); break;
        case 10: _t->showFormSetting(); break;
        case 11: _t->runExtraction(); break;
        case 12: _t->reloadWorkspace(); break;
        case 13: _t->slotSetModelID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slotSetStrategyID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slotSetParameterSetID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slotSetDataset((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DeviceWorkspace::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DeviceWorkspace::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DeviceWorkspace,
      qt_meta_data_DeviceWorkspace, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DeviceWorkspace::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DeviceWorkspace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DeviceWorkspace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceWorkspace))
        return static_cast<void*>(const_cast< DeviceWorkspace*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DeviceWorkspace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void DeviceWorkspace::reload()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
