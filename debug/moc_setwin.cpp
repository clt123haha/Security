/****************************************************************************
** Meta object code from reading C++ file 'setwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/setwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetWin_t {
    QByteArrayData data[10];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetWin_t qt_meta_stringdata_SetWin = {
    {
QT_MOC_LITERAL(0, 0, 6), // "SetWin"
QT_MOC_LITERAL(1, 7, 4), // "down"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 5), // "notDo"
QT_MOC_LITERAL(4, 19, 15), // "changeVideoPath"
QT_MOC_LITERAL(5, 35, 13), // "changeImgPath"
QT_MOC_LITERAL(6, 49, 9), // "updateSet"
QT_MOC_LITERAL(7, 59, 6), // "Cansel"
QT_MOC_LITERAL(8, 66, 10), // "openMsgBox"
QT_MOC_LITERAL(9, 77, 11) // "closeMsgBox"

    },
    "SetWin\0down\0\0notDo\0changeVideoPath\0"
    "changeImgPath\0updateSet\0Cansel\0"
    "openMsgBox\0closeMsgBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SetWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetWin *_t = static_cast<SetWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->down(); break;
        case 1: _t->notDo(); break;
        case 2: _t->changeVideoPath(); break;
        case 3: _t->changeImgPath(); break;
        case 4: _t->updateSet(); break;
        case 5: _t->Cansel(); break;
        case 6: _t->openMsgBox(); break;
        case 7: _t->closeMsgBox(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SetWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetWin::down)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SetWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetWin::notDo)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SetWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SetWin.data,
      qt_meta_data_SetWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SetWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SetWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SetWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SetWin::down()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SetWin::notDo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
