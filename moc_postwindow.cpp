/****************************************************************************
** Meta object code from reading C++ file 'postwindow.h'
**
** Created: Wed May 21 22:50:29 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "postwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'postwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PostWindow[] = {

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
      12,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PostWindow[] = {
    "PostWindow\0\0on_show_comment_button_clicked()\0"
    "on_show_favorites_button_clicked()\0"
    "on_liked_button_clicked()\0"
};

void PostWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PostWindow *_t = static_cast<PostWindow *>(_o);
        switch (_id) {
        case 0: _t->on_show_comment_button_clicked(); break;
        case 1: _t->on_show_favorites_button_clicked(); break;
        case 2: _t->on_liked_button_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PostWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PostWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PostWindow,
      qt_meta_data_PostWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PostWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PostWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PostWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PostWindow))
        return static_cast<void*>(const_cast< PostWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PostWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
