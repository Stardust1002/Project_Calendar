#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QStandardItemModel* model = new QStandardItemModel(2,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("LUNDI")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("MARDI")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("MERCREDI")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("JEUDI")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("VENDREDI")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("SAMEDI")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("DIMANCHE")));
    ui->tableView->setModel(model);
*/
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem* w = new QTableWidgetItem(QString("Se branler"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, LUNDI, w);
    ui->tableWidget->item(0,0)->setBackgroundColor(QColor("YELLOW"));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem* w2 = new QTableWidgetItem(QString("RENDU NA17"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, MARDI, w2);

    QTableWidgetItem* w3 = new QTableWidgetItem(QString("SOPRA STERIA"));
    ui->tableWidget->setItem(0, JEUDI, w3);
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
    int jour = date.dayOfWeek();
    int mois = date.month();
    int annee = date.year();
    int semaine = date.weekNumber(&annee);
    ui->tableWidget->selectColumn(jour-1);
    //Créer une méthode qui charge les données de la semaine avec le numéro de semaine et l'année !

    qDebug() << "Jour" << jour << "de la" << semaine << "ième semaine de" << annee;
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    qDebug() << "Evenement: " << item->text();

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

      TacheManager& TM = TacheManager::getInstance();
      TacheUnitaire* t = dynamic_cast<TacheUnitaire*>(TM.getItem(item->text()));
      if(t!=nullptr){
          t->afficher();
                  t->afficher();
                  ui->groupBox->setEnabled(true);
                  ui->identificateur->setText(t->getId());
                  ui->titre->setText(t->getTitre());
                  ui->duree->setText(t->getDuree().toString());
                  ui->type->setText(t->whoAmI());
      }
      else{
      ActiviteManager& AM = ActiviteManager::getInstance();
      Activite* a = AM.getItem(item->text());
      if(a == nullptr)return;
      a->afficher();
      ui->groupBox->setEnabled(true);
      ui->identificateur->setText(a->getId());
      ui->titre->setText(a->getTitre());
      ui->duree->setText(a->getDuree().toString());
      ui->type->setText(a->getTypeToString());
    }

}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    TacheManager& TM = TacheManager::getInstance();
    TacheUnitaire* t = dynamic_cast<TacheUnitaire*>(TM.getItem(item->text()));
    if(t!=nullptr){
        t->afficher();
        on_actionUnitaire_triggered(t);
    }
    else{
    ActiviteManager& AM = ActiviteManager::getInstance();
    Activite* a = AM.getItem(item->text());
    if(a == nullptr)return;
    a->afficher();
    on_newActivity_triggered(a);
    }
}

void MainWindow::on_voir_clicked()
{
    on_actionUnitaire_triggered();
}

void MainWindow::on_actionVue_Globale_triggered()
{
    vueGlobale* vue = new vueGlobale(this);
    vue->show();
}
