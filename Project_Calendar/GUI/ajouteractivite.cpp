#include "ajouteractivite.h"
#include "ui_ajouteractivite.h"

ajouterActivite::ajouterActivite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterActivite)
{
    ui->setupUi(this);
    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

ajouterActivite::~ajouterActivite()
{
    delete ui;
}

void ajouterActivite::on_pushButton_clicked()
{
    if(!ui->identificateur->text().isEmpty() &&
       ui->duree->text() != "00:00" &&
       !ui->titre->toPlainText().isEmpty())
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DE L'ACTIVITE
            ouvrirInformation("Activité crée avec succès!\nN'oubliez pas de la programmer !");
            this->~ajouterActivite();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}

