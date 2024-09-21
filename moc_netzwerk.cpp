/****************************************************************************
** Meta object code from reading C++ file 'netzwerk.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../schach/netzwerk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netzwerk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Netzwerk_t {
    QByteArrayData data[19];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Netzwerk_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Netzwerk_t qt_meta_stringdata_Netzwerk = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Netzwerk"
QT_MOC_LITERAL(1, 9, 14), // "logNetzwerkMsg"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "message"
QT_MOC_LITERAL(4, 33, 12), // "logInGameMsg"
QT_MOC_LITERAL(5, 46, 12), // "moveReceived"
QT_MOC_LITERAL(6, 59, 8), // "MoveInfo"
QT_MOC_LITERAL(7, 68, 8), // "moveInfo"
QT_MOC_LITERAL(8, 77, 11), // "gameStarted"
QT_MOC_LITERAL(9, 89, 12), // "ServerStarts"
QT_MOC_LITERAL(10, 102, 8), // "QString&"
QT_MOC_LITERAL(11, 111, 11), // "groupNumber"
QT_MOC_LITERAL(12, 123, 12), // "moveRejected"
QT_MOC_LITERAL(13, 136, 8), // "undoMove"
QT_MOC_LITERAL(14, 145, 12), // "undoAccepted"
QT_MOC_LITERAL(15, 158, 8), // "accepted"
QT_MOC_LITERAL(16, 167, 20), // "opponentNameReceived"
QT_MOC_LITERAL(17, 188, 7), // "oppName"
QT_MOC_LITERAL(18, 196, 15) // "ChatMsgReceived"

    },
    "Netzwerk\0logNetzwerkMsg\0\0message\0"
    "logInGameMsg\0moveReceived\0MoveInfo\0"
    "moveInfo\0gameStarted\0ServerStarts\0"
    "QString&\0groupNumber\0moveRejected\0"
    "undoMove\0undoAccepted\0accepted\0"
    "opponentNameReceived\0oppName\0"
    "ChatMsgReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Netzwerk[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       8,    2,   68,    2, 0x06 /* Public */,
      12,    0,   73,    2, 0x06 /* Public */,
      13,    0,   74,    2, 0x06 /* Public */,
      14,    1,   75,    2, 0x06 /* Public */,
      16,    1,   78,    2, 0x06 /* Public */,
      18,    1,   81,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 10,    9,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Netzwerk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Netzwerk *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logNetzwerkMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->logInGameMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->moveReceived((*reinterpret_cast< MoveInfo(*)>(_a[1]))); break;
        case 3: _t->gameStarted((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->moveRejected(); break;
        case 5: _t->undoMove(); break;
        case 6: _t->undoAccepted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->opponentNameReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->ChatMsgReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Netzwerk::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::logNetzwerkMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::logInGameMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(MoveInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::moveReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(bool , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::gameStarted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::moveRejected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::undoMove)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::undoAccepted)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::opponentNameReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Netzwerk::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Netzwerk::ChatMsgReceived)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Netzwerk::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Netzwerk.data,
    qt_meta_data_Netzwerk,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Netzwerk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Netzwerk::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Netzwerk.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Netzwerk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Netzwerk::logNetzwerkMsg(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Netzwerk::logInGameMsg(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Netzwerk::moveReceived(MoveInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Netzwerk::gameStarted(bool _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Netzwerk::moveRejected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Netzwerk::undoMove()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Netzwerk::undoAccepted(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Netzwerk::opponentNameReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Netzwerk::ChatMsgReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
