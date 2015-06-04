#include "manager.h"
#include <ostream>

TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& duree,
                          bool preemptive, const QString& dispo, const QString& echeance){
    QString formatTime = "hh:mm";
    QTime d = QTime::fromString(duree, formatTime);
    QString formatDateTime = "dd:MM:yyyy:HH:mm";
    QDateTime date_dispo = QDateTime::fromString(dispo,formatDateTime);
    if(!date_dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    QDateTime date_echeance = QDateTime::fromString(echeance,formatDateTime);
    if(!date_echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    TacheUnitaire* t = new TacheUnitaire(id, titre, d, preemptive, date_dispo, date_echeance);
    addItem(*t);
    return *t;
}
TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QTime& duree,
                          bool preemptive,const QDateTime& dispo, const QDateTime& echeance){
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    TacheUnitaire* t = new TacheUnitaire(id, titre, duree, preemptive, dispo, echeance);
    addItem(*t);
    return *t;
}

TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& titre, const QString& dispo, const QString& echeance, vector<Tache*> liste){
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime date_dispo = QDateTime::fromString(dispo,format);
    qDebug()<<dispo<<"\t"<<date_dispo;
    if(!date_dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    QDateTime date_echeance = QDateTime::fromString(echeance,format);
    if(!date_echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    TacheComposite* t = new TacheComposite(id, titre, liste, date_dispo, date_echeance);
    addItem(*t);
    return *t;
 }
TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& titre, const QDateTime& dispo, const QDateTime& echeance, vector<Tache*> liste){
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    TacheComposite* t = new TacheComposite(id, titre, liste, dispo, echeance);
    addItem(*t);
    return *t;
 }

Activite& ActiviteManager::ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QString& d){
    QString format = "HH:mm";
    QTime duree = QTime::fromString(d,format);
    Activite* activite = new Activite(id,t,ty,duree);
         addItem(*activite);
        return *activite;
}

Activite& ActiviteManager::ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QTime &d){
        Activite* activite = new Activite(id,t,ty,d);
         addItem(*activite);
        return *activite;
}

Projet& ProjetManager::ajouterProjet(const QString& id, const QString& titre, const QString& dispo){
   QString format = "dd:MM:yyyy:HH:mm";
   QDateTime date_dispo = QDateTime::fromString(dispo,format);
    Projet* t = new Projet(id, titre, date_dispo);
    addItem(*t);
    return *t;
}
Projet& ProjetManager::ajouterProjet(const QString& id, const QString& titre, const QDateTime& dispo){
    Projet* t = new Projet(id,titre,dispo);
    addItem(*t);
    return *t;
}


