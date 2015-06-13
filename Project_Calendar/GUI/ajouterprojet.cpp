#include "ajouterprojet.h"
#include "ui_ajouterprojet.h"
#include <QFileDialog>

ajouterProjet::ajouterProjet(Projet* proj, QWidget *parent) :
    QDialog(parent),projet(proj),
    ui(new Ui::ajouterProjet)
{
    ui->setupUi(this);
    ui->dispo->setDateTime(QDateTime::currentDateTime());
    if(projet != nullptr){
        ui->pushButton_2->setEnabled(true);
        ui->identificateur->setText(projet->getId());
        ui->titre->setPlainText(projet->getTitre());
        ui->dispo->setDateTime(projet->getDisponibilite());
        if(projet->getSize() > 0) // SI une tache fait partie du projet, on ne peut plus avancer la date de dispo, on la bloque.
            ui->dispo->setDateTimeRange(QDateTime::fromString("01:01:2000:00:00", "dd:MM:yyyy:HH:mm"), projet->getDisponibilite());
    }



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
     if(projet == nullptr){
            //AJOUT DU PROJET
            ProjetManager& PM = ProjetManager::getInstance();
            if(PM.getItem(ui->identificateur->text()) != nullptr){
                ouvrirWarning("Un projet avec le même identificateur est déjà existant !","Erreur");
                return;
            }
            Projet& P = PM.ajouterProjet(ui->identificateur->text(),ui->titre->toPlainText(), ui->dispo->dateTime());
            P.afficher();
            ouvrirInformation("Projet créé avec succès!\nN'oubliez pas d'ajouter des taches !");
            close();
     }
     else{
         // MODIFICATION DU PROJET
         if(ouvrirQuestion("Êtes-vous sûr de vouloir modifier ce projet ?", "Attention") == QMessageBox::No)return;
         projet->setId(ui->identificateur->text());
         projet->setDisponibilite(ui->dispo->dateTime());
         projet->setTitre(ui->titre->toPlainText());
         projet->afficher();
        ouvrirInformation("Projet modifié avec succès !", "Félicitations");
        close();
     }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}

void ajouterProjet::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Enregistrer sous","./","XML File (*.xml)");
    if(!filename.isNull()){
        try{
          ///  Memento::getInstance(XML::getInstance(filename)).save();
          /// Ajouter methode de sauvegarde de projet
        }
        catch(const char* s){
            ouvrirWarning(QString(s));
        }
    }
}
