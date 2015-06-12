#include "programmationtache.h"
#include "ui_programmationtache.h"
#include "mainwindow.h"
programmationTache::programmationTache(TacheUnitaire* tache, QWidget *parent) :
    QDialog(parent),tache(tache),parent(parent),
    ui(new Ui::programmationTache)
{
    try{
    ui->setupUi(this);
    setWindowTitle("Programmation d'une Tache");

   ProgrammationManager& ProgM = ProgrammationManager::getInstance();
   TacheManager& TM = TacheManager::getInstance();
   QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

   if(tache != 0 && ProgM.isProgrammee(*tache)){
             ui->statut->setCurrentIndex(1);
             on_statut_activated(1);
    }
    else if(tache != 0 && !tache->isPreemptive()){
        ui->statut->setCurrentIndex(0);
        on_statut_activated(0);
    }
   else if(tache != 0){
       ui->statut->setCurrentIndex(2);
       on_statut_activated(2);
   }

    if(ui->tache->currentText().isEmpty() && tache == 0){//Si aucune activité à programmer
       on_statut_activated(2); //on place le selecteur sur les taches preemptives à programmer
       ui->statut->setCurrentIndex(2);
       if(!ui->tache->currentText().isEmpty() && tache == 0)//si une tache preemptive  existe
           tache = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));
       else{
           on_statut_activated(1);
           ui->statut->setCurrentIndex(1);
           if(!ui->tache->currentText().isEmpty() && tache == 0)
               tache = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));
           else
            throw "Aucune tache n'est créée ou liée à un projet !\nPourquoi ne pas en ajouter une ?";
        }
    }
    else if(tache == 0)
        tache =dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));


    ui->dispo->setEnabled(false);
    ui->echeance->setEnabled(false);
    ui->label_duree->setDisabled(true);

    vector<Programmation*>& prog = tache->getProgrammations();
    if(prog.size() == 1)
        ui->programmation->setDateTime(prog[0]->getDate());

}
    catch(const char* s){ouvrirWarning(s);}
}

programmationTache::~programmationTache()
{
    delete ui;
}

void programmationTache::on_programmer_clicked()
{
     ProgrammationManager& ProgM = ProgrammationManager::getInstance();
     TacheManager& TM = TacheManager::getInstance();
     MainWindow* w = dynamic_cast<MainWindow*>(parent);

     try{
         if(ui->tache->currentText().isEmpty()){
             ouvrirWarning("Veuillez-selectionner une tâche !");
             return;
         }
         TacheUnitaire* act = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));
         if(!act->isPreemptive() && ProgM.isProgrammee(*act)){
             Programmation* programmation = act->getProgrammations()[0];
             ProgM.deleteItem(programmation);
          }
         else if(act->isPreemptive() && ui->listeprogrammation->currentText() != "Nouvelle Programmation" ){
             int index = ui->listeprogrammation->currentIndex();
             ouvrirInformation(QString::number(index));
             Programmation* programmation = act->getProgrammations()[index];
             ProgM.deleteItem(programmation);
         }

         ProgM.ajouterProgrammation(*act,ui->programmation->dateTime(),ui->duree->time());
         ouvrirInformation("Programmation ajoutée/modifée avec succès !");
         w->refresh_calendar();
         close();


     }catch(const char* s){ouvrirWarning(s);};
}

void programmationTache::on_deprog_clicked()
{
    try{
    if(!ui->tache->currentText().isEmpty() && ui->statut->currentText() != "Non-Programmée") //faire un operateur d'addition pour comparer fin+durée et comparer avec pred et succ
    {
        if(ui->statut->currentText() != "Programmée" && ui->listeprogrammation->currentText() == "Nouvelle Programmation"){
            ouvrirWarning("Veuillez-selectionner une tâche !");
             return;
        }
        if(ouvrirQuestion("Etes-vous sûr de vouloir la dé-programmer ?","Attention") == QMessageBox::Yes){
            MainWindow* w = dynamic_cast<MainWindow*>(parent);
            ProgrammationManager& ProgM = ProgrammationManager::getInstance();
            TacheManager& TM = TacheManager::getInstance();
            TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));
            if(!tmp->isPreemptive())
                 ProgM.deleteItem(tmp->getProgrammations()[0]);
            else{
                int index = ui->listeprogrammation->currentIndex();
                Programmation* programmation = tmp->getProgrammations()[index];
                ProgM.deleteItem(programmation);
            }
            ouvrirInformation("Tache dé-programmée avec succès!\n");
            w->refresh_calendar();
            close();
        }
    }
    else
        ouvrirWarning("Tache non-programmée ou non-selectionnée !","Erreur");
    }catch(const char* s){ouvrirWarning(s);}
}

