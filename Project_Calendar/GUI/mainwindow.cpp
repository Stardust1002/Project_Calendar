#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), date_calendrier(QDate::currentDate()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh_calendar(date_calendrier);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newActivity_triggered(Activite* a)
{
    ajouterActivite* activite = new ajouterActivite(a, this);
    activite->show();
}

void MainWindow::on_actionUnitaire_triggered(TacheUnitaire* t)
{
    tacheEditeur* tache = new tacheEditeur(t, this);
    tache->show();
}


void MainWindow::on_actionCr_er_un_Projet_triggered(Projet* p)
{
    ajouterProjet* projet = new ajouterProjet(p, this);
    projet->show();
}

void MainWindow::on_actionComposite_triggered()
{
    ajouterTacheComposite* tache = new ajouterTacheComposite(0, this);
    tache->show();

}

void MainWindow::on_actionProgrammer_une_Tache_triggered()
{
    programmationTache* programmation = new programmationTache(0,this);
    programmation->show();

}

void MainWindow::on_actionProgrammer_une_Activit_triggered()
{
    programmationActivite* programmation = new programmationActivite(this); //Faire surcharge pour modifier activité
    programmation->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    programmationTache* programmation = new programmationTache(0,this);
    programmation->show();

}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    refresh_calendar(date);
}

void MainWindow::refresh_calendar(const QDate& date){
    date_calendrier = date;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ProgrammationManager& ProM = ProgrammationManager::getInstance();
    int jour = date.dayOfWeek();
    int annee;
    int semaine = date.weekNumber(&annee);
    int max = 0;
    vector<Programmation*> liste = ProM.getProgrammations(semaine,annee);
    vector<int> jours(7,0);

    for(vector<Programmation*>::iterator it = liste.begin(); it != liste.end(); ++it){
        const QString& nom = (*it)->getEvenement().getId();
        const QString& heure = (*it)->getDate().time().toString("HH:mm");
        QDate& date = (*it)->getDate().date();
        qDebug() << nom;
        if(max == jours[date.dayOfWeek()-1])
            ui->tableWidget->setRowCount(++max);

        ui->tableWidget->setItem(jours[date.dayOfWeek()-1]++,date.dayOfWeek()-1, new QTableWidgetItem(heure + " | " + nom));
        if((*it)->getEvenement().whoAmI() != "tache_unitaire")//ACTIVITE EN BLEU
                ui->tableWidget->item(jours[date.dayOfWeek()-1]-1,date.dayOfWeek()-1)->setBackgroundColor(QColor(0, 0, 255, 57));
        else //TACHES UNITAIRES EN ROUGE
                ui->tableWidget->item(jours[date.dayOfWeek()-1]-1,date.dayOfWeek()-1)->setBackgroundColor(QColor(255, 0, 0, 57));

    }
    ui->tableWidget->selectColumn(jour-1);
}
void MainWindow::refresh_calendar(){
    refresh_calendar(date_calendrier);
}



void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
//    qDebug() << "Evenement: " << item->text();

    //AFFICHAGE de l'évènement dans le cadre du bord droit
    //Récupérer toutes les informations d'un évènement suivant un identificateur
    //checker programmation manager pour récuperer l'evenement et demander son type avec whoAmI

    //Si tache unitaire
//    TacheManager& TM = TacheManager::getInstance();
//    TacheUnitaire* t = dynamic_cast<TacheUnitaire*>(TM.getItem(item->text()));
//    if(t==nullptr)return;
//        t->afficher();
//        ui->groupBox->setEnabled(true);
//        ui->identificateur->setText(t->getId());
//        ui->titre->setText(t->getTitre());
//        ui->duree->setText(t->getDuree().toString());

//
    //Si evenement
      const QStringList& liste = item->text().split(" | ");
      const QString& identificateur = liste[1];
      const QString& horaire = liste[0];
      const QStringList& time = horaire.split(":");

      // on retrouve le jour de la semaine pour reformer la date complète et avoir accès à la programmation

      int mois,annee,j;
      date_calendrier.getDate(&annee,&mois,&j);
      j = j + 1 - date_calendrier.dayOfWeek() + item->column();

      QDateTime prog(QDate(annee,mois,j),QTime(time[0].toInt(),time[1].toInt(),0,0));
      qDebug() << prog.toString();

      TacheManager& TM = TacheManager::getInstance();
      TacheUnitaire* t = dynamic_cast<TacheUnitaire*>(TM.getItem(identificateur));
      ProgrammationManager& ProgM = ProgrammationManager::getInstance();
      qDebug() << ProgM.getProgrammation(prog)->getEvenement().getId();

      if(t!=nullptr){
                  ui->groupBox->setEnabled(true);
                  ui->identificateur->setText(t->getId());
                  ui->titre->setText(t->getTitre());
                  ui->duree->setText(t->getDuree().toString());
                  ui->type->setText(t->whoAmI());
      }
      else{
      ActiviteManager& AM = ActiviteManager::getInstance();
      Activite* a = AM.getItem(identificateur);
      if(a == nullptr)return;
      ui->groupBox->setEnabled(true);
      ui->identificateur->setText(a->getId());
      ui->titre->setText(a->getTitre());
      ui->duree->setText(a->getDuree().toString());
      ui->type->setText(a->getTypeToString());
    }

}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    const QStringList& liste = item->text().split(" | ");
    const QString& identificateur = liste[1];
    const QString& horaire = liste[0];
    TacheManager& TM = TacheManager::getInstance();
    TacheUnitaire* t = dynamic_cast<TacheUnitaire*>(TM.getItem(identificateur));
    if(t!=nullptr){
        t->afficher();
        on_actionUnitaire_triggered(t);
    }
    else{
    ActiviteManager& AM = ActiviteManager::getInstance();
    Activite* a = AM.getItem(identificateur);
    if(a == nullptr)return;
    a->afficher();
    on_newActivity_triggered(a);
    }
}

void MainWindow::on_voir_clicked()
{
    TacheManager& TM = TacheManager::getInstance();
    ActiviteManager& AM = ActiviteManager::getInstance();

    if(ui->type->text() == "tache_unitaire"){
        TacheUnitaire* e = dynamic_cast<TacheUnitaire*>(TM.getItem(ui->identificateur->text()));
        on_actionUnitaire_triggered(e);
    }
    else{
        Activite* e = AM.getItem(ui->identificateur->text());
        on_newActivity_triggered(e);
}
}

void MainWindow::on_actionVue_Globale_triggered()
{
    vueGlobale* vue = new vueGlobale(this);
    vue->show();
}



const QDate& MainWindow::getCurrentDate()const{
    return date_calendrier;
}

