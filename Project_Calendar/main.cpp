#include "GUI/mainwindow.h"
#include <QApplication>
#include "qtimespan.h"
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
    ProgrammationManager &ProgM = ProgrammationManager::getInstance();
    PrecedenceManager &PrecM = PrecedenceManager::getInstance();

    TacheUnitaire *tu[4];

    tu[0] = &TM.ajouterTacheUnitaire("1","Test1","01:00",0,"20:10:1994:00:00","20:10:1994:10:00");
    tu[1] = &TM.ajouterTacheUnitaire("2","Test2","01:00",0,"20:10:1994:00:00","20:10:1994:23:59");
    tu[2] = &TM.ajouterTacheUnitaire("3","Test3","01:00",0,"20:10:1994:00:00","20:10:1994:23:59");
    tu[3] = &TM.ajouterTacheUnitaire("SOPRA STERIA","Test4","02:00",0,"20:10:2002:00:00","20:10:2009:23:59");

    TacheComposite& tc1 = TM.ajouterTacheComposite("C1","Frolux","06:06:1993:12:21","10:07:1995:01:59");
    TacheComposite& tc2 = TM.ajouterTacheComposite("C2","Frolux","06:06:1993:12:21","10:07:2011:01:59");


    tc1.push_back(*tu[0]);
    tc2.push_back(*tu[2]);
    tc2.push_back(*tu[3]);


    PrecM.ajouterPrecedence(*tu[0],*tu[1]);
    PrecM.ajouterPrecedence(*tu[1],*tu[3]);


    Projet& p = PM.ajouterProjet("NA17","Ca casse les couilles","20:10:1994:00:00");
    p.ajouterTache("SOPRA STERIA");



    Activite& act = AM.ajouterActivite("Se branler", "avec son colloc", Activite::REUNION, "00:30");
    act.afficher();




    Programmation& prog = ProgM.ajouterProgrammation(act,"12:07:2022:12:36","02:12");
    qDebug()<<prog.getDuree()<<ProgM.dureeProgrammee(act)<<ProgM.isProgrammee(act);

    p.afficher();

   // TM.deleteItem("C1");

    qDebug()<<"Jusqu'ici tout va bien";

    return a.exec();
}
