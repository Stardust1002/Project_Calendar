#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDateTime>
#include <QObject>
#include "timing.h"
using namespace std;

class Evenement
{
protected:
 TIME::Duree duree;
 Evenement(TIME::Duree d):duree(d){}
public:
 TIME::Duree getDuree()const{return duree;}
};
class Tache{
protected:

    friend class TacheManager;
    QString identificateur;
    QString titre;
    QDateTime date_echeance;
    QDateTime date_dispo;
    Tache(QString id, QString title, QDateTime dispo, QDateTime echeance): identificateur(id), titre(title), date_dispo(dispo), date_echeance(echeance){}

public:
    QDateTime getDisponibilite() const{return date_dispo;}
    virtual QDateTime getEcheance() const  = 0;
    QString getTitre()const{return titre;}
    QString getId()const{return identificateur;}

};

class TacheComposite:public Tache{
private:
    friend class TacheManager;
    vector<Tache*> tab;
    TacheComposite(const TacheComposite&);
    TacheComposite& operator=(const TacheComposite&);
    ~TacheComposite();
    TacheComposite(QString id, QString title, vector<Tache*> t, QDateTime date_dispo, QDateTime date_echeance);

public:
    size_t getSize(){return tab.size();}
    QDateTime getEcheance()const{return this->date_echeance;}
};

class TacheUnitaire:public Tache, public Evenement{
private:
    friend class TacheManager;
    friend class TacheComposite;
    bool preemptive;
    TacheUnitaire(const Tache&);
    TacheUnitaire& operator=(const TacheUnitaire&);
    TacheUnitaire(QString id, QString t, TIME::Duree duree, bool pre, QDateTime dispo, QDateTime echeance):
        Tache(id,t,dispo,echeance),Evenement(duree), preemptive(pre){}
    ~TacheUnitaire(){}
public:
   QDateTime getEcheance()const{return this->date_echeance;}

};


class Activite:public Evenement{
    friend class ActiviteManager;
    enum TypeActivite{RDV,REUNION};
    QString identificateur;
    QString titre;
    TypeActivite type;
    TIME::Duree duree;
    Activite(QString id, QString t, TypeActivite ty, TIME::Duree d):Evenement(d), identificateur(id),
        titre(t), type(ty){}
    ~Activite(){}
public:
    QString getType(){return type;}
    TIME::Duree getDuree(){return duree;}
    QString getTitre(){return titre;}

};

class Programmation{
    friend class ProgrammationManager;
    Evenement* const evenement;
    QDateTime date;
    TIME::Horaire horaire;
    Programmation(Evenement* const e, QDateTime d, TIME::Horaire h):date(d), horaire(h), evenement(e){}
    ~Programmation(){}
public:
    Evenement* const getEvenement()const{return evenement;}
    QDateTime getDate()const {return date;}
    TIME::Horaire getHoraire(){return horaire;}

};

class Projet{
    friend class ProjectManager;
    QString identificateur;
    QString titre;
    vector<Tache*> tab;
    QDateTime date_dispo;
    //Projet(QString id, QString t, QDateTime d, vector<Tache*> t);
   Projet(QString id, QString t, QDateTime d):identificateur(id), titre(t), date_dispo(d){  }
    ~Projet(){tab.clear();}

public:
    size_t getSize() const{return tab.size();}
    QDateTime getDisponibilite()const{return date_dispo;}
    QDateTime getEcheance()const;
    QString getTitre()const{return titre;}
    QString getId()const{return identificateur;}
    void ajouterTache(Tache* t);
    //void ajouterTache(const QString& id);
    void retirerTache(Tache* t);
   // void retirerTache(const QString& id);
};

class Precedence{
    friend class PrecedenceManager;
    Tache* pred;
    Tache* succ;
    Precedence(Tache* t1, Tache* t2):pred(t1), succ(t2){}
    ~Precedence(){}
public:
    Tache* const getSuccesseur(){return succ;}
    Tache* const getPredecesseur(){return pred;}
};

#endif // EVENEMENT_H
