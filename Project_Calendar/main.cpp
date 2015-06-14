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
