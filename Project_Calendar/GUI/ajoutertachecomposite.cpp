#include "ajoutertachecomposite.h"
#include "ui_ajoutertachecomposite.h"

ajouterTacheComposite::ajouterTacheComposite(TacheComposite* tache, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterTacheComposite)
{
    ui->setupUi(this);
    TacheManager& TM = TacheManager::getInstance();
    ProjetManager& PM = ProjetManager::getInstance();
    setWindowTitle("Création d'une Tache Composite");
    ui->dispo->setDateTime(QDateTime::currentDateTime());
    ui->echeance->setDateTime(QDateTime::currentDateTime());

    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

    if(tache != 0){
        ui->identificateur->setText(tache->getId());
        ui->titre->setText(tache->getTitre());

        //recherche du projet
        ui->dispo->setDateTime(tache->getDisponibilite());
        ui->echeance->setDateTime(tache->getEcheance());
        for(TacheComposite::iterator it = tache->begin(); it != tache->end(); ++it)
             ui->composants->addItem((*it)->getId());
        ui->projet->setCurrentText(tache->getProjet()->getId());
    }

    for(ProjetManager::iterator it = PM.begin(); it != PM.end(); ++it){
        if(*it != tache->getProjet())
            ui->projet->addItem((*it)->getId());
    }


    for(TacheManager::iterator it = TM.begin(); it != TM.end(); ++it){
        if(*it != tache){ // Si tache = notre tache composite ALORS on ne l'affiche pas dans la liste des pred possibles.
            if(tache != 0){
                TacheComposite::iterator it2 = tache->begin();
            while(it2 != tache->end())++it;
            if(it2 == tache->end())// Si tache = tache composante ALORS on ne l'affich pas dans la liste des pred possibles.
             ui->liste->addItem((*it)->getId());
        }
            else
                ui->liste->addItem((*it)->getId());
    }
}
}

ajouterTacheComposite::~ajouterTacheComposite()
{
    delete ui;
}



void ajouterTacheComposite::on_pushButton_clicked()
{
    if(!ui->identificateur->text().isEmpty() &&
       ui->dispo->text() != "00/00/0000 00:00" &&
       ui->dispo->text() != ui->echeance->text() &&
       ui->echeance->text() != "00/00/0000 00:00" &&
       !ui->titre->toPlainText().isEmpty() &&
       ui->composants->count() > 0 &&
       ui->dispo->dateTime() < ui->echeance->dateTime())
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DE LA TACHE COMPOSITE
            vector<Tache*> Liste;
            TacheManager& TM = TacheManager::getInstance();
            if(TM.getItem(ui->identificateur->text()) != nullptr){
                ouvrirWarning("Attention une tâche possède déjà cet identificateur,\nVeuillez en changer!");
                return;
            }

           for(int i = 0; i < ui->composants->count(); i++) //generation à la volée de la liste des composants, pointeurs de tache.
                 Liste.push_back(TM.getItem(ui->composants->item(i)->text()));

            TacheComposite& t = TM.ajouterTacheComposite(ui->identificateur->text(), ui->titre->toPlainText(),ui->dispo->dateTime(), ui->echeance->dateTime(), Liste);
            t.afficher();
            ouvrirInformation("Tache Composite créée avec succès!\nN'oubliez pas de programmer ses tâches unitaires !");
            this->~ajouterTacheComposite();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}

void ajouterTacheComposite::on_projet_currentIndexChanged(const QString &projet)
{
    ui->liste_taches_projet->clear();
    ProjetManager& PM = ProjetManager::getInstance();
    Projet* p = PM.getItem(projet);
    for(Projet::iterator it = p->begin(); it != p->end(); ++it)
        ui->liste_taches_projet->addItem((*it)->getId());
}
