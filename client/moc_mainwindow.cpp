/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed May 28 20:27:13 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
     113,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     176,  170,   11,   11, 0x08,
     209,   11,   11,   11, 0x08,
     229,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     269,   11,   11,   11, 0x08,
     287,   11,   11,   11, 0x08,
     308,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_sign_in_clicked()\0"
    "on_select_avatar_clicked()\0"
    "on_register_button_clicked()\0"
    "on_register_2_clicked()\0"
    "on_share_button_clicked()\0"
    "on_share_select_file_clicked()\0index\0"
    "on_tabWidget_currentChanged(int)\0"
    "show_clicked_post()\0show_post()\0"
    "on_actionLogout_triggered()\0"
    "approve_request()\0disapprove_request()\0"
    "on_refresh_button_clicked()\0"
    "render_admin_window()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_sign_in_clicked(); break;
        case 1: _t->on_select_avatar_clicked(); break;
        case 2: _t->on_register_button_clicked(); break;
        case 3: _t->on_register_2_clicked(); break;
        case 4: _t->on_share_button_clicked(); break;
        case 5: _t->on_share_select_file_clicked(); break;
        case 6: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->show_clicked_post(); break;
        case 8: _t->show_post(); break;
        case 9: _t->on_actionLogout_triggered(); break;
        case 10: _t->approve_request(); break;
        case 11: _t->disapprove_request(); break;
        case 12: _t->on_refresh_button_clicked(); break;
        case 13: _t->render_admin_window(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
