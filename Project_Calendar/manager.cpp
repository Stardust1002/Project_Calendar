#include "manager.h"
#include <ostream>


/* ------------------------------------ */
/* ---------- TACHE MANAGER ----------- */
/* ------------------------------------ */



TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& duree,
                          bool preemptive, const QString& dispo, const QString& echeance){
    QTimeSpan d = QTimeSpan::fromString(duree, "hh:mm");
    QDateTime date_dispo = QDateTime::fromString(dispo,"dd:MM:yyyy:HH:mm");
    QDateTime date_echeance = QDateTime::fromString(echeance,"dd:MM:yyyy:HH:mm");
    return ajouterTacheUnitaire(id, titre, d, preemptive, date_dispo, date_echeance);

}
TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& titre, const QTimeSpan& duree,
                          bool preemptive,const QDateTime& dispo, const QDateTime& echeance){
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    if(dispo.date() == echeance.date() && QTimeSpan(0,0).addSecs(dispo.secsTo(echeance)) < duree)
        throw "Erreur : Durée de la tâche supérieur au temps disponible pour la réaliser";
    TacheUnitaire* t = new TacheUnitaire(id, titre, duree, preemptive, dispo, echeance);
    addItem(*t);
    return *t;
}

TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& titre, const QString& dispo, const QString& echeance, vector<Tache*> liste){
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime date_dispo = QDateTime::fromString(dispo,format);
    QDateTime date_echeance = QDateTime::fromString(echeance,format);
    return ajouterTacheComposite(id, titre, date_dispo, date_echeance,liste);
 }
TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& titre, const QDateTime& dispo, const QDateTime& echeance, vector<Tache*> liste){
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    for(iterator it = tab.begin() ; it != tab.end() ; it++)
        if((*it)->getId() == id)
            throw "Error : Identifiant déja utilisé";
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
    if(!dispo.isValid())
        throw "error : Creation de projet impossible";
    Projet* t = new Projet(id,titre,dispo);
    addItem(*t);
    return *t;
}


/* ----------------------------------------- */
/* ---------- PRECEDENCE MANAGER ----------- */
/* ----------------------------------------- */

Precedence&  PrecedenceManager::ajouterPrecedence(const Tache& t1,const Tache& t2){
    if(isPredecesseur(t1,t2) || isPredecesseur(t2,t1))
        throw "Error : Ajout de précédence impossible";
     Precedence* t = new Precedence(t1,t2);
     addItem(*t);
     return *t;
 }

bool PrecedenceManager::isPredecesseur(const Tache& t1, const Tache& t2)const{
    for(const_iterator it = tab.begin(); it != tab.end() ; it++)
        if(&(*it)->getSuccesseur() == &t2  && (&(*it)->getPredecesseur() == &t1 || isPredecesseur(t1,(*it)->getPredecesseur())))
            return true;
    if(typeid(t2) == typeid(const TacheComposite&)){
        const TacheComposite& tc2 = dynamic_cast<const TacheComposite&>(t2);
        for(TacheComposite::const_iterator it = tc2.begin(); it != tc2.end() ; it++)
            if(*it == &t1 || isPredecesseur(t1,**it))
                return true;
    }
    return false;
}
void PrecedenceManager::deleteItem(Precedence *p){
    const_iterator it = tab.begin();
    while(it != tab.end() && *it != p) ++it;
     if(it != tab.end()){
          tab.erase(it);
          delete p;
     }
   }



/* -------------------------------------------- */
/* ---------- PROGRAMMATION MANAGER ----------- */
/* -------------------------------------------- */

Programmation& ProgrammationManager::ajouterProgrammation(Evenement& evenement,const QDateTime& horaire,const QTimeSpan& duree){
    if(!horaire.isValid() || !duree.isValid() || duree == QTimeSpan(0,0) || !isProgrammable(evenement,horaire,duree))
        throw "Error : Evenement non programmable";
    Programmation *prog = new Programmation(evenement,horaire,duree);
    addItem(*prog);
    return *prog;
}

