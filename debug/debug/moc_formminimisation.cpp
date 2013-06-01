/****************************************************************************
** Meta object code from reading C++ file 'formminimisation.h'
**
** Created: Sun 2. Jun 01:47:59 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/formminimisation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formminimisation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FormMinimisation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   17,   17,   17, 0x08,
      69,   53,   17,   17, 0x08,
      95,   17,   17,   17, 0x08,
     114,   17,   17,   17, 0x08,
     144,  133,   17,   17, 0x08,
     181,   17,   17,   17, 0x08,
     198,   17,   17,   17, 0x08,
     212,   17,   17,   17, 0x08,
     227,   17,   17,   17, 0x08,
     261,  245,   17,   17, 0x08,
     328,  324,   17,   17, 0x08,
     366,  358,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FormMinimisation[] = {
    "FormMinimisation\0\0stopExtraction()\0"
    "startExtraction()\0iteration,error\0"
    "doneIteration(int,double)\0stopMinimisation()\0"
    "doneMinimisation()\0parameters\0"
    "replotGraphics(QMap<QString,double>)\0"
    "saveParameters()\0saveGraphic()\0"
    "timerTimeout()\0copyToClipboard()\0"
    "axis,part,event\0"
    "axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)\0"
    "pos\0parametersContextMenu(QPoint)\0"
    "graph,e\0plottableClick(QCPAbstractPlottable*,QMouseEvent*)\0"
};

void FormMinimisation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormMinimisation *_t = static_cast<FormMinimisation *>(_o);
        switch (_id) {
        case 0: _t->stopExtraction(); break;
        case 1: _t->startExtraction(); break;
        case 2: _t->doneIteration((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->stopMinimisation(); break;
        case 4: _t->doneMinimisation(); break;
        case 5: _t->replotGraphics((*reinterpret_cast< QMap<QString,double>(*)>(_a[1]))); break;
        case 6: _t->saveParameters(); break;
        case 7: _t->saveGraphic(); break;
        case 8: _t->timerTimeout(); break;
        case 9: _t->copyToClipboard(); break;
        case 10: _t->axisDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 11: _t->parametersContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 12: _t->plottableClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FormMinimisation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FormMinimisation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FormMinimisation,
      qt_meta_data_FormMinimisation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FormMinimisation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FormMinimisation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FormMinimisation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormMinimisation))
        return static_cast<void*>(const_cast< FormMinimisation*>(this));
    return QDialog::qt_metacast(_clname);
}

int FormMinimisation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void FormMinimisation::stopExtraction()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
