#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
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
    Tache(QString id, QString title): identificateur(id), titre(title){};

public:
    virtual QDate getDisponibilite() const = 0;
    virtual QDate getEcheance() const  = 0;
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
    TacheComposite(QString id, QString title, vector<Tache*> t):Tache(id, title){
        for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it)
            tab.push_back(*it);
    }

public:
    size_t getSize(){return tab.size();}
  //QDate getDisponibilite()const;
  //QDate getEcheance()const;
};

class TacheUnitaire:public Tache, public Evenement{
private:
    friend class TacheManager;
    bool preemptive;
    QDate date_dispo;
    QDate date_echeance;
    TacheUnitaire(const Tache&);
    TacheUnitaire& operator=(const TacheUnitaire&);
    TacheUnitaire(QString id, QString t, TIME::Duree duree, bool pre, QDate dispo, QDate echeance):
        Tache(id,t),Evenement(duree), preemptive(pre), date_dispo(dispo), date_echeance(echeance){}

public:
   QDate getDisponibilite()const{return date_dispo;}
   QDate getEcheance()const{return date_echeance;}

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

public:
    QString getType(){return type;}
    TIME::Duree getDuree(){return duree;}
    QString getTitre(){return titre;}

};

class Programmation{
    friend class ProgrammationManager;
    Evenement* const evenement;
    QDate date;
    TIME::Horaire horaire;
    Programmation(Evenement* const e, QDate d, TIME::Horaire h):date(d), horaire(h), evenement(e){}

public:
    Evenement* const getEvenement()const{return evenement;}
    QDate getDate()const {return date;}
    TIME::Horaire getHoraire(){return horaire;}

};

class Projet{
    friend class ProjectManager;
    QString identificateur;
    QString titre;
    vector<Tache*> tab;
    QDate date_dispo;
    //Projet(QString id, QString t, QDate d, vector<Tache*> t);
   Projet(QString id, QString t, QDate d):identificateur(id), titre(t), date_dispo(d){}

public:
    size_t getSize() const{return tab.size();}
    QDate getDisponibilite()const{return date_dispo;}
    QDate getEcheance()const;
    QString getTitre()const{return titre;}
    QString getId()const{return identificateur;}
    void ajouterTache(Tache* t);
    void ajouterTache(const QString& id);
    void retirerTache(Tache* t);
    void retirerTache(const QString& id);
};

class Precedence{
    friend class PrecedenceManager;
    Tache* pred;
    Tache* succ;
    Precedence(Tache* t1, Tache* t2):pred(t1), succ(t2){}

public:
    Tache* const getSuccesseur(){return succ;}
    Tache* const getPredecesseur(){return pred;}
};

#endif // EVENEMENT_H
