/****************************************************************************
** Meta object code from reading C++ file 'clickableimage.h'
**
** Created: Sat May 17 21:08:27 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clickableimage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clickableimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClickableImage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,
      58,   16,   15,   15, 0x05,
      94,   16,   15,   15, 0x05,
     131,   16,   15,   15, 0x05,
     167,   16,   15,   15, 0x05,
     204,   16,   15,   15, 0x05,
     242,   16,   15,   15, 0x05,
     272,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ClickableImage[] = {
    "ClickableImage\0\0sender\0"
    "leftButtonPressed(ClickableImage*)\0"
    "rightButtonPressed(ClickableImage*)\0"
    "middleButtonPressed(ClickableImage*)\0"
    "leftButtonReleased(ClickableImage*)\0"
    "rightButtonReleased(ClickableImage*)\0"
    "middleButtonReleased(ClickableImage*)\0"
    "mouseEntered(ClickableImage*)\0"
    "mouseLeft(ClickableImage*)\0"
};

void ClickableImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClickableImage *_t = static_cast<ClickableImage *>(_o);
        switch (_id) {
        case 0: _t->leftButtonPressed((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 1: _t->rightButtonPressed((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 2: _t->middleButtonPressed((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 3: _t->leftButtonReleased((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 4: _t->rightButtonReleased((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 5: _t->middleButtonReleased((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 6: _t->mouseEntered((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        case 7: _t->mouseLeft((*reinterpret_cast< ClickableImage*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClickableImage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClickableImage::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ClickableImage,
      qt_meta_data_ClickableImage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClickableImage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClickableImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClickableImage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClickableImage))
        return static_cast<void*>(const_cast< ClickableImage*>(this));
    return QLabel::qt_metacast(_clname);
}

int ClickableImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ClickableImage::leftButtonPressed(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClickableImage::rightButtonPressed(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClickableImage::middleButtonPressed(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClickableImage::leftButtonReleased(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClickableImage::rightButtonReleased(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClickableImage::middleButtonReleased(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClickableImage::mouseEntered(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClickableImage::mouseLeft(ClickableImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
