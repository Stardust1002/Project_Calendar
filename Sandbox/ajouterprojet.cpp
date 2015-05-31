#include "ajouterprojet.h"
#include "ui_ajouterprojet.h"
#include "fonctions.h"

ajouterProjet::ajouterProjet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterProjet)
{
    ui->setupUi(this);
    ui->dispo->setDateTime(QDateTime::currentDateTime());
    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

ajouterProjet::~ajouterProjet()
{
    delete ui;
}

void ajouterProjet::on_pushButton_clicked()
{
    if(!ui->identificateur->text().isEmpty() &&
       ui->dispo->text() != "00/00/0000 00:00" &&
       !ui->titre->toPlainText().isEmpty())
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DU PROJET
            ouvrirInformation("Projet créé avec succès!\nN'oubliez pas d'ajouter des taches !");
            this->~ajouterProjet();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}
