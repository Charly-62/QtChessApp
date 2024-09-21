/****************************************************************************
** Meta object code from reading C++ file 'schachapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../schach/schachapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'schachapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SchachApp_t {
    QByteArrayData data[25];
    char stringdata0[440];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SchachApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SchachApp_t qt_meta_stringdata_SchachApp = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SchachApp"
QT_MOC_LITERAL(1, 10, 17), // "handleSquareClick"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "row"
QT_MOC_LITERAL(4, 33, 3), // "col"
QT_MOC_LITERAL(5, 37, 19), // "on_leIP_textChanged"
QT_MOC_LITERAL(6, 57, 4), // "arg1"
QT_MOC_LITERAL(7, 62, 34), // "on_cbHostClient_currentTextCh..."
QT_MOC_LITERAL(8, 97, 4), // "mode"
QT_MOC_LITERAL(9, 102, 38), // "on_cbStartingPlayer_currentTe..."
QT_MOC_LITERAL(10, 141, 14), // "startingPlayer"
QT_MOC_LITERAL(11, 156, 21), // "updateNetzwerkConsole"
QT_MOC_LITERAL(12, 178, 7), // "message"
QT_MOC_LITERAL(13, 186, 19), // "updateInGameConsole"
QT_MOC_LITERAL(14, 206, 16), // "device_connected"
QT_MOC_LITERAL(15, 223, 19), // "device_disconnected"
QT_MOC_LITERAL(16, 243, 19), // "device_stateChanged"
QT_MOC_LITERAL(17, 263, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(18, 292, 19), // "on_bConnect_clicked"
QT_MOC_LITERAL(19, 312, 17), // "on_bStart_clicked"
QT_MOC_LITERAL(20, 330, 18), // "on_pbClear_clicked"
QT_MOC_LITERAL(21, 349, 17), // "on_pbUndo_clicked"
QT_MOC_LITERAL(22, 367, 20), // "on_bSendName_clicked"
QT_MOC_LITERAL(23, 388, 23), // "on_lename_returnPressed"
QT_MOC_LITERAL(24, 412, 27) // "on_leSendChat_returnPressed"

    },
    "SchachApp\0handleSquareClick\0\0row\0col\0"
    "on_leIP_textChanged\0arg1\0"
    "on_cbHostClient_currentTextChanged\0"
    "mode\0on_cbStartingPlayer_currentTextChanged\0"
    "startingPlayer\0updateNetzwerkConsole\0"
    "message\0updateInGameConsole\0"
    "device_connected\0device_disconnected\0"
    "device_stateChanged\0QAbstractSocket::SocketState\0"
    "on_bConnect_clicked\0on_bStart_clicked\0"
    "on_pbClear_clicked\0on_pbUndo_clicked\0"
    "on_bSendName_clicked\0on_lename_returnPressed\0"
    "on_leSendChat_returnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SchachApp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x08 /* Private */,
       5,    1,   99,    2, 0x08 /* Private */,
       7,    1,  102,    2, 0x08 /* Private */,
       9,    1,  105,    2, 0x08 /* Private */,
      11,    1,  108,    2, 0x08 /* Private */,
      13,    1,  111,    2, 0x08 /* Private */,
      14,    0,  114,    2, 0x08 /* Private */,
      15,    0,  115,    2, 0x08 /* Private */,
      16,    1,  116,    2, 0x08 /* Private */,
      18,    0,  119,    2, 0x08 /* Private */,
      19,    0,  120,    2, 0x08 /* Private */,
      20,    0,  121,    2, 0x08 /* Private */,
      21,    0,  122,    2, 0x08 /* Private */,
      22,    0,  123,    2, 0x08 /* Private */,
      23,    0,  124,    2, 0x08 /* Private */,
      24,    0,  125,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SchachApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SchachApp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleSquareClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_leIP_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_cbHostClient_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_cbStartingPlayer_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->updateNetzwerkConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->updateInGameConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->device_connected(); break;
        case 7: _t->device_disconnected(); break;
        case 8: _t->device_stateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 9: _t->on_bConnect_clicked(); break;
        case 10: _t->on_bStart_clicked(); break;
        case 11: _t->on_pbClear_clicked(); break;
        case 12: _t->on_pbUndo_clicked(); break;
        case 13: _t->on_bSendName_clicked(); break;
        case 14: _t->on_lename_returnPressed(); break;
        case 15: _t->on_leSendChat_returnPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SchachApp::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SchachApp.data,
    qt_meta_data_SchachApp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SchachApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SchachApp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SchachApp.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SchachApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
