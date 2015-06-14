#include "ajoutertachecomposite.h"
#include "ui_ajoutertachecomposite.h"

ajouterTacheComposite::ajouterTacheComposite(TacheComposite* tache, QWidget *parent) :
    QDialog(parent),tache_composite(tache),
    ui(new Ui::ajouterTacheComposite)
{
    ui->setupUi(this);
    TacheManager& TM = TacheManager::getInstance();
    ProjetManager& PM = ProjetManager::getInstance();
    setWindowTitle("Création d'une Tache Composite");
    ui->dispo->setDateTime(QDateTime::currentDateTime());
    ui->echeance->setDateTime(QDateTime::currentDateTime());

    QObject::connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));

    if(tache != 0){ // SI MODIFICATION
        Projet* p = tache->getProjet();
        ui->identificateur->setText(tache->getId());
        ui->titre->setText(tache->getTitre());
        ui->dispo->setDateTime(tache->getDisponibilite());
        ui->echeance->setDateTime(tache->getEcheance());
        ui->dispo->setMinimumDateTime(p->getDisponibilite());
        ui->echeance->setMaximumDateTime(p->getEcheance());
        ui->projet->setDisabled(true);
        ui->dispo->setDisabled(true);
        ui->echeance->setDisabled(true);
        ui->projet->setDisabled(true);
        ui->composants->setDisabled(true);
        ui->liste_taches_projet->setDisabled(true);
        ui->projet->addItem(p->getId());
        for(TacheComposite::const_iterator it = tache->begin(); it != tache->end(); ++it)
             ui->composants->addItem((*it)->getId());
        vector<Precedence*> Precedences = tache->getPrecedences();
        for(vector<Precedence*>::const_iterator it = Precedences.begin(); it != Precedences.end(); ++it)
            ui->pred->addItem((*it)->getPredecesseur().getId());
    }
    else{ // SI AJOUT ON LISTE LES PROJETS
    for(ProjetManager::iterator it = PM.begin(); it != PM.end(); ++it)
            ui->projet->addItem((*it)->getId());
    }

    // Liste des taches dans la colonne de droite "liste des taches" pour devenir précédente
    for(TacheManager::iterator it = TM.begin(); it != TM.end(); ++it){
        if(*it != tache){ // Si tache = notre tache composite ALORS on ne l'affiche pas dans la liste des pred possibles.
            if(tache != 0){
            TacheComposite::iterator it2 = tache->begin();
            vector<Precedence*> Precedences = tache->getPrecedences();
            vector<Precedence*>::iterator it3 = Precedences.begin();
            while(it2 != tache->end() && *it2 != *it)++it2;
            while(it3 != Precedences.end() && (*it3)->getPredecesseur().getId() != (*it)->getId())++it3;
            if(it2 == tache->end() && it3 == Precedences.end())// Si tache = tache composante ALORS on ne l'affich pas dans la liste des pred possibles.
             ui->liste->addItem((*it)->getId());
             }
            else
             ui->liste->addItem((*it)->getId());
    }}
}

ajouterTacheComposite::~ajouterTacheComposite()
{
    delete ui;
}



void ajouterTacheComposite::on_pushButton_clicked()
{
    bool erreur = false;
    try{

        if(!ui->identificateur->text().isEmpty() &&
           ui->dispo->text() != "00/00/0000 00:00" &&
           ui->dispo->text() != ui->echeance->text() &&
           ui->echeance->text() != "00/00/0000 00:00" &&
           !ui->titre->toPlainText().isEmpty() &&
           ui->composants->count() > 0 &&
           ui->dispo->dateTime() < ui->echeance->dateTime())
        {
            TacheManager& TM = TacheManager::getInstance();
            if(tache_composite == 0){
                //AJOUT DE LA TACHE COMPOSITE
                vector<Tache*> Liste;
                PrecedenceManager& PrM = PrecedenceManager::getInstance();
                ProjetManager& PM = ProjetManager::getInstance();
                if(TM.getItem(ui->identificateur->text()) != nullptr){
                    ouvrirWarning("Attention une tâche possède déjà cet identificateur,\nVeuillez en changer!");
                    return;
                }
                for(int i = 0; i < ui->composants->count(); i++){
                    if(!ui->composants->item(i)->text().isEmpty()){
                    for(int j = 0; j < ui->pred->count(); j++){  //generation à la volée de la liste des composants, pointeurs de tache.
                         if(ui->composants->item(i)->text() == ui->pred->item(j)->text()){ // Si un composant est predecesseur
                             ouvrirWarning("Attention, un composant ne peut pas être prédécesseur");
                             return;
                             }
                    }
                              Liste.push_back(TM.getItem(ui->composants->item(i)->text()));
                     }
                }

                TacheComposite& t = TM.ajouterTacheComposite(ui->identificateur->text(), ui->titre->toPlainText(),ui->dispo->dateTime(), ui->echeance->dateTime(), Liste);
                t.setProjet(*PM.getItem(ui->projet->currentText()));
                for(int i = 0; i < ui->pred->count(); ++i)
                    PrM.ajouterPrecedence(*TM.getItem(ui->pred->item(i)->text()), t);
                t.afficher();

                if(!erreur){
                    ouvrirInformation("Tache Composite créée avec succès!\nN'oubliez pas de programmer ses tâches unitaires !");
                }
                else
                    ouvrirWarning("Des erreurs ont eu lieu, veuillez-vérifier la tâche composite dans la vue globale !");

                close();
            }else{
                //MODIFICATION DE LA TACHE COMPOSITE

             if(tache_composite->getId() != ui->identificateur->text() && TM.getItem(ui->identificateur->text()) == 0)
                tache_composite->setId(ui->identificateur->text());
             else if (tache_composite->getId() != ui->identificateur->text()){
                 ouvrirWarning("Attention, une tache ayant cet identificateur est déjà existant !");
                 return;
             }
             tache_composite->setTitre(ui->titre->toPlainText());
             try{
             PrecedenceManager& PrM = PrecedenceManager::getInstance();
             vector<Precedence*> Precedences = tache_composite->getPrecedences();
             for(vector<Precedence*>::iterator it = Precedences.begin(); it != Precedences.end(); ++it)
                 PrM.deleteItem(*it);
             for(int i = 0; i < ui->pred->count(); i++){
                 if(!ui->pred->item(i)->text().isEmpty())
                     PrM.ajouterPrecedence(*TM.getItem(ui->pred->item(i)->text()), *tache_composite);
             }

             }catch(const char* s){ ouvrirWarning(s);}
             ouvrirInformation("Tache Composite modifiée avec succès!\n");
            close();
            }
        }
        else
            ouvrirWarning("Des informations sont manquantes !","Erreur");
    }
    catch(const char* s){
             ouvrirWarning(QString(s));
             erreur = true;
    }
}

void ajouterTacheComposite::on_projet_currentIndexChanged(const QString &projet)
{
    ui->liste_taches_projet->clear();
    ProjetManager& PM = ProjetManager::getInstance();
    Projet* p = PM.getItem(projet);
    for(Projet::iterator it = p->begin(); it != p->end(); ++it){
        ui->liste_taches_projet->addItem((*it)->getId());
    }
}
