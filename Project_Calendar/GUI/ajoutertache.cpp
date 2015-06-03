#include "ajoutertache.h"
ajouterTache::ajouterTache(Tache& tacheToEdit, QWidget* parent):tache(tacheToEdit), QWidget(parent)
{

   parent->setWindowTitle(QString("Edition de la tâche ") + tacheToEdit.getId());
   hlayout_1 = new QHBoxLayout;
   hlayout_2 = new QHBoxLayout;
   hlayout_3 = new QHBoxLayout;
   hlayout_4 = new QHBoxLayout;

   vlayout = new QVBoxLayout;

   lab = new QLabel("Identificateur: ");
   id = new QLineEdit(tache.getId());
   pre = new QCheckBox(" Preemptive");
   if(tache.isPreemptive())
       pre->setChecked(true);

    hlayout_1->addWidget(lab);
    hlayout_1->addWidget(id);
    hlayout_1->addSpacing(10);
    hlayout_1->addWidget(pre);

    lab2 = new QLabel("Titre: ");
    titre = new QTextEdit(tache.getTitre());
    hlayout_2->addWidget(lab2);
    hlayout_2->addWidget(titre);

    lab3 = new QLabel("Disponibilite: ");
    lab4 = new QLabel("Echeance: ");
    dispo = new QDateEdit(tache.getDateDisponibilite());
    echeance = new QDateEdit(tache.getDateEcheance());
    heures = new QSpinBox;
    minutes = new QSpinBox;
    heures->setValue(tache.getDuree().getHeure());
    minutes->setValue(tache.getDuree().getMinute());
    heures->setSuffix(" heures");
    minutes->setSuffix(" minutes");
    heures->setRange(0,23);
    minutes->setRange(0,59);
    hlayout_3->addWidget(lab3);
    hlayout_3->addWidget(dispo);
    hlayout_3->addSpacing(10);
    hlayout_3->addWidget(lab4);
    hlayout_3->addWidget(echeance);
    hlayout_3->addSpacing(10);
    hlayout_3->addWidget(heures);
    hlayout_3->addWidget(minutes);

    cancel = new QPushButton("Annuler");
    save = new QPushButton("Sauver");

    save->setDisabled(false);
    hlayout_4->addWidget(cancel);
    hlayout_4->addWidget(save);

    vlayout->addItem(hlayout_1);
    vlayout->addItem(hlayout_2);
    vlayout->addItem(hlayout_3);
    vlayout->addItem(hlayout_4);

    parent->setLayout(vlayout);
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(sauver()));
    QObject::connect(cancel, SIGNAL(clicked()), parent, SLOT(close()));
}
void ajouterTache::sauver()
{
    TacheManager* tm = &TacheManager::getInstance();
    if(tm->isTacheExistante(id->text())){
        QMessageBox::warning(this, "Erreur", "Erreur: Tache existante");
        return;
    }
    Duree d(heures->text().toInt(), minutes->text().toInt());
//    tm->ajouterTache(id->text(), titre->toPlainText(), d, dispo, echeance, pre->text());
    QMessageBox::information(this, "Félicitations", "YEAH BITCH");
    //attribuer à l'objet tache chaque propriété
    //tache.xxxx = ...
}
ajouterTache::~ajouterTache()
{

}
