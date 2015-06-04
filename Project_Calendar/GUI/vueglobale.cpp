#include "vueglobale.h"
#include "ui_vueglobale.h"

vueGlobale::vueGlobale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vueGlobale)
{
    ui->setupUi(this);
    ui->treeWidget->resizeColumnToContents(1);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(3);

}

vueGlobale::~vueGlobale()
{
    delete ui;
}



void vueGlobale::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(column == 1 && !item->text(column).isEmpty()){
        // Recherche de la tache, si tache composite lancer:
        ajouterTacheComposite* tacheComposite = new ajouterTacheComposite(0,this);
        tacheComposite->show();
        // SINON lancer tacheEditeur.h
    }
    else if(column == 2 && !item->text(column).isEmpty()){
        // Recherche de la tache, checker la methode isComposite, si tache unitaire lancer:
        programmationTache* programmation = new programmationTache(0,this);
        programmation->show();
        // SINON lancer tacheEditeur.h
    }
    else if(column == 0 && !item->text(column).isEmpty()){
        //Recherche du projet correspondant, et le modifier
        ajouterProjet* projet = new ajouterProjet(0, this);
       projet->show();
    }
}
