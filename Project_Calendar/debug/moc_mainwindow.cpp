/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[413];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_newActivity_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 27), // "on_actionUnitaire_triggered"
QT_MOC_LITERAL(4, 65, 14), // "TacheUnitaire*"
QT_MOC_LITERAL(5, 80, 1), // "t"
QT_MOC_LITERAL(6, 82, 34), // "on_actionCr_er_un_Projet_trig..."
QT_MOC_LITERAL(7, 117, 28), // "on_actionComposite_triggered"
QT_MOC_LITERAL(8, 146, 39), // "on_actionProgrammer_une_Tache..."
QT_MOC_LITERAL(9, 186, 41), // "on_actionProgrammer_une_Activ..."
QT_MOC_LITERAL(10, 228, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(11, 252, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(12, 278, 4), // "date"
QT_MOC_LITERAL(13, 283, 26), // "on_tableWidget_itemClicked"
QT_MOC_LITERAL(14, 310, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(15, 328, 4), // "item"
QT_MOC_LITERAL(16, 333, 32), // "on_tableWidget_itemDoubleClicked"
QT_MOC_LITERAL(17, 366, 15), // "on_voir_clicked"
QT_MOC_LITERAL(18, 382, 30) // "on_actionVue_Globale_triggered"

    },
    "MainWindow\0on_newActivity_triggered\0"
    "\0on_actionUnitaire_triggered\0"
    "TacheUnitaire*\0t\0on_actionCr_er_un_Projet_triggered\0"
    "on_actionComposite_triggered\0"
    "on_actionProgrammer_une_Tache_triggered\0"
    "on_actionProgrammer_une_Activit_triggered\0"
    "on_pushButton_2_clicked\0"
    "on_calendarWidget_clicked\0date\0"
    "on_tableWidget_itemClicked\0QTableWidgetItem*\0"
    "item\0on_tableWidget_itemDoubleClicked\0"
    "on_voir_clicked\0on_actionVue_Globale_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       3,    1,   81,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    1,   89,    2, 0x08 /* Private */,
      13,    1,   92,    2, 0x08 /* Private */,
      16,    1,   95,    2, 0x08 /* Private */,
      17,    0,   98,    2, 0x08 /* Private */,
      18,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_newActivity_triggered(); break;
        case 1: _t->on_actionUnitaire_triggered(); break;
        case 2: _t->on_actionUnitaire_triggered((*reinterpret_cast< TacheUnitaire*(*)>(_a[1]))); break;
        case 3: _t->on_actionCr_er_un_Projet_triggered(); break;
        case 4: _t->on_actionComposite_triggered(); break;
        case 5: _t->on_actionProgrammer_une_Tache_triggered(); break;
        case 6: _t->on_actionProgrammer_une_Activit_triggered(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 9: _t->on_tableWidget_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->on_tableWidget_itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->on_voir_clicked(); break;
        case 12: _t->on_actionVue_Globale_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