void programmationTache::on_statut_activated(int index)
{
    TacheManager& TM = TacheManager::getInstance();
    ProgrammationManager& ProgM = ProgrammationManager::getInstance();
    ui->tache->clear();
    if(index == 0){ // on récupère les evts non programmés et non preemptifs, ayant été liés dans un projet
        for(TacheManager::const_iterator it = TM.begin(); it != TM.end(); ++it){
            if((*it)->whoAmI() == "tache_composite" || (*it)->getProjet() == 0)continue;
            TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(*it);
            if(tmp->isPreemptive())continue;
            if(!ProgM.isProgrammee(*tmp)){
                ui->tache->insertItem(-1, tmp->getId());
            }
        }
    }
    else if(index == 1){ // on récupère les evts déjà programmés
        for(TacheManager::const_iterator it = TM.begin(); it != TM.end(); ++it){
            if((*it)->whoAmI() == "tache_composite" || (*it)->getProjet() == 0)continue;
            TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(*it);
            if(ProgM.isProgrammee(*tmp))
                ui->tache->addItem(tmp->getId());
            if(tmp == tache)
                ui->tache->setCurrentIndex(ui->tache->count()-1);
        }
    }
    else{ // on récupère les taches preemptives non programmées
        for(TacheManager::const_iterator it = TM.begin(); it != TM.end(); ++it){
            if((*it)->whoAmI() == "tache_composite"|| (*it)->getProjet() == 0)continue;
            TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(*it);
            if(!tmp->isPreemptive())continue;

            if(!ProgM.isProgrammee(*tmp))
                ui->tache->addItem(tmp->getId());
            if(tmp == tache)
                ui->tache->setCurrentIndex(ui->tache->count()-1);
        }
    }
    //on affiche la première activité de la liste
    on_tache_activated(ui->tache->currentText());
    this->adjustSize();
}

void programmationTache::on_tache_activated(const QString &arg1)
{
    if(!arg1.isEmpty()){
    TacheManager& TM = TacheManager::getInstance();
    TacheUnitaire* act = dynamic_cast<TacheUnitaire*>(TM.getItem(arg1));
    vector<Programmation*>& prog = act->getProgrammations();
    if(prog.size() == 1){
        ui->programmation->setDateTime(prog[0]->getDate());
    }
    else{
    }
    if(!act->isPreemptive()){
        ui->duree->setTime(act->getDuree());
        ui->groupBox_2->setHidden(true);
    }
    else{
        ui->groupBox_2->setHidden(false);
       vector<Programmation*>& programmations = act->getProgrammations();
       QTimeSpan duree_programmee(0,0);
       for(vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++it){
           ui->listeprogrammation->addItem((*it)->getDuree().toString());
           duree_programmee = duree_programmee + (*it)->getDuree();
           qDebug() << duree_programmee;
       }
       duree_programmee = act->getDuree() - duree_programmee;
       if(duree_programmee != QTimeSpan(0,0))
           ui->listeprogrammation->addItem("Nouvelle Programmation");
       ui->listeprogrammation->setCurrentIndex(ui->listeprogrammation->count()-1);
        ui->label_duree_2->setText(duree_programmee.toString());
        ui->duree->setMaximumTime(duree_programmee);
        on_listeprogrammation_activated(ui->listeprogrammation->currentText());
    }

    this->adjustSize();
    ui->label_duree->setText(act->getDuree().toString());
    ui->dispo->setDateTime(act->getDisponibilite());
    ui->echeance->setDateTime(act->getEcheance());

}
}

void programmationTache::on_listeprogrammation_activated(const QString &arg1)
{
    if(arg1.isEmpty())return;
    if(arg1 != "Nouvelle Programmation"){
        TacheManager& TM = TacheManager::getInstance();
        TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->tache->currentText()));
        vector<Programmation*> programmations = tmp->getProgrammations();
        int index = ui->listeprogrammation->currentIndex();
        ui->duree->setTime(programmations[index]->getDuree());
        ui->programmation->setDateTime(programmations[index]->getDate());
    }
}
