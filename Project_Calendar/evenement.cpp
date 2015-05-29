#include "evenement.h"
TacheComposite::~TacheComposite(){
        for(vector<Tache*>::iterator it = this->tab.begin(); it != this->tab.end(); ++it)
            delete *it;
        this->tab.clear();
    }
/*Projet::Projet(QString id, QString t, QDateTime d, vector<Tache*> t):identificateur(id), titre(t), date_dispo(d){
    for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it){
       tab.push_back(*it);
    }
}
*/
TacheComposite::TacheComposite(QString id, QString title, vector<Tache*> t, QDateTime date_dispo, QDateTime date_echeance):Tache(id, title,date_dispo,date_echeance){
        for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it)
            tab.push_back(*it);}

QDateTime Projet::getEcheance()const{
        vector<Tache*>::const_iterator it = tab.begin();
        QDateTime echeance = (*it)->getEcheance();
        ++it;
        for(;it != tab.end(); ++it){
            if((*it)->getEcheance() > echeance)
                echeance = (*it)->getEcheance();
        }
        return echeance;
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

