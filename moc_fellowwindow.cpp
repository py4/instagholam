/****************************************************************************
** Meta object code from reading C++ file 'fellowwindow.h'
**
** Created: Wed May 21 22:19:39 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fellowwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fellowwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_fellowwindow[] = {

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
      14,   13,   13,   13, 0x08,
      32,   13,   13,   13, 0x08,
      53,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_fellowwindow[] = {
    "fellowwindow\0\0approve_request()\0"
    "disapprove_request()\0request_to_friend()\0"
};

void fellowwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fellowwindow *_t = static_cast<fellowwindow *>(_o);
        switch (_id) {
        case 0: _t->approve_request(); break;
        case 1: _t->disapprove_request(); break;
        case 2: _t->request_to_friend(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData fellowwindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fellowwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_fellowwindow,
      qt_meta_data_fellowwindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fellowwindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fellowwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fellowwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fellowwindow))
        return static_cast<void*>(const_cast< fellowwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int fellowwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
