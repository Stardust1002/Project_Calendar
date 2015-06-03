#include "programmationactivite.h"
#include "ui_programmationactivite.h"

programmationActivite::programmationActivite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::programmationActivite)
{
    setWindowTitle("Programmation d'une Activité");
    ui->setupUi(this);
    ui->type->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->programmation->setDateTime(QDateTime::currentDateTime());
    ui->programmation->setDateTimeRange(QDateTime::currentDateTime(), QDateTime::fromString("01:01:2100 23:59","dd:MM:yyyy HH:mm"));
    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

programmationActivite::~programmationActivite()
{
    delete ui;
}

void programmationActivite::on_programmer_clicked()
{
    if(!ui->activite->currentText().isEmpty()) //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ouvrirQuestion("Est-ce là votre ultime bafouille ?") == QMessageBox::Yes){
            //AJOUT DE L'ACTIVITE
            ouvrirInformation("Programmation créée avec succès!\n");
            this->~programmationActivite();
        }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");

}


void programmationActivite::on_deprogrammer_clicked()
{
    if(!ui->activite->currentText().isEmpty() && ui->statut->currentText() == "Programmée") //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ouvrirQuestion("Etes-vous sûr de vouloir la déprogrammer ?","Attention") == QMessageBox::Yes){
            //DEPROGRAMMATION DE L'ACTIVITE
            ouvrirInformation("Activité déprogrammée créée avec succès!\n");
            this->~programmationActivite();
        }
    }
    else
        ouvrirWarning("Activité non-programmée ou non-selectionnée !","Erreur");

}