/****************************************************************************
** Meta object code from reading C++ file 'dialogdeletedevices.h'
**
** Created: Sun 2. Jun 00:26:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/dialogs/dialogdeletedevices.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogdeletedevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogDeleteDevices[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      42,   20,   20,   20, 0x08,
      65,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogDeleteDevices[] = {
    "DialogDeleteDevices\0\0appendToRemoveList()\0"
    "removeFromRemoveList()\0removeButtonClicked()\0"
};

void DialogDeleteDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogDeleteDevices *_t = static_cast<DialogDeleteDevices *>(_o);
        switch (_id) {
        case 0: _t->appendToRemoveList(); break;
        case 1: _t->removeFromRemoveList(); break;
        case 2: _t->removeButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DialogDeleteDevices::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogDeleteDevices::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogDeleteDevices,
      qt_meta_data_DialogDeleteDevices, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogDeleteDevices::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogDeleteDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogDeleteDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogDeleteDevices))
        return static_cast<void*>(const_cast< DialogDeleteDevices*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogDeleteDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
