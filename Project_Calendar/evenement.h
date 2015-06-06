#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include "GUI/fonctions.h"
#include "qtimespan.h"

template <class T, class U>class Manager;
class TacheManager;
class ProgrammationManager;
class ProjetManager;
class PrecedenceManager;

class TacheComposite;

using namespace std;
class Projet;


class Evenement
{
    QTimeSpan duree;
protected:
    Evenement(const QTimeSpan& d):duree(d){}
    virtual ~Evenement()=0{}
public:
    const QTimeSpan& getDuree()const{return duree;}
    virtual void setDuree(const QTimeSpan& d){duree=d;}
    virtual QString whoAmI()const = 0;
    virtual bool isPreemptive() const = 0;
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
    virtual ~Tache()=0{}
public:
    Projet *getProjet()const;
    const QDateTime& getDisponibilite() const{return date_dispo;}
    const QDateTime& getEcheance() const{return date_echeance;}
    const QString& getTitre()const{return titre;}
    const QString& getId()const{return identificateur;}
    void setId(const QString& i){identificateur = i;}
    void setTitre(const QString& t){titre = t;}
    void setDisponibilite(const QString& d);
    void setEcheance(const QString& e);
    void setProjet(Projet& p);
    void setProjet(const QString& id);
    TacheComposite* getComposite()const;
    virtual void setDisponibiliteDT(const QDateTime& d){date_dispo = d;}
    virtual void setEcheanceDT(const QDateTime& e){date_echeance = e;}
    virtual void afficher()const;
    virtual QString whoAmI()const = 0;


};

class TacheComposite:public Tache{
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;

    vector<Tache*> tab;

    TacheComposite(const TacheComposite&);
    TacheComposite& operator=(const TacheComposite&);
    ~TacheComposite();
    TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance);

public:
    size_t getSize(){return tab.size();}

    class iterator : public vector<Tache*>::iterator{
    public:
        iterator():vector<Tache*>::iterator(){}
        iterator(vector<Tache*>::iterator it):vector<Tache*>::iterator(it){}
    };
    class const_iterator : public vector<Tache*>::const_iterator{
    public:
        const_iterator():vector<Tache*>::const_iterator(){}
        const_iterator(vector<Tache*>::const_iterator it):vector<Tache*>::const_iterator(it){}
    };
    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}
    const_iterator begin()const{return tab.begin();}
    const_iterator end()const{return tab.end();}
    bool isComposable(const Tache& t)const;
    void push_back(Tache &t);
    void pop_back(){tab.pop_back();}
    iterator erase(iterator position){return tab.erase(position);}

    void setDisponibiliteDT(const QDateTime& dispo)override;
    void setEcheanceDT(const QDateTime& echeance)override;

    void afficher();
    QString whoAmI()const{return "tache_composite";}


};

class TacheUnitaire:public Tache, public Evenement{
private:
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;

    bool preemptive;
    TacheUnitaire(const Tache&);
    TacheUnitaire& operator=(const TacheUnitaire&);
    TacheUnitaire(const QString& id, const QString& t, const QTimeSpan& duree, bool pre, const QDateTime& dispo, const QDateTime& echeance):
        Tache(id,t,dispo,echeance),Evenement(duree), preemptive(pre){}
    ~TacheUnitaire(){}
public:
   const QDateTime& getEcheance()const{return this->date_echeance;}
   void setDuree(const QTimeSpan& d){
       if(!preemptive && d>QTimeSpan(12,00))
           throw "Error : Durée d'une Tâche non preemptive supérieur à 12H impossible";
       Evenement::setDuree(d);
   }
   bool isPreemptive()const override{return preemptive;}
   void setPreemptive(const bool& b){preemptive = b;}
   QString whoAmI()const{return "tache_unitaire";}
   void afficher()const;
};

class Activite:public Evenement{
public:
    enum TypeActivite{RDV,REUNION};
private:
    friend class ActiviteManager;
    QString identificateur;
    QString titre;
    TypeActivite type;
    Activite(const QString& id, const QString& t, TypeActivite ty, const QTimeSpan& d):Evenement(d), identificateur(id),
        titre(t), type(ty){}
public:
    QString getId()const{return identificateur;}
    const TypeActivite& getType()const{return type;}
    QString getTypeToString()const{if(type == RDV)return "Rendez-vous";else return "Réunion";}
    QString getTitre()const{return titre;}
    QString whoAmI()const{return "activite";}
    bool isPreemptive( )const override{return false;}
    void setId(const QString& i){identificateur = i;}
    void setTitre(const QString& t){titre = t;}
    void setType(const TypeActivite& t){type = t;}
    void setTypeFromString(const QString& t){if(t == "Rendez-vous")type = RDV;else type=REUNION;}
    //void setDuree(const QTimeSpan& t){Evenement::setDuree(t);}
    virtual void afficher()const;


};

class Programmation{
    friend class ProgrammationManager;
    friend class Manager<Programmation,ProgrammationManager>;

    Evenement& evenement;
    QDateTime date;
    QTimeSpan duree;
    Programmation(Evenement& e, const QDateTime& d, const QTimeSpan& du):date(d), duree(du), evenement(e){}
    ~Programmation(){}
public:
    Evenement& getEvenement()const{return evenement;}
    const QDateTime& getDate()const {return date;}
    const QTimeSpan& getDuree(){return duree;}

};

class Projet{
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
    class iterator : public vector<Tache*>::iterator{
    public:
       iterator():vector<Tache*>::iterator(){}
       iterator(vector<Tache*>::iterator it):vector<Tache*>::iterator(it){}
   };
    class const_iterator : public vector<Tache*>::const_iterator{
    public:
       const_iterator():vector<Tache*>::const_iterator(){}
       const_iterator(vector<Tache*>::const_iterator it):vector<Tache*>::const_iterator(it){}
   };
    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}
    size_t getSize() const{return tab.size();}
    const QDateTime& getDisponibilite()const{return date_dispo;}
    QDateTime getEcheance();
    const QString& getTitre()const{return titre;}
    const QString& getId()const{return identificateur;}
    bool possede(const Tache& t);
    void setId(const QString& i){identificateur = i;}
    void setTitre(const QString& t){titre = t;}
    void setDisponibilite(const QDateTime& t){date_dispo = t;}
    void ajouterTache(Tache* t);
    void ajouterTache(const QString& id);
    void retirerTache(Tache* t);
    void retirerTache(const QString& id);
    virtual void afficher();
};

class Precedence{
    friend class PrecedenceManager;
    friend class Manager<Precedence,PrecedenceManager>;
    const Tache* pred;
    const Tache* succ;
    Precedence(const Tache& t1, const Tache& t2):pred(&t1), succ(&t2){}
    ~Precedence(){}
public:
    const Tache& getSuccesseur()const{return *succ;}
    const Tache& getPredecesseur()const{return *pred;}
};

#endif // EVENEMENT_H
