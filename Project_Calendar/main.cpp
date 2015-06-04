#include "GUI/mainwindow.h"
#include <QApplication>
#include "manager.h"
#include "timing.h"
#include <ostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TacheManager &TM = TacheManager::getInstance();
    ProjetManager &PM = ProjetManager::getInstance();
    ActiviteManager &AM = ActiviteManager::getInstance();

    //TacheManager::freeInstance();

    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime test = QDateTime::fromString("21:10:1994:25:00",format);
    qDebug()<<test;
    qDebug()<<test.isValid();

    TacheUnitaire *tu[4];

    tu[0] = &TM.ajouterTacheUnitaire("1","Test1","01:00",0,"20:10:1994:00:00","20:10:1994:23:59");
    tu[1] = &TM.ajouterTacheUnitaire("2","Test2","01:00",0,"20:10:1994:00:00","20:10:1994:23:59");
    tu[2] = &TM.ajouterTacheUnitaire("3","Test3","01:00",0,"20:10:1994:00:00","20:10:1994:23:59");
    tu[3] = &TM.ajouterTacheUnitaire("SOPRA STERIA","Test4","02:00",0,"20:10:2015:00:00","20:10:2015:23:59");

    Projet& p = PM.ajouterProjet("NA17","Ca casse les couilles","20:10:1994:00:00");
    p.afficher();

    Activite& act = AM.ajouterActivite("Se branler", "avec son colloc", Activite::REUNION, "00:30");
    act.afficher();

    //TacheComposite& tc = TM.ajouterTacheComposite("C1","composite");
    //tc.push_back(*tu[0]);
    //tc.push_back(*tu[1]);
    //tc.push_back(*tu[2]);

   // format = "dd:MM:yyyy:HH:mm";
   // QDateTime date_dispo = QDateTime::fromString("21:10:1994:23:00",format);
   // qDebug()<<date_dispo;

   // format = "dd:MM:yyyy:HH:mm";
   // QDateTime dispo = QDateTime::fromString("21:10:1994:23:00",format);
  //  qDebug()<<dispo;

    //tc.setDisponibilite("21:10:1994:23:00");

   // TM.deleteItem("C1");

    qDebug()<<"Jusqu'ici tout va bien";

    return a.exec();
}
