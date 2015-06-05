#include "tacheediteur.h"

tacheEditeur::tacheEditeur(TacheUnitaire* tacheToEdit, QWidget* parent):tache(tacheToEdit), QDialog(parent)
{
    TacheManager& TM = TacheManager::getInstance();
    ProjetManager& PM = ProjetManager::getInstance();
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
    lab9 = new QLabel("Liste des Taches");
    hlayout_7->addWidget(lab7);
    hlayout_7->addWidget(lab9);


    pred = new QListWidget;

    liste_taches = new QListWidget;
    hlayout_6->addWidget(pred);
    hlayout_6->addWidget(liste_taches);

    for(TacheManager::iterator it = TM.begin(); it != TM.end(); ++it){
        if(*it != tacheToEdit)
            liste_taches->addItem((*it)->getId());
    }



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
        dispo->setDateTime(tache->getDisponibilite());
        echeance->setDateTime(tache->getEcheance());
        duree->setTime(tache->getDuree());
        Projet* tmp = tache->getProjet();
        if(tmp != nullptr)
            projet->addItem(tmp->getId());
        else
            projet->addItem("Sélectionner");
    }else
    projet->addItem("Sélectionner");


    for(ProjetManager::iterator it = PM.begin(); it != PM.end(); ++it){
        if(*it != tache->getProjet())
            projet->addItem((*it)->getId());
    }
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
       dispo->text() != echeance->text() &&
       duree->text() != "00:00"){
        if(!pre->isChecked() && duree->time() > QTime::fromString("12:00","hh:mm")){
            ouvrirWarning("Une tâche non-préemptive doit durer moins de 12h !");
             return;}
        TacheManager& TM = TacheManager::getInstance();
        if(tache == 0){
        //AJOUT DE LA TACHE
        if(TM.getItem(id->text()) != nullptr){
            ouvrirWarning("Attention une tâche possède déjà cet identificateur,\nVeuillez en changer!");
            return;
        }
        TacheUnitaire& t = TM.ajouterTacheUnitaire(id->text(),titre->toPlainText(),duree->time(),pre->isChecked(),dispo->dateTime(),echeance->dateTime());
        if(projet->currentText() != "Sélectionner") //AJOUT DE LA TACHE DANS LE PROJET
              t.setProjet(projet->currentText());

        ouvrirInformation("Tache créée avec succès !\nN'oubliez pas de la programmer !","Félicitations");
        //t.afficher();
        close();
        }
        else{
        if(ouvrirQuestion("Êtes-vous sûr de vouloir modifier cette tâche ?") == QMessageBox::Yes){
            //MODIFICATION DE LA TACHE
        tache->setDisponibiliteDT(dispo->dateTime());
        tache->setDuree(duree->time());
        tache->setTitre(titre->toPlainText());
        tache->setEcheanceDT(echeance->dateTime());
        tache->setId(id->text());
        tache->setPreemptive(pre->isChecked());

        if(tache->getProjet() != nullptr && tache->getProjet()->getId() != projet->currentText())
            tache->setProjet(projet->currentText());
        else if(tache->getProjet() == nullptr && projet->currentText() != "Sélectionner")
            tache->setProjet(projet->currentText());
        ouvrirInformation("Tâche modifiée avec succès!");
        close();
        }}
    }
    else
        ouvrirWarning("Des informations sont manquantes ou érronées !","Erreur");
}
tacheEditeur::~tacheEditeur()
{

}

