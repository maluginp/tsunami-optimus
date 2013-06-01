/****************************************************************************
** Meta object code from reading C++ file 'formparameters.h'
**
** Created: Sun 2. Jun 01:00:06 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formparameters.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formparameters.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormParameters[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x05,
      59,   56,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      94,   81,   15,   15, 0x08,
     123,   15,   15,   15, 0x08,
     137,   15,   15,   15, 0x08,
     154,   15,   15,   15, 0x08,
     167,   15,   15,   15, 0x08,
     181,   15,   15,   15, 0x08,
     195,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormParameters[] = {
    "FormParameters\0\0name,id\0"
    "updateParameterSet(QString,int)\0id\0"
    "acceptParameters(int)\0parameterSet\0"
    "changeParameterSets(QString)\0clickBtnAdd()\0"
    "clickBtnRemove()\0clickApply()\0"
    "clickCancel()\0clickAddSet()\0"
    "clickSaveTemplate()\0"
};

void FormParameters::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormParameters *_t = static_cast<FormParameters *>(_o);
        switch (_id) {
        case 0: _t->updateParameterSet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->acceptParameters((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeParameterSets((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->clickBtnAdd(); break;
        case 4: _t->clickBtnRemove(); break;
        case 5: _t->clickApply(); break;
        case 6: _t->clickCancel(); break;
        case 7: _t->clickAddSet(); break;
        case 8: _t->clickSaveTemplate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormParameters::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormParameters::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FormParameters,
      qt_meta_data_FormParameters, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormParameters::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormParameters::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormParameters::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormParameters))
        return static_cast<void*>(const_cast< FormParameters*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FormParameters::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FormParameters::updateParameterSet(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FormParameters::acceptParameters(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
