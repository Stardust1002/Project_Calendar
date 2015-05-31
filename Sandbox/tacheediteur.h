#ifndef TACHEEDITEUR_H
#define TACHEEDITEUR_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include "calendar.h"
#include "fonctions.h"
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QListWidget>
#include <QAbstractItemView>

class tacheEditeur:public QDialog
{

    Q_OBJECT

    Tache* tache;
    QHBoxLayout* hlayout_1;
    QHBoxLayout* hlayout_2;
    QHBoxLayout* hlayout_3;
    QHBoxLayout* hlayout_4;
    QHBoxLayout* hlayout_5;
    QHBoxLayout* hlayout_6;
    QHBoxLayout* hlayout_7;
    QHBoxLayout* hlayout_8;


    QVBoxLayout * vlayout;

    QLabel* lab;
    QLineEdit* id ;
    QCheckBox* pre;
    QLabel* lab2 ;
    QTextEdit* titre;
    QLabel* lab3;
    QLabel* lab4;
    QLabel* lab5;
    QLabel* lab6;
    QLabel* lab7;
    QLabel* lab8;
    QLabel* lab9;

    QDateTimeEdit* dispo;
    QDateTimeEdit* echeance;
    QTimeEdit* duree;
    QPushButton* cancel;
    QPushButton* save;
    QComboBox* projet;
    QListWidget* pred;
    QListWidget* succ;
    QListWidget* liste_taches;

public slots:
    void sauver();

public:
    tacheEditeur(Tache* tacheToEdit = 0, QWidget* parent = 0);
    ~tacheEditeur();
};


#endif // TACHEEDITEUR_H
