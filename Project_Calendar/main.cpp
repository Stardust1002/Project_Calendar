#include "mainwindow.h"
#include <QApplication>
#include "manager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Manager<int>& m = Manager<int>::getInstance();

    w.show();

    return a.exec();
}
