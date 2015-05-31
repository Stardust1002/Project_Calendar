#include "programmationtache.h"
#include "ui_programmationtache.h"

programmationTache::programmationTache(Tache* tache, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::programmationTache)
{

    ui->setupUi(this);
    setWindowTitle("Programmation d'une Tache");
    ui->programmation->setDateTime(QDateTime::currentDateTime());
    if(ui->tache->currentText().isEmpty()){
        ui->dispo->setDateTime(QDateTime::currentDateTime());
    }

    ui->programmation->setDateTimeRange(ui->dispo->dateTime(),ui->echeance->dateTime());
    ui->dispo->setEnabled(false);
    ui->echeance->setEnabled(false);

    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

programmationTache::~programmationTache()
{
    delete ui;
}

void programmationTache::on_programmer_clicked()
{
    if(!ui->projet->currentText().isEmpty() &&
       !ui->projet->currentText().isEmpty() &&
       ui->dispo->dateTime() <= ui->programmation->dateTime() &&
       ui->echeance->dateTime() > ui->programmation->dateTime()) //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DE LA PROGRAMMATION TACHE
            ouvrirInformation("Programmation créée avec succès!\n");
            this->~programmationTache();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");

}

void programmationTache::on_deprog_clicked()
{
    if(ui->statut->currentText() == "Programmée" && !ui->tache->currentText().isEmpty()) //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ouvrirQuestion("Êtes-vous sûr de vouloir la déprogrammer ?","Attention") == QMessageBox::Yes){
            // DEPROGRAMMATION TACHE
            ouvrirInformation("Tâche déprogrammée avec succès !\n");
            this->~programmationTache();
        }
    }
    else
        ouvrirWarning("La tâche n'est pas programmée ou non-selectionnée !","Erreur");
}