Programmation& ProgrammationManager::ajouterProgrammation(Evenement& evenement,const QString& d,const QString& du){
    QDateTime date = QDateTime::fromString(d,"dd:MM:yyyy:HH:mm");
    QTimeSpan duree = QTimeSpan::fromString(du,"HH:mm");
    return ajouterProgrammation(evenement,date,duree);
}

QTimeSpan ProgrammationManager::dureeProgrammee(const Evenement& e)const{
    QTimeSpan duree(0,0);
    bool Preemptive = e.isPreemptive();
    for(const_iterator it = tab.begin(); it!= tab.end() ; ++it){
        if((&(*it)->getEvenement()) == &e){
                if(!Preemptive)
                    return (*it)->getDuree();
                else
                    duree += (*it)->getDuree();
        }
    }
    return duree;
}

bool ProgrammationManager::isProgrammee(const Evenement& e)const{
    if(dureeProgrammee(e) == e.getDuree())
        return true;
    return false;
}

bool ProgrammationManager::isProgrammable(const Evenement& e, const QDateTime& horaire,const QTimeSpan& duree)const{
    QTimeSpan& dureeProg = dureeProgrammee(e);
    QDateTime fin(horaire.addSecs(QTimeSpan(0,0).secsTo(duree)));
    if(duree > (e.getDuree() - dureeProg))
        return false;
    else if(!e.isPreemptive() && duree != e.getDuree())
        return false;
    if(typeid(e) == typeid(TacheUnitaire&)){
        const TacheUnitaire& tu = dynamic_cast<const TacheUnitaire&>(e);
        if(horaire < tu.getDisponibilite() || fin > tu.getEcheance())
            return false;
    }
    for(const_iterator it = begin() ; it != end() ; it++){
        if( ((*it)->getDate() < horaire && (*it)->getFin() > fin)
                || ((*it)->getDate() > horaire && (*it)->getDate() < fin)
                || ((*it)->getFin() > horaire && (*it)->getFin() < fin) )
            return false;
    }
    return true;

}

QDateTime ProgrammationManager::getFinTache(const TacheUnitaire& tache)const{
    vector<const Programmation*>& liste = getProgrammations(tache);
    QDateTime fin;
    for(vector<const Programmation*>::iterator it = liste.begin() ; it != liste.end() ; it++){
        if((*it)->getFin() > fin)
            fin = (*it)->getFin();
    }
    return fin;
}

vector<const Programmation*> ProgrammationManager::getProgrammations(const TacheUnitaire& tache)const{
    vector<const Programmation*> liste;
    for(const_iterator it = tab.begin(); it != tab.end(); ++it){
        if(&(*it)->getEvenement() == &tache)
            liste.push_back(*it);
    }
    return liste;
}

const vector<Programmation*> ProgrammationManager::getProgrammations(int week, int year)const{ // Liste des programmations par date croissante
    vector<Programmation*> liste;
    for(const_iterator it = tab.begin(); it != tab.end(); ++it){
        Programmation* programmation = *it;
        QDate date = programmation->getDate().date();
        if(date.weekNumber() == week && date.year() == year){
            vector<Programmation*>::const_iterator it2 = liste.begin();
            while(it2 != liste.end() && (*it2)->getDate() < (*it)->getDate())++it2;
            liste.insert(it2, programmation);
        }
    }
    return liste;
}

Programmation* ProgrammationManager::getProgrammation(const QDateTime& date)const{ // recupération d'une programmation car date est la "clef primaire"
    const_iterator it = tab.begin();
    while(it != tab.end() && (*it)->getDate() != date)++it;
    if(it != tab.end())
        return *it;
    return 0;
}
void ProgrammationManager::deleteItem(Programmation *p){
    iterator it = tab.begin();
    while(it != tab.end() && *it != p) ++it;
     if(it != tab.end()){
       tab.erase(it);
       delete p;
     }
   }
