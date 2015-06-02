#include "mainwindow.h"
#include <QApplication>
#include "manager.h"
#include "timing.h"
#include <ostream>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;*/

    TacheManager &TM = TacheManager::getInstance();
    //TacheManager::freeInstance();

    TacheUnitaire *tu[3];

    tu[0] = &TM.ajouterTacheUnitaire("1","Test1","01:00",0,"20:10:1994:00:00","20:10:1994:23:99");
    tu[1] = &TM.ajouterTacheUnitaire("2","Test2","01:00",0,"20:10:1994:00:00","20:10:1994:23:99");
    tu[2] = &TM.ajouterTacheUnitaire("3","Test3","01:00",0,"20:10:1994:00:00","20:10:1994:23:99");
    TacheComposite& tc = TM.ajouterTacheComposite("C1","composite");
    tc.push_back(*tu[0]);
    tc.push_back(*tu[1]);
    tc.push_back(*tu[2]);

    tc.setDisponibilite("21:10:1994:99:00");

    TM.supprimerTache("C1");

    qDebug()<<"Jusqu'ici tout va bien";

    return 0;

    /*w.show();

    return a.exec();*/
}
