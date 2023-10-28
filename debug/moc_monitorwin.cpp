/****************************************************************************
** Meta object code from reading C++ file 'monitorwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/monitorwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitorwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MonitorWin_t {
    QByteArrayData data[12];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MonitorWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MonitorWin_t qt_meta_stringdata_MonitorWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MonitorWin"
QT_MOC_LITERAL(1, 11, 10), // "ChangeGrid"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 2), // "id"
QT_MOC_LITERAL(4, 26, 13), // "ChangeGridBun"
QT_MOC_LITERAL(5, 40, 10), // "SeeAllGrid"
QT_MOC_LITERAL(6, 51, 13), // "takingPicture"
QT_MOC_LITERAL(7, 65, 7), // "getImg1"
QT_MOC_LITERAL(8, 73, 3), // "img"
QT_MOC_LITERAL(9, 77, 7), // "getImg2"
QT_MOC_LITERAL(10, 85, 7), // "getImg3"
QT_MOC_LITERAL(11, 93, 7) // "getImg4"

    },
    "MonitorWin\0ChangeGrid\0\0id\0ChangeGridBun\0"
    "SeeAllGrid\0takingPicture\0getImg1\0img\0"
    "getImg2\0getImg3\0getImg4"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MonitorWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       1,    0,   65,    2, 0x0a /* Public */,
       5,    0,   66,    2, 0x0a /* Public */,
       6,    0,   67,    2, 0x0a /* Public */,
       7,    1,   68,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      11,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void, QMetaType::QImage,    8,
    QMetaType::Void, QMetaType::QImage,    8,

       0        // eod
};

void MonitorWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MonitorWin *_t = static_cast<MonitorWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChangeGrid((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ChangeGridBun((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ChangeGrid(); break;
        case 3: _t->SeeAllGrid(); break;
        case 4: _t->takingPicture(); break;
        case 5: _t->getImg1((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->getImg2((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 7: _t->getImg3((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 8: _t->getImg4((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MonitorWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MonitorWin.data,
      qt_meta_data_MonitorWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MonitorWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MonitorWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MonitorWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MonitorWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
