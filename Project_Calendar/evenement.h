#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
#include <QDateTime>
#include <QObject>
#include "timing.h"
#include <QDebug>

template <class T, class U>class Manager;
class TacheManager;
class ProgrammationManager;
class ProjetManager;
class PrecedenceManager;

using namespace std;

class Evenement
{
    QTime duree;
protected:
    Evenement(const QTime& d):duree(d){}
    virtual ~Evenement()=0{}
public:
    const QTime& getDuree()const{return duree;}
    virtual void setDuree(const QTime& d){duree=d;}
};

class Tache{
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;
protected:
    QString identificateur;
    QString titre;
    QDateTime date_echeance;
    QDateTime date_dispo;
    Tache(const QString& id, const QString& title, const QDateTime& dispo, const QDateTime& echeance): identificateur(id), titre(title), date_dispo(dispo), date_echeance(echeance){}
    Tache(const Tache& t){*this = (t);}
    const Tache& operator=(const Tache& t);
    virtual ~Tache()=0{qDebug()<<"Destruction tache \n";}
public:
    const QDateTime& getDisponibilite() const{return date_dispo;}
    const QDateTime& getEcheance() const{return date_echeance;}
    const QString& getTitre()const{return titre;}
    const QString& getId()const{return identificateur;}

    void setId(const QString& i){identificateur = i;}
    void setTitre(const QString& t){titre = t;}
    void setDisponibilite(const QString& d);
    void setEcheance(const QString& e);
    virtual void setDisponibiliteDT(const QDateTime& d){date_dispo = d;}
    virtual void setEcheanceDT(const QDateTime& e){date_echeance = e;}
};

class TacheComposite:public Tache{
    typedef vector<Tache *>::iterator iterator;
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;

    vector<Tache*> tab;

    TacheComposite(const TacheComposite&);
    TacheComposite& operator=(const TacheComposite&);
    ~TacheComposite();
    TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance);

public:
    size_t getSize(){return tab.size();}

    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}

    void push_back(Tache &t){tab.push_back(&t);}
    void pop_back(){tab.pop_back();}
    iterator erase(iterator position){return tab.erase(position);}

    void setDisponibiliteDT(const QDateTime& dispo)override;
    void setEcheanceDT(const QDateTime& echeance)override;
};

class TacheUnitaire:public Tache, public Evenement{
private:
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;

    bool preemptive;
    TacheUnitaire(const Tache&);
    TacheUnitaire& operator=(const TacheUnitaire&);
    TacheUnitaire(const QString& id, const QString& t, const QTime& duree, bool pre, const QDateTime& dispo, const QDateTime& echeance):
                Tache(id,t,dispo,echeance),Evenement(duree), preemptive(pre){}
    ~TacheUnitaire(){qDebug()<<"Destruction tache unitaire\n";}
public:
   const QDateTime& getEcheance()const{return this->date_echeance;}
   void setDuree(const QTime& d){
       if(!preemptive && d>QTime(12,00))
           throw "Error : Durée d'une Tâche non preemptive supérieur à 12H impossible";
       Evenement::setDuree(d);
   }

};

class Activite:public Evenement{
    friend class ActiviteManager;
    enum TypeActivite{RDV,REUNION};
    QString identificateur;
    QString titre;
    TypeActivite type;
    Activite(const QString& id, const QString& t, TypeActivite ty, const QTime& d):Evenement(d), identificateur(id),
        titre(t), type(ty){}
    ~Activite(){}
public:
    QString getType(){return type;}
    QString getTitre(){return titre;}

};

class Programmation{
    friend class ProgrammationManager;
    friend class Manager<Programmation,ProgrammationManager>;

    Evenement* const evenement;
    QDateTime date;
    QTime duree;
    Programmation(Evenement* const e, const QDateTime& d, const QTime& du):date(d), duree(du), evenement(e){}
    ~Programmation(){}
public:
    Evenement* const getEvenement()const{return evenement;}
    const QDateTime& getDate()const {return date;}
    const QTime& getDuree(){return duree;}

};

class Projet{
    typedef vector<Tache*>::iterator iterator;
    typedef vector<Tache*>::const_iterator const_iterator;
    friend class ProjetManager;
    friend class Manager<Projet,ProjetManager>;
    QString identificateur;
    QString titre;
    vector<Tache*> tab;
    QDateTime date_dispo;
    //Projet(QString id, QString t, QDateTime d, vector<Tache*> t);
   Projet(const QString& id, const QString& t, const QDateTime& d):identificateur(id), titre(t), date_dispo(d){  }
    ~Projet(){tab.clear();}

public:
    size_t getSize() const{return tab.size();}
    const QDateTime& getDisponibilite()const{return date_dispo;}
    const QDateTime& getEcheance()const;
    const QString& getTitre()const{return titre;}
    const QString& getId()const{return identificateur;}
    void ajouterTache(Tache* t);
    //void ajouterTache(const QString& id);
    void retirerTache(Tache* t);
   // void retirerTache(const QString& id);
};

class Precedence{
    friend class PrecedenceManager;
    friend class Manager<Precedence,PrecedenceManager>;
    Tache* pred;
    Tache* succ;
    Precedence(Tache& t1, Tache& t2):pred(&t1), succ(&t2){}
    ~Precedence(){}
public:
    Tache* const getSuccesseur(){return succ;}
    Tache* const getPredecesseur(){return pred;}
};

#endif // EVENEMENT_H
