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

    ProjetManager& PM = ProjetManager::getInstance();

    for(ProjetManager::iterator it = PM.begin(); it != PM.end(); ++it){
    Projet& projet = (**it);
    QTreeWidgetItem* vueProjet = insertProjet(projet);
    QTreeWidgetItem* tachesUnitaires = insertItem("Taches Unitaires", vueProjet);
    QTreeWidgetItem* tachesComposites = insertItem("Taches Composites", vueProjet);
    QTreeWidgetItem* programmees = insertItem("Programmées", tachesUnitaires);
    QTreeWidgetItem* nonProgrammees = insertItem("Non-Programmées", tachesUnitaires);


    for(Projet::iterator it2 = projet.begin(); it2 != projet.end(); ++it2){
    if((*it2)->whoAmI() == "tache_unitaire"){
        TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(*it2);
        QTreeWidgetItem *tu;

        if(!tmp->isPreemptive())
            tu = insertItem(tmp->getId(),tmp->getDuree().toString(), nonProgrammees);
        else{
            tu = insertItem(tmp->getId(),tmp->getDuree().toString(),"Préemptive", nonProgrammees);
            QTreeWidgetItem *programmations = insertItem("Programmations",tu);
            //affichage des programmations par programmationManager
        }
        insertItem("Prédécesseurs", tu);
    }
    else{
        QTreeWidgetItem* tc = insertItem((*it2)->getId(), tachesComposites);
        insertItem("Taches Composantes", tc);
        insertItem("Prédécesseurs", tc);
    }
   }
  }

  //TACHES AYANT AUCUN PROJET
    QTreeWidgetItem* aucun = new QTreeWidgetItem();
    aucun->setText(PROJET, "Non Défini");
    ui->treeWidget->addTopLevelItem(aucun);
    QTreeWidgetItem* tachesUnitaires = insertItem("Taches Unitaires", aucun);
    QTreeWidgetItem* tachesComposites = insertItem("Taches Composites", aucun);

    TacheManager& TM = TacheManager::getInstance();
    for(TacheManager::iterator it = TM.begin(); it != TM.end(); ++it){
        if((*it)->getProjet() == nullptr){
            if((*it)->whoAmI() == "tache_unitaire"){
                TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(*it);
                QTreeWidgetItem *tu;

                if(!tmp->isPreemptive())
                    tu = insertItem(tmp->getId(),tmp->getDuree().toString(), tachesUnitaires);
                else
                    tu = insertItem(tmp->getId(),tmp->getDuree().toString(),"Préemptive", tachesUnitaires);
                insertItem("Prédécesseurs", tu);
            }
            else{
                QTreeWidgetItem* tc = insertItem((*it)->getId(), tachesComposites);
                insertItem("Taches Composantes", tc);
                insertItem("Prédécesseurs", tc);
            }
    }
    }
}

vueGlobale::~vueGlobale()
{
    delete ui;
}
QTreeWidgetItem* vueGlobale::insertProjet(const Projet& p){
    QTreeWidgetItem* projet = new QTreeWidgetItem();
    projet->setText(PROJET, p.getId());
    ui->treeWidget->addTopLevelItem(projet);
    return projet;
}
QTreeWidgetItem* vueGlobale::insertItem(const QString& nom, QTreeWidgetItem* parent){
    QTreeWidgetItem* categorie = new QTreeWidgetItem();
    categorie->setText(PROJET, nom);
    parent->addChild(categorie);
    return categorie;
}
QTreeWidgetItem* vueGlobale::insertItem(const QString& nom, const QString& duree, QTreeWidgetItem* parent){
    QTreeWidgetItem* categorie = new QTreeWidgetItem();
    categorie->setText(PROJET, nom);
    categorie->setText(IDENTIFICATEUR, nom);
    categorie->setText(DUREE, duree);
    parent->addChild(categorie);
    return categorie;
}
QTreeWidgetItem* vueGlobale::insertItem(const QString& nom, const QString& duree,const QString& prog, QTreeWidgetItem* parent){
    QTreeWidgetItem* categorie = new QTreeWidgetItem();
    categorie->setText(PROJET, nom);
    categorie->setText(IDENTIFICATEUR, nom);
    categorie->setText(DUREE, duree);
    categorie->setText(PROGRAMMATION, prog);
    parent->addChild(categorie);
    return categorie;
}

void vueGlobale::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column){
    if((column == 0 || column == 1) && !item->text(column).isEmpty()){
        // Recherche de la tache, si tache composite lancer:
        TacheManager& TM = TacheManager::getInstance();
        ProjetManager& PM = ProjetManager::getInstance();
        Tache* t = TM.getItem(item->text(column));
        if(t == nullptr){ // Il s'agit d'un projet
            Projet* p = PM.getItem(item->text(column));
            if(p == nullptr)return; //aucun projet trouvé
            ajouterProjet* editeurProjet = new ajouterProjet(p, this);
            editeurProjet->show();
        }
        else{
            if(t->whoAmI() == "tache_unitaire"){

                TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(t);
                tacheEditeur* editeurTacheUnitaire = new tacheEditeur(tmp,this);
                editeurTacheUnitaire->show();
            }
            else{
                TacheComposite* tmp = dynamic_cast<TacheComposite*>(t);
                ajouterTacheComposite* tacheComposite = new ajouterTacheComposite(tmp,this);
                tacheComposite->show();
            }
        }
        this->close();
    }
    else if(column == 2 && !item->text(column).isEmpty()){
        // Recherche de la tache, checker la methode isComposite, si tache unitaire lancer:
        programmationTache* programmation = new programmationTache(0,this);
        programmation->show();
    }
}
