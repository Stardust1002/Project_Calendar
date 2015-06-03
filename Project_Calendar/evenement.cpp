#include "evenement.h"
#include "manager.h"


const Tache& Tache::operator=(const Tache& t){
    identificateur = t.getId();
    titre = t.getTitre();
    date_echeance = t.getEcheance();
    date_dispo = t.getDisponibilite();
    return *this;
}


void Tache::setDisponibilite(const QString& d){
    qDebug()<<d;
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime dispo = QDateTime::fromString(d,format);
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    qDebug()<<dispo;
    setDisponibiliteDT(dispo);
}
void Tache::setEcheance(const QString& e){
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime echeance = QDateTime::fromString(e,format);
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    setEcheanceDT(echeance);
}

TacheComposite::~TacheComposite(){
    qDebug()<<"Destruction tache composite\n";
    for(iterator it = this->tab.begin(); it != this->tab.end(); ++it)
        TacheManager::getInstance().supprimerTache(**it);
    this->tab.clear();
}
/*Projet::Projet(QString id, QString t, QDateTime d, vector<Tache*> t):identificateur(id), titre(t), date_dispo(d){
    for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it){
       tab.push_back(*it);
    }
}
*/
TacheComposite::TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance):Tache(id, title,date_dispo,date_echeance){
    for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it)
        tab.push_back(*it);
}

void TacheComposite::setDisponibiliteDT(const QDateTime& dispo){
    iterator it = tab.begin();
    const QDateTime* minDispo = &(*it)->getDisponibilite();
    it++;
    for(;it != tab.end();it++)
        if((*it)->getDisponibilite() < *minDispo)
            minDispo = &(*it)->getDisponibilite();
    qDebug()<<"minDispo : "<<*minDispo<<"\tdispo : "<<dispo;
    if(*minDispo < dispo)
        throw "error : Tache Composite possédant une tache disponible avant elle même";
    Tache::setDisponibiliteDT(dispo);
}

void TacheComposite::setEcheanceDT(const QDateTime& echeance){
    iterator it = tab.begin();
    const QDateTime* maxEcheance = &(*it)->getDisponibilite();
    for(;it != tab.end();it++)
        if((*it)->getDisponibilite() > *maxEcheance)
            maxEcheance = &(*it)->getDisponibilite();
    if(*maxEcheance < echeance)
        throw "error : Tache Composite possédant une tache devant être terminée après elle même";
    Tache::setEcheanceDT(echeance);
}

const QDateTime& Projet::getEcheance()const{
    const_iterator it = tab.begin();
    const QDateTime* maxEcheance = &(*it)->getEcheance();
    ++it;
    for(;it != tab.end(); ++it){
        if((*it)->getEcheance() > *maxEcheance)
            maxEcheance = &(*it)->getEcheance();
    }
    return *maxEcheance;
}
void Projet::ajouterTache(Tache* t){
    if(t != 0)tab.push_back(t);
    else throw "Olalala: Tache inexistante";
}

void Projet::retirerTache(Tache* t){
    if(t == 0) throw "Olalala: Tache inexistance";
    for(vector<Tache*>::iterator it = tab.begin(); it != tab.end(); ++it)
        if(*it == t){
            tab.erase(it);
            return;
        }
    throw "Olalala: Tache inexistante";
}
//void Projet::ajouterTache(const QString& id){};
//void Projet::retirerTache(const QString& id){};
//Tache* const rechercherTache(const QString& id){} //à faire une fois les façades mises d'iterator au point

