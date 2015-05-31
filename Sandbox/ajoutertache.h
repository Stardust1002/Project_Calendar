#ifndef AJOUTERTACHE_H
#define AJOUTERTACHE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include "calendar.h"
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QDateEdit>
#include <QSpinBox>

class ajouterTache:public QWidget
{

    Q_OBJECT

    Tache& tache;
    QHBoxLayout* hlayout_1;
    QHBoxLayout* hlayout_2;
    QHBoxLayout* hlayout_3;
    QHBoxLayout* hlayout_4;
    QVBoxLayout * vlayout;
    QLabel* lab;
    QLineEdit* id ;
    QCheckBox* pre;
    QLabel* lab2 ;
    QTextEdit* titre;
    QLabel* lab3;
    QLabel* lab4;
    QDateEdit* dispo;
    QDateEdit* echeance;
    QSpinBox* heures;
    QSpinBox* minutes;
    QPushButton* cancel;
    QPushButton* save;

public slots:
    void sauver();

public:
    ajouterTache(Tache$tacheToEdit, QWidget* parent = 0);
    ~ajouterTache();
};
#endif // AJOUTERTACHE_H
