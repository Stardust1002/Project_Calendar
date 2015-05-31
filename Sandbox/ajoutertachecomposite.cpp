#include "ajoutertachecomposite.h"
#include "ui_ajoutertachecomposite.h"

ajouterTacheComposite::ajouterTacheComposite(Tache* tache, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterTacheComposite)
{
    ui->setupUi(this);
    setWindowTitle("Création d'une Tache Composite");
    ui->dispo->setDateTime(QDateTime::currentDateTime());
    ui->echeance->setDateTime(QDateTime::currentDateTime());

    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

    if(tache != 0){
        ui->identificateur->setText(tache->getId());
        ui->titre->setText(tache->getTitre());
        //recherche du projet
        //dispo->setDateTime(tache->getDateDisponibilite());
        //echeance->setDateTime(tache->getDateDisponibilite());

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
       ui->echeance->text() != "00/00/0000 00:00" &&
       !ui->titre->toPlainText().isEmpty() &&
       ui->composants->count() > 0 &&
       ui->dispo->dateTime() < ui->echeance->dateTime())
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DU PROJET
            ouvrirInformation("Tache Composite créée avec succès!\nN'oubliez pas de programmer ses tâches unitaires !");
            this->~ajouterTacheComposite();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}
