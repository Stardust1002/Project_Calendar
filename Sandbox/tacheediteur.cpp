#include "tacheediteur.h"
#include "fonctions.h"

tacheEditeur::tacheEditeur(Tache* tacheToEdit, QWidget* parent):tache(tacheToEdit), QDialog(parent)
{
    setWindowTitle("Création d'une Tache");

   hlayout_1 = new QHBoxLayout;
   hlayout_2 = new QHBoxLayout;
   hlayout_3 = new QHBoxLayout;
   hlayout_4 = new QHBoxLayout;
   hlayout_5 = new QHBoxLayout;
   hlayout_6 = new QHBoxLayout;
   hlayout_7 = new QHBoxLayout;
   hlayout_8 = new QHBoxLayout;

   vlayout = new QVBoxLayout;

   lab = new QLabel("Identificateur: ");
   id = new QLineEdit;
   pre = new QCheckBox(" Preemptive");
    hlayout_1->addWidget(lab);
    hlayout_1->addWidget(id);
    hlayout_1->addSpacing(10);
    hlayout_1->addWidget(pre);

    lab2 = new QLabel("Titre: ");
    titre = new QTextEdit;
    hlayout_2->addWidget(lab2);
    hlayout_2->addWidget(titre);

    lab3 = new QLabel("Disponibilite: ");
    lab4 = new QLabel("Echeance: ");
    lab5 = new QLabel("Duree: ");
    lab6 = new QLabel("Projet: ");

    dispo = new QDateTimeEdit;
    dispo->setCalendarPopup(true);
    dispo->setDateTime(QDateTime::currentDateTime());
    echeance = new QDateTimeEdit;
    echeance->setCalendarPopup(true);
    echeance->setDateTime(QDateTime::currentDateTime());
    duree = new QTimeEdit;
    projet = new QComboBox;

    hlayout_3->addWidget(lab3);
    hlayout_3->addWidget(dispo);
    hlayout_3->addSpacing(10);
    hlayout_3->addWidget(lab4);
    hlayout_3->addWidget(echeance);
    hlayout_3->addSpacing(10);
    hlayout_3->addWidget(lab5);
    hlayout_3->addWidget(duree);

    hlayout_5->addWidget(lab6);
    hlayout_5->addWidget(projet);

    cancel = new QPushButton("Annuler");
    save = new QPushButton("Sauver");

    save->setDisabled(false);
    hlayout_4->addWidget(cancel);
    hlayout_4->addWidget(save);

    lab7 = new QLabel("Prédecesseurs");
    lab8 = new QLabel("Successeurs");
    lab9 = new QLabel("Liste des Taches");
    hlayout_7->addWidget(lab7);
    hlayout_7->addWidget(lab9);
    hlayout_7->addWidget(lab8);


    pred = new QListWidget();
    succ = new QListWidget();

    liste_taches = new QListWidget();
    hlayout_6->addWidget(pred);
    hlayout_6->addWidget(liste_taches);
    hlayout_6->addWidget(succ);
    liste_taches->addItem("LO21");
    liste_taches->addItem("NA17");
    liste_taches->addItem("SR02");
    liste_taches->addItem("IA02");
    liste_taches->addItem("IC05");
    liste_taches->addItem("MG01");



    liste_taches->setDragEnabled(true);
    liste_taches->setDropIndicatorShown(true);
    liste_taches->setDragDropMode(QAbstractItemView::DragDrop);
    liste_taches->setDefaultDropAction(Qt::MoveAction);
    liste_taches->setDragDropOverwriteMode(false);
    liste_taches->setEditTriggers(QListWidget::NoEditTriggers);

    pred->setDragEnabled(true);
    pred->setDropIndicatorShown(true);
    pred->setDragDropMode(QAbstractItemView::DragDrop);
    pred->setDefaultDropAction(Qt::MoveAction);
    pred->setDragDropOverwriteMode(false);
    pred->setEditTriggers(QListWidget::NoEditTriggers);

    succ->setDragEnabled(true);
    succ->setDropIndicatorShown(true);
    succ->setDragDropMode(QAbstractItemView::DragDrop);
    succ->setDefaultDropAction(Qt::MoveAction);
    succ->setDragDropOverwriteMode(false);
    succ->setEditTriggers(QListWidget::NoEditTriggers);

    vlayout->addItem(hlayout_1);
    vlayout->addItem(hlayout_2);
    vlayout->addItem(hlayout_3);
    vlayout->addItem(hlayout_5);
    vlayout->addItem(hlayout_7);
    vlayout->addItem(hlayout_6);
    vlayout->addItem(hlayout_4);


    if(tache != 0){
        id->setText(tache->getId());
        if(tache->isPreemptive())
               pre->setChecked(true);
        titre->setText(tache->getTitre());
        //dispo->setDateTime(tache->getDateDisponibilite());
        //echeance->setDateTime(tache->getDateEcheance());
    }else
    projet->addItem("Sélectionner");
    projet->addItem("NA17");
    projet->addItem("LO21");
    projet->addItem("IA02");





    this->setLayout(vlayout);
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(sauver()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

}
void tacheEditeur::sauver()
{
    if(!id->text().isEmpty() &&
       !titre->toPlainText().isEmpty()&&
       !dispo->text().isEmpty() &&
       !echeance->text().isEmpty() &&
       dispo->dateTime() < echeance->dateTime() &&
       duree->text() != "00:00"){
        if(!pre->isChecked() && duree->time() > QTime::fromString("12:00","hh:mm")){
            ouvrirWarning("Une tâche non-préemptive doit durer moins de 12h !");
             return;}
        if(tache == 0){
        //AJOUT DE LA TACHE
        ouvrirInformation("Tache créée avec succès !\nN'oubliez pas de la programmer !","Félicitations");
         }
        else{
        if(ouvrirQuestion("Êtes-vous sûr de vouloir modifier cette tâche ?")){
            //MODIFICATION DE LA TACHE
        }}
        delete this;
    }
    else
        ouvrirWarning("Des informations sont manquantes ou érronées !","Erreur");
}
tacheEditeur::~tacheEditeur()
{

}

