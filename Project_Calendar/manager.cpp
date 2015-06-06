#include "manager.h"
#include <ostream>


/* ------------------------------------ */
/* ---------- TACHE MANAGER ----------- */
/* ------------------------------------ */

TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& duree,
                          bool preemptive, const QString& dispo, const QString& echeance){
    QString formatTime = "hh:mm";
    QTimeSpan d = QTimeSpan::fromString(duree, formatTime);
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
TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QTimeSpan& duree,
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


/* ----------------------------------------- */
/* ---------- ACTIVITE MANAGER ------------- */
/* ----------------------------------------- */

Activite& ActiviteManager::ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QString& d){
    QString format = "HH:mm";
    QTimeSpan duree = QTimeSpan::fromString(d,format);
    Activite* activite = new Activite(id,t,ty,duree);
    addItem(*activite);
    return *activite;
}

Activite& ActiviteManager::ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QTimeSpan &d){
    Activite* activite = new Activite(id,t,ty,d);
    addItem(*activite);
    return *activite;
}


/* ------------------------------------- */
/* ---------- PROJET MANAGER ----------- */
/* ------------------------------------- */

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


/* ----------------------------------------- */
/* ---------- PRECEDENCE MANAGER ----------- */
/* ----------------------------------------- */

bool PrecedenceManager::isPredecesseur(const Tache& t1, const Tache& t2)const{
    for(const_iterator it = tab.begin(); it != tab.end() ; it++)
        if(&(*it)->getSuccesseur() == &t2  && (&(*it)->getPredecesseur() == &t1 || isPredecesseur(t1,(*it)->getPredecesseur())))
            return true;
    if(typeid(t2) == typeid(TacheComposite)){
        const TacheComposite& tc2 = dynamic_cast<const TacheComposite&>(t2);
        for(TacheComposite::const_iterator it = tc2.begin(); it != tc2.end() ; it++)
            if(*it == &t1 || isPredecesseur(t1,**it))
                return true;
    }
    return false;
}


/* -------------------------------------------- */
/* ---------- PROGRAMMATION MANAGER ----------- */
/* -------------------------------------------- */

Programmation& ProgrammationManager::ajouterProgrammation(Evenement& evenement,const QDateTime& horaire,const QTimeSpan& duree){
    if(isProgrammable(evenement,horaire,duree) )
        return Programmation(evenement,horaire,duree);
}

Programmation& ProgrammationManager::ajouterProgrammation(Evenement& evenement,const QString& d,const QString& du){
    QDateTime date = QDateTime::fromString(d,"dd:MM:yyyy:HH:mm");
    QTimeSpan duree = QTimeSpan::fromString(du,"HH:mm");

    return ajouterProgrammation(evenement,date,duree);

}

const QTimeSpan& ProgrammationManager::dureeProgrammee(const Evenement& e)const{
    QTimeSpan duree;
    /*bool Preemptive = e.isPreemptive();
    for(const_iterator it = tab.begin(); it!= tab.end() ; it++){
        if(&(*it)->getEvenement() == &t && !Preemptive)
            return (*it)->getDuree;
        else
            duree += (*it)->getEvenement().getDuree();
    }*/
    return duree;
}

bool ProgrammationManager::isProgrammee(const Evenement& e)const{
    if(dureeProgrammee(e) == e.getDuree())
        return true;
    return false;
}

bool ProgrammationManager::isProgrammable(const Evenement& e, const QDateTime& horaire,const QTimeSpan& duree)const{
    if(!isProgrammee(e))
        ;
    return false;
}
