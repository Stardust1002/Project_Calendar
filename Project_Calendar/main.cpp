#include "GUI/mainwindow.h"
#include <QApplication>
#include "qtimespan.h"
#include "manager.h"
#include "import-export.h"
#include <ostream>
#include <QSound>
#include <QSplashScreen>
#include "Windows.h"

/*! \mainpage Rocket! Calendar
 *
 * \section  Présentation
 *
 * Rocket! Calendar a été réalisé par Valentin Feld et Antoine Jeannot en Printemps 2015.
 *
 * Cette application de calendrier est le fruit de l'apprentissage du C++ et de ses design patterns réalisé en LO21 à l'Université de Technologie de Compiègne.
 *
 * En dépit de lourdes contraintes de temps dûes aux délais impartis, des concessions ont dûes être faites.
 *
 * Nous avons essayé de livrer le programme le plus complet possible tout en respectant un maximum le cahier des charges imposé.
 *
 * Aussi, de nombreuses optimisations sont possibles et réalisables grâce à une architecture qui se veut évolutive et maintenable.
 *
 * La conception de ce projet nous aura permis d'améliorer notre travail d'équipe ainsi que nos compétences manageriales, sous la pression des examens et des rendus de nos cinq autres projets simultanés.
 *
 * Elle a également été l'occasion de se former aux outils de collaboration en ligne comme GitHub.
 *
 * De plus, les méthodes SCRUM ont été employées dès le début de l'analyse du problème, de la modélisation logique des données à la création de cette documentation.
 *
 * Vous trouverez ci-dessous:
 * - l'executable
 * - la video de présentation
 * - les impressions d'écran
 * - la modélisation UML
 * - le lien vers les fichiers sources disponibles sur GitHub
 *
 * Pour nous contacter:
 * - Antoine: antoine.jeannot@etu.utc.fr
 * - Valentin: valentin.feld@etu.utc.fr
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        Memento::getInstance().load();
    }
    catch(const char* ){
        Memento::getInstance().save();
    }


    /*TacheManager &TM = TacheManager::getInstance();
    ProjetManager &PM = ProjetManager::getInstance();
    ActiviteManager &AM = ActiviteManager::getInstance();
    ProgrammationManager &ProgM = ProgrammationManager::getInstance();
    PrecedenceManager &PrecM = PrecedenceManager::getInstance();

    TacheUnitaire *tu[4];

    try{
    tu[0] = &TM.ajouterTacheUnitaire("1","Test1","01:00",0,"07:06:2015:00:00","10:08:2015:10:00");
    tu[1] = &TM.ajouterTacheUnitaire("2","Test2","01:00",0,"08:06:2015:00:00","10:08:2015:10:00");
    tu[2] = &TM.ajouterTacheUnitaire("3","Test3","01:00",0,"09:06:2015:00:00","10:08:2015:10:00");
    tu[3] = &TM.ajouterTacheUnitaire("SOPRA STERIA","Test4","02:00",0,"20:01:2015:00:00","21:10:2016:23:59");

    TacheComposite& tc1 = TM.ajouterTacheComposite("C1","Frolux","06:06:1993:12:21","10:07:2025:01:59");
    TacheComposite& tc2 = TM.ajouterTacheComposite("C2","Frolux","06:06:1993:12:21","10:07:2021:01:59");


    tc1.push_back(*tu[0]);
    tc2.push_back(*tu[2]);
    tc2.push_back(*tu[3]);


    PrecM.ajouterPrecedence(tc2,*tu[0]);
    //PrecM.ajouterPrecedence(*tu[1],*tu[3]);


    Projet& p = PM.ajouterProjet("NA17","Ca casse les couilles","20:10:1994:00:00");
    p.ajouterTache("SOPRA STERIA");
    p.ajouterTache(tc1.getId());
    p.ajouterTache(tc2.getId());
    p.ajouterTache(tu[0]);
    p.ajouterTache(tu[1]);
    p.ajouterTache(tu[2]);

    Activite& act = AM.ajouterActivite("Manger", "avec son colloc", Activite::REUNION, "00:30");
    Activite& act2 = AM.ajouterActivite("Vaisselle", "avec son colloc", Activite::REUNION, "00:10");


    TacheUnitaire & preempt = TM.ajouterTacheUnitaire("4","Donner Pain aux canards","02:00",1,"08:06:2015:00:00","10:08:2015:10:00");
//ProgM.ajouterProgrammation(preempt,"15:06:2015:09:00","01:00");
  //  ProgM.ajouterProgrammation(preempt,"17:06:2015:22:00","01:00");

ProgM.ajouterProgrammation(act,"08:06:2015:12:36","00:30");
 ProgM.ajouterProgrammation(act2,"10:06:2015:12:36","00:10");
//    qDebug()<<prog.getDuree()<<ProgM.dureeProgrammee(act)<<ProgM.isProgrammee(act);

    ProgM.ajouterProgrammation(*tu[1],"10:06:2015:10:00","01:00");
    ProgM.ajouterProgrammation(*tu[2],"10:06:2015:09:00","01:00");
    ProgM.ajouterProgrammation(*tu[3],"11:06:2015:15:30","02:00");
    ProgM.ajouterProgrammation(*tu[0],"11:06:2015:17:30","01:00");

    qDebug()<<"\n\n"<<ProgM.getFinTache(*tu[0]);
    qDebug()<<ProgM.getFinTache(*tu[1]);
    qDebug()<<ProgM.getFinTache(*tu[2]);
    qDebug()<<ProgM.getFinTache(*tu[3]);

//    vector<Programmation*> liste = act.getProgrammations();
//    qDebug() << "----------------------";
//    for(vector<Programmation*>::iterator it = liste.begin(); it != liste.end(); ++it)
//        qDebug() << "Programmation:" << (*it)->getDate();


   // p.afficher();

   // TM.deleteItem("C1");

    // ----- Test Export ------

    Memento& m = Memento::getInstance();
    // Plus besoin de specifier la strategie (par défaut XML avec pathname = "auto-save.xml"
    //XML& format= XML::getInstance();
    //format.setPathname("new.xml");
    //m.setStrategie(&format);
    m.save();

    qDebug()<<"Jusqu'ici tout va bien";

    }

 catch(const char* s){ouvrirWarning(s);}*/


    MainWindow w;
    QSplashScreen screen;
    screen.setPixmap(QPixmap(":/Extra/logo.png"));
    screen.show();
    QSound::play(":/Extra/sound.wav");
    Sleep(1500);
    screen.finish(&w);
    w.show();
    return a.exec();

}
