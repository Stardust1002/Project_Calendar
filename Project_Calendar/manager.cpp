#include "manager.h"
#include <ostream>

TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& duree,
                          bool preemptive, const QString& dispo, const QString& echeance){
    QString formatTime = "hh:mm";
    QTime d = QTime::fromString(duree, formatTime);
    QString formatDateTime = "dd:MM:yyyy:HH:mm";
    QDateTime date_dispo = QDateTime::fromString(dispo,formatDateTime);
    QDateTime date_echeance = QDateTime::fromString(echeance,formatDateTime);
    TacheUnitaire* t = new TacheUnitaire(id, titre, d, preemptive, date_dispo, date_echeance);
    addItem(*t);
    return *t;
}

TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& titre, const QString& dispo, const QString& echeance, vector<Tache*> liste){
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime date_dispo = QDateTime::fromString(dispo,format);
    QDateTime date_echeance = QDateTime::fromString(echeance,format);
    TacheComposite* t = new TacheComposite(id, titre, liste, date_dispo, date_echeance);
    addItem(*t);
    return *t;
 }



void TacheManager::supprimerTache(const QString& id){
    iterator it;
    for(it = this->tab.begin(); it != this->tab.end() && (*it)->getId() != id ; ++it);
    supprimerTache(it);
}

void TacheManager::supprimerTache(Tache& tache){
    supprimerTache(tache.getId());
}

void TacheManager::supprimerTache(iterator it){
    Tache* pt = *it;
    tab.erase(it);
    delete pt;
    qDebug()<<"\nTaille : "<<tab.size();
}
