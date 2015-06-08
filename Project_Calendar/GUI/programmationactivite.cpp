#include "programmationactivite.h"
#include "ui_programmationactivite.h"
#include "mainwindow.h"
programmationActivite::programmationActivite(Activite* activite, QWidget *parent) :
    QDialog(parent), activite(activite),parent(parent),
    ui(new Ui::programmationActivite)
{
    ActiviteManager& AM = ActiviteManager::getInstance();
    setWindowTitle("Programmation d'une Activité");
    ui->setupUi(this);
    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

    if(activite != 0){
             ui->status->setCurrentIndex(1);
             on_status_currentIndexChanged(1);
    }
    else{
        qDebug() << "hello?";
        ui->status->setCurrentIndex(0);
        on_status_currentIndexChanged(0);
        qDebug() << "hello!";
    }

    if(ui->activity->currentText().isEmpty() && activite == 0){//Si aucune activité à programmer
       on_status_currentIndexChanged(1); //on place le selecteur sur les activité déjà programmées
       ui->status->setCurrentIndex(1);
       if(!ui->activity->currentText().isEmpty() && activite == 0)//si une activité programmée existe
           activite = AM.getItem(ui->activity->currentText());
       else //aucune activité déjà programmée
            throw "Aucune activité n'est créée !\nPourquoi ne pas en ajouter une ?";
        }
    else if(activite == 0)
        activite = AM.getItem(ui->activity->currentText());


    ui->type->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->type->setCurrentText(activite->getTypeToString());
    ui->textEdit->setText(activite->getTitre());
    ui->programmation->setDateTime(activite->getProgrammations()[0]->getDate());
    ui->duree->setDisabled(true);
    ui->duree->setTime(activite->getDuree());
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
        if(ui->activity->currentText().isEmpty()){
            ouvrirWarning("Veuillez-selectionner une activité !");
            return;
        }
        Activite* act = AM.getItem(ui->activity->currentText());
        if(ProgM.isProgrammee(*act)){
            Programmation* programmation = act->getProgrammations()[0];
            ProgM.deleteItem(programmation);
         }

        ProgM.ajouterProgrammation(*act,ui->programmation->dateTime(),ui->duree->time());
        ouvrirInformation("Programmation ajoutée/modifée avec succès !");
        w->refresh_calendar();
        close();

    }catch(const char* s){ouvrirWarning(s);};
}


void programmationActivite::on_deprogrammer_clicked()
{
    if(!ui->activity->currentText().isEmpty() && ui->status->currentText() == "Programmée") //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ouvrirQuestion("Etes-vous sûr de vouloir la déprogrammer ?","Attention") == QMessageBox::Yes){
            MainWindow* w = dynamic_cast<MainWindow*>(parent);
            ProgrammationManager& ProgM = ProgrammationManager::getInstance();
            ActiviteManager& AM = ActiviteManager::getInstance();
            ProgM.deleteItem(AM.getItem(ui->activity->currentText())->getProgrammations()[0]);
            ouvrirInformation("Activité déprogrammée créée avec succès!\n");
            w->refresh_calendar();
            close();
        }
    }
    else
        ouvrirWarning("Activité non-programmée ou non-selectionnée !","Erreur");

}



void programmationActivite::on_status_currentIndexChanged(int index)
{
    ActiviteManager& AM = ActiviteManager::getInstance();
    ProgrammationManager& ProgM = ProgrammationManager::getInstance();
    ui->activity->clear();

    if(index == 0){ // on récupère les evts non programmées
        for(ActiviteManager::const_iterator it = AM.begin(); it != AM.end(); ++it){
            QString tmp =(*it)->getId();
            if(!ProgM.isProgrammee(**it)){
                ouvrirWarning((*it)->getId()); //////////ERREUR WTFFFF
                ui->activity->addItem((*it)->getId());
            }
        }
    }else{ // on récupère les evts déjà programmées
        for(ActiviteManager::const_iterator it = AM.begin(); it != AM.end(); ++it){
            if(ProgM.isProgrammee(**it))
                ui->activity->addItem((*it)->getId());
            if(*it == activite)
                ui->activity->setCurrentIndex(ui->activity->count()-1);
        }
    }
}

void programmationActivite::on_activity_currentIndexChanged(const QString &arg1)
{
    if(arg1.isEmpty())return;
    ActiviteManager& AM = ActiviteManager::getInstance();
    Activite* act = AM.getItem(arg1);
    ui->type->setCurrentText(act->getTypeToString());
    ui->textEdit->setText(act->getTitre());
    ui->programmation->setDateTime(act->getProgrammations()[0]->getDate());
    ui->duree->setDisabled(true);
    ui->duree->setTime(act->getDuree());
}
