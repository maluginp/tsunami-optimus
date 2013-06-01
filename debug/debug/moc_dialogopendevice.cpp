/****************************************************************************
** Meta object code from reading C++ file 'dialogopendevice.h'
**
** Created: Sun 2. Jun 00:26:23 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/dialogs/dialogopendevice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogopendevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogOpenDevice[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x08,
      47,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogOpenDevice[] = {
    "DialogOpenDevice\0\0index\0setDevice(QModelIndex)\0"
    "newDevice()\0"
};

void DialogOpenDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogOpenDevice *_t = static_cast<DialogOpenDevice *>(_o);
        switch (_id) {
        case 0: _t->setDevice((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->newDevice(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DialogOpenDevice::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogOpenDevice::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogOpenDevice,
      qt_meta_data_DialogOpenDevice, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogOpenDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogOpenDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogOpenDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogOpenDevice))
        return static_cast<void*>(const_cast< DialogOpenDevice*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogOpenDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
