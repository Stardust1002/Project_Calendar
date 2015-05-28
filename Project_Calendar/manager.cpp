#include "manager.h"

void TacheManager::supprimerTache(QString id){
    for(vector<Tache*>::iterator it = this->tab.begin(); it != this->tab.end(); ++it){
        if((*it)->getId() == id){
            delete *it;
            break;
        }
    }
}
