/****************************************************************************
** Meta object code from reading C++ file 'loginwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/loginwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginWin_t {
    QByteArrayData data[11];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginWin_t qt_meta_stringdata_LoginWin = {
    {
QT_MOC_LITERAL(0, 0, 8), // "LoginWin"
QT_MOC_LITERAL(1, 9, 6), // "getUid"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 3), // "uid"
QT_MOC_LITERAL(4, 21, 7), // "doLogin"
QT_MOC_LITERAL(5, 29, 4), // "name"
QT_MOC_LITERAL(6, 34, 10), // "backtoMain"
QT_MOC_LITERAL(7, 45, 5), // "login"
QT_MOC_LITERAL(8, 51, 13), // "openEnrollWin"
QT_MOC_LITERAL(9, 65, 14), // "closeEnrollWin"
QT_MOC_LITERAL(10, 80, 14) // "changePwdStaus"

    },
    "LoginWin\0getUid\0\0uid\0doLogin\0name\0"
    "backtoMain\0login\0openEnrollWin\0"
    "closeEnrollWin\0changePwdStaus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       4,    0,   60,    2, 0x06 /* Public */,
       6,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LoginWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginWin *_t = static_cast<LoginWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getUid((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->doLogin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->doLogin(); break;
        case 3: _t->backtoMain(); break;
        case 4: _t->login(); break;
        case 5: _t->openEnrollWin(); break;
        case 6: _t->closeEnrollWin(); break;
        case 7: _t->changePwdStaus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LoginWin::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWin::getUid)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LoginWin::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWin::doLogin)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LoginWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWin::doLogin)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (LoginWin::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWin::backtoMain)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject LoginWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoginWin.data,
      qt_meta_data_LoginWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LoginWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LoginWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LoginWin::getUid(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoginWin::doLogin(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LoginWin::doLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LoginWin::backtoMain()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
