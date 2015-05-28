#include "evenement.h"
TacheComposite::~TacheComposite(){
        for(vector<Tache*>::iterator it = this->tab.begin(); it != this->tab.end(); ++it)
            delete *it;
        this->tab.clear();
    }
/*Projet::Projet(QString id, QString t, QDate d, vector<Tache*> t):identificateur(id), titre(t), date_dispo(d){
    for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it){
       tab.push_back(*it);
    }
}
*/
