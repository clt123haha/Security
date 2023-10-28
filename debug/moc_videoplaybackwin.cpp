/****************************************************************************
** Meta object code from reading C++ file 'videoplaybackwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/videoplaybackwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplaybackwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoPlaybackWin_t {
    QByteArrayData data[13];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlaybackWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlaybackWin_t qt_meta_stringdata_VideoPlaybackWin = {
    {
QT_MOC_LITERAL(0, 0, 16), // "VideoPlaybackWin"
QT_MOC_LITERAL(1, 17, 11), // "closePlayer"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "back"
QT_MOC_LITERAL(4, 35, 7), // "forward"
QT_MOC_LITERAL(5, 43, 8), // "forward2"
QT_MOC_LITERAL(6, 52, 10), // "changedata"
QT_MOC_LITERAL(7, 63, 11), // "changeIndex"
QT_MOC_LITERAL(8, 75, 1), // "i"
QT_MOC_LITERAL(9, 77, 9), // "palyVideo"
QT_MOC_LITERAL(10, 87, 18), // "showCalendarWidget"
QT_MOC_LITERAL(11, 106, 10), // "videoUpOne"
QT_MOC_LITERAL(12, 117, 12) // "videoDownOne"

    },
    "VideoPlaybackWin\0closePlayer\0\0back\0"
    "forward\0forward2\0changedata\0changeIndex\0"
    "i\0palyVideo\0showCalendarWidget\0"
    "videoUpOne\0videoDownOne"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlaybackWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    1,   69,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoPlaybackWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoPlaybackWin *_t = static_cast<VideoPlaybackWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closePlayer(); break;
        case 1: _t->back(); break;
        case 2: _t->forward(); break;
        case 3: _t->forward2(); break;
        case 4: _t->changedata(); break;
        case 5: _t->changeIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->palyVideo(); break;
        case 7: _t->showCalendarWidget(); break;
        case 8: _t->videoUpOne(); break;
        case 9: _t->videoDownOne(); break;
        default: ;
        }
    }
}

const QMetaObject VideoPlaybackWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoPlaybackWin.data,
      qt_meta_data_VideoPlaybackWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoPlaybackWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlaybackWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlaybackWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoPlaybackWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
