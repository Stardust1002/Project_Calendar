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
    QTableWidgetItem* w = new QTableWidgetItem(QString("CHICAGO INTERVIEW"));
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

void MainWindow::on_newActivity_triggered()
{
    ajouterActivite* activite = new ajouterActivite(this);
    activite->show();
}

void MainWindow::on_actionUnitaire_triggered()
{
    tacheEditeur* tache = new tacheEditeur(0, this);
    tache->show();
}

void MainWindow::on_actionCr_er_un_Projet_triggered()
{
    ajouterProjet* projet = new ajouterProjet(this);
    projet->show();
}

void MainWindow::on_actionComposite_triggered()
{
    ajouterTacheComposite* tache = new ajouterTacheComposite(0, this);
    tache->show();

}

void MainWindow::on_actionProgrammer_une_Tache_triggered()
{
    programmationTache* programmation = new programmationTache(this);
    programmation->show();

}

void MainWindow::on_actionProgrammer_une_Activit_triggered()
{
    programmationActivite* programmation = new programmationActivite(this);
    programmation->show();
}
