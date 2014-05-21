/****************************************************************************
** Meta object code from reading C++ file 'favoriteswindow.h'
**
** Created: Wed May 21 22:50:28 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "favoriteswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'favoriteswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_favoriteswindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_favoriteswindow[] = {
    "favoriteswindow\0\0view_friend()\0"
};

void favoriteswindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        favoriteswindow *_t = static_cast<favoriteswindow *>(_o);
        switch (_id) {
        case 0: _t->view_friend(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData favoriteswindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject favoriteswindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_favoriteswindow,
      qt_meta_data_favoriteswindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &favoriteswindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *favoriteswindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *favoriteswindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_favoriteswindow))
        return static_cast<void*>(const_cast< favoriteswindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int favoriteswindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
