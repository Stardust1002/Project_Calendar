#include "ajouteractivite.h"
#include "ui_ajouteractivite.h"
#include "mainwindow.h"
ajouterActivite::ajouterActivite(Activite *a, QWidget *parent) :
    QDialog(parent),activite(a),parent(parent),
    ui(new Ui::ajouterActivite)
{
    ProgrammationManager& ProgM = ProgrammationManager::getInstance();
    ui->setupUi(this);
    if(activite != 0){
        ui->identificateur->setText(activite->getId());
        ui->titre->setPlainText(activite->getTitre());
        ui->duree->setTime(activite->getDuree());
        if(ProgM.isProgrammee(*activite))
            ui->duree->setDisabled(true);
        ui->type->setCurrentIndex(activite->getType());
    }
    else
        ui->pushButton_2->setDisabled(true);
    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

ajouterActivite::~ajouterActivite()
{
    delete ui;
}

void ajouterActivite::on_pushButton_clicked()
{
    MainWindow* w = dynamic_cast<MainWindow*>(parent);
    if(!ui->identificateur->text().isEmpty() &&
       ui->duree->text() != "00:00" &&
       !ui->titre->toPlainText().isEmpty())
    {
            if(activite == 0){ // AJOUT
            ActiviteManager& AM = ActiviteManager::getInstance();
            if(AM.getItem(ui->identificateur->text()) != nullptr){
                ouvrirWarning("Une activité possède déjà le même identificateur,\n Veuillez-changer l'identificateur !");
                return;
            }
            int type;
            if(ui->type->currentText() == "RDV")
                 type = Activite::RDV;
            else
                type = Activite::REUNION;

            Activite& a = AM.ajouterActivite(ui->identificateur->text(),
                               ui->titre->toPlainText(),
                               static_cast<Activite::TypeActivite>(type),
                               ui->duree->time());
            a.afficher();
            ouvrirInformation("Activité créée avec succès!\nN'oubliez pas de la programmer !");
            close();
            }
            else if(ouvrirQuestion("Êtes-vous sûr de vouloir modifier cette activité ?","Attention")== QMessageBox::Yes){
            activite->setId(ui->identificateur->text());
            activite->setTitre(ui->titre->toPlainText());
            activite->setTypeFromString(ui->type->currentText());
            activite->setDuree(ui->duree->time());
            ouvrirInformation("Activité modifiée avec succès!\n");
            activite->afficher();
            w->refresh_calendar();
            close();
            }
    }
    else
        ouvrirWarning("Des informations sont manquantes !","Erreur");
}


void ajouterActivite::on_pushButton_2_clicked()
{
    if(ouvrirQuestion("Êtes-vous sûr de vouloir supprimer cette activité ?") == QMessageBox::Yes){
        MainWindow* w = dynamic_cast<MainWindow*>(parent);
        ProgrammationManager& PM = ProgrammationManager::getInstance();
        ActiviteManager& AM = ActiviteManager::getInstance();
        if(PM.isProgrammee(*activite))
            PM.deleteItem(activite->getProgrammations()[0]);
        AM.deleteItem(*activite);
    ouvrirInformation("Activité supprimée avec succès !");
    w->refresh_calendar();
    close();
    }
}
