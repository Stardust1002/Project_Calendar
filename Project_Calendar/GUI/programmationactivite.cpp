#include "programmationactivite.h"
#include "ui_programmationactivite.h"
#include "mainwindow.h"
programmationActivite::programmationActivite(Activite* activite, QWidget *parent) :
    QDialog(parent), activite(activite),parent(parent),
    ui(new Ui::programmationActivite)
{
    ProgrammationManager& ProgM = ProgrammationManager::getInstance();

    setWindowTitle("Programmation d'une Activité");
    ui->setupUi(this);
    if(activite != 0){
    qDebug() << activite->getId();
    if(ProgM.isProgrammee(*activite))
        ui->statut->setCurrentIndex(1);
    else
        ui->statut->setCurrentIndex(0);
    ui->statut->setDisabled(true);
    ui->type->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->type->setCurrentText(activite->getTypeToString());
    ui->textEdit->setText(activite->getTitre());
    ui->programmation->setDateTime(activite->getProgrammations()[0]->getDate());
    ui->activity->addItem(activite->getId());
    ui->activity->setDisabled(true);
    ui->duree->setDisabled(true);
    ui->duree->setTime(activite->getDuree());
    }

    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

}

programmationActivite::~programmationActivite()
{
    delete ui;
}

void programmationActivite::on_programmer_clicked()
{
    ProgrammationManager& ProgM = ProgrammationManager::getInstance();
    ActiviteManager& AM = ActiviteManager::getInstance();
    MainWindow* w = dynamic_cast<MainWindow*>(parent);

    try{

        if(activite != 0){
            Programmation* programmation = activite->getProgrammations()[0];
            ProgM.deleteItem(programmation);
         }
        else{
            Activite* activite = AM.getItem(ui->activity->currentText());
        }
        ProgM.ajouterProgrammation(*activite,ui->programmation->dateTime(),ui->duree->time());
        ouvrirInformation("Programmation ajoutée/modifée avec succès !");
        w->refresh_calendar();
        close();

    }catch(const char* s){ouvrirWarning(s);};
}


void programmationActivite::on_deprogrammer_clicked()
{
    if(!ui->activity->currentText().isEmpty() && ui->statut->currentText() == "Programmée") //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
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
