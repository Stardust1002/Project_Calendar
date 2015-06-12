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
class Precedence;
class TacheComposite;
class Programmation;

using namespace std;
class Projet;

///La classe Evenement est virtuelle pure, seules ses classes filles: TacheUnitaire et Activite peuvent être instanciées, par leurs Managers respectifs.
class Evenement
{
    QTimeSpan duree;
protected:
    Evenement(const QTimeSpan& d):duree(d){}
    virtual ~Evenement()=0{}
public:
    const QTimeSpan& getDuree()const{
  ///La méthode getDuree() renvoie la durée de l'évènement.
return duree;}
    virtual void setDuree(const QTimeSpan& d){
///La méthode setDuree() met à jour la durée avec celle passée en paramètre.
            duree=d;}
    vector<Programmation*> getProgrammations()const;
    virtual QString whoAmI()const = 0;
    virtual bool isPreemptive() const = 0;
    virtual const QString getId() const = 0;
};

///La classe Tache est virtuelle pure, seules ses classes filles: tâche unitaire et tâche composite peuvent être instanciées, par le TacheManager.
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
    vector<Precedence*> getPrecedences()const;
    const QDateTime& getDisponibilite() const{
        ///La méthode getDisponibilite() renvoie la date de disponibilité de la tâche.
        return date_dispo;}
    const QDateTime& getEcheance() const{
        ///La méthode getEcheance() renvoie la date d'écheance de la tâche.
        return date_echeance;}
    const QString& getTitre()const{
        ///La méthode getTitre() renvoie le titre de la tâche.
        return titre;}
    const QString& getId()const{
        ///La méthode getId() renvoie l'identificateur de la tâche.
        return identificateur;}
    void setId(const QString& i){
        ///La méthode setId() met à jour l'identificateur de la tâche avec la chaine passée en paramètre.
        identificateur = i;}
    void setTitre(const QString& t){
        ///La méthode setTitre() met à jour le titre de la tâche avec la chaine passée en paramètre.
        titre = t;}
    void setDisponibilite(const QString& d);
    void setEcheance(const QString& e);
    void setProjet(Projet& p);
    void setProjet(const QString& id);
    TacheComposite* getComposite()const;
    virtual void setDisponibiliteDT(const QDateTime& d){
        ///La méthode setDisponibiliteDT() met à jour la date de disponibilite de la tâche avec la date passée en paramètre.
        date_dispo = d;}
    virtual void setEcheanceDT(const QDateTime& e)
    ///La méthode setEcheanceDT() met à jour la date d'écheance de la tâche avec la date passée en paramètre.
    {date_echeance = e;}
    virtual void afficher()const;
    virtual QString whoAmI()const = 0;


};

///Une TacheComposite est une tâche non-programmable composée d'autres tâches, pouvant être unitaires ou composites. Elle ne peut être instanciée que par le biais TacheManager.
class TacheComposite:public Tache{
    friend class TacheManager;
    friend class Manager<Tache,TacheManager>;

    vector<Tache*> tab;

    TacheComposite(const TacheComposite&);
    TacheComposite& operator=(const TacheComposite&);
    ~TacheComposite();
    TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance);

public:
    size_t getSize(){/// Renvoie le nombre de taches composantes.
        return tab.size();}

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
    iterator begin(){///Renvoie un iterator sur la première tâche composante.
        return tab.begin();}
    iterator end(){///Renvoie un iterator sur la fin du tableau de tâches composantes.
        return tab.end();}
    const_iterator begin()const{
        ///Renvoie un const_iterator sur la première tâche composante
        return tab.begin();}
    const_iterator end()const{
        ///Renvoie un const_iterator sur la fin du tableau de tâches composantes.
        return tab.end();}
    bool isComposable(const Tache& t)const;
    void push_back(Tache &t);
    void pop_back(){
        ///Supprime le pointeur vers la première tâche composante.
        tab.pop_back();}
    iterator erase(iterator position){
        ///Supprime le pointeur de tâche composante pointée par l'iterator
        return tab.erase(position);}

    void setDisponibiliteDT(const QDateTime& dispo)override;
    void setEcheanceDT(const QDateTime& echeance)override;

    void afficher();
    QString whoAmI()const{
        ///Renvoie le type de tâche, ici "tache_composite"
        return "tache_composite";}


};

///Une TacheUnitaire est une tâche programmable et composable. Elle ne peut être instanciée que par le biais du TacheManager.
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
   const QDateTime& getEcheance()const{
       ///Renvoie l'écheance de la tache.
       return this->date_echeance;}
   void setDuree(const QTimeSpan& d){
       ///Met à jour la durée de la tâche en prenant en compte le fait qu'elle soit est préemptive ou non.
       if(!preemptive && d>QTimeSpan(12,00))
           throw "Error : Durée d'une Tâche non preemptive supérieur à 12H impossible";
       Evenement::setDuree(d);
   }
   bool isPreemptive()const override{
       ///Renvoie vrai si la tâche est préemptive, faux sinon.
       return preemptive;}
   void setPreemptive(const bool& b){
       ///Met à jour la préemptivité de la tâche.
       preemptive = b;}
   QString whoAmI()const{
       ///Renvoie le type de tâche, ici "tâche_unitaire".
       return "tache_unitaire";}
   void afficher()const;
   const QString getId()const{
       ///Renvoie l'identificateur de la tache.
       return Tache::getId();}
};

///Une Activite est un évènement qui programmable. Elle ne peut être instanciée que par le biais de l'ActiviteManager
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
    const QString getId()const{
        ///Renvoie l'identificateur de l'activité.
        return identificateur;}
    const TypeActivite& getType()const{
        ///Renvoie le type de l'activité sous forme d'un TypeActivite (voir énumération TypeActivite).
        return type;}
    QString getTypeToString()const{
        ///Renvoie le type de l'activité sous forme de chaine de caractères const char*.
        if(type == RDV)return "Rendez-vous";else return "Réunion";}
    QString getTitre()const{
        ///Renvoie le titre de l'activité.
        return titre;}
    QString whoAmI()const{
        ///Renvoie le type de l'évènement, ici "activite".
        return "activite";}
    bool isPreemptive( )const override{
        ///Renvoie faux sur la premptivité de l'évènement (un activité ne peut être préemptive).
        return false;}
    void setId(const QString& i){
        ///Met à jour l'identificateur de l'évènement.
        identificateur = i;}
    void setTitre(const QString& t){
        ///Met à jour le titre de l'évènement.
        titre = t;}
    void setType(const TypeActivite& t){
        ///Met à jour le type de l'activité.
        type = t;}
    void setTypeFromString(const QString& t){
        ///Met à jour le type de l'activité
        if(t == "Rendez-vous")type = RDV;else type=REUNION;}
    virtual void afficher()const;


};

///La classe Programmation permet de programmer un évènement à une heure fixe en fonction de ses Precedence s, de sa date de disponibilité et de sa date d'échéance. Une programmation ne peut être instanciée que par le biais du ProgrammationManager.
class Programmation{
    friend class ProgrammationManager;
    friend class Manager<Programmation,ProgrammationManager>;

    Evenement& evenement;
    QDateTime date;
    QTimeSpan duree;
    Programmation(Evenement& e, const QDateTime& d, const QTimeSpan& du):date(d), duree(du), evenement(e){}
    ~Programmation(){}
public:
    Evenement& getEvenement()const{
        ///Renvoie l'évènement lié à la programmation.
        return evenement;}
    const QDateTime& getDate()const {
        ///Renvoie la date de la programmation.
        return date;}
    QDateTime getFin()const{
        ///Renvoie la date de fin de la programmation, calculée grâce à la durée et au début de celle-ci.
        return QDateTime(date.addSecs(QTimeSpan(0,0).secsTo(duree)));}
    const QTimeSpan& getDuree()const{
        ///Renvoie la durée de la programmation.
        return duree;}

};

///La classe Projet permet de regrouper différentes Taches et impose une dâte de disponibilité. Elle ne peut être instanciée que par le biais du ProjetManager.
class Projet{
    friend class ProjetManager;
    friend class Manager<Projet,ProjetManager>;
    QString identificateur;
    QString titre;
    vector<Tache*> tab;
    QDateTime date_dispo;
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
    iterator begin(){
        ///Renvoie un iterator sur la première tâche composante.
        return tab.begin();}
    iterator end(){
        ///Renvoie un iterator sur la fin du tableau de tâches composantes.
        return tab.end();}
    const_iterator begin()const{
        ///Renvoie un const_iterator sur la première tâche composante.
        return tab.begin();}
    const_iterator end()const{
        ///Renvoie un const_iterator sur la fin du tableau de tâches composantes.
        return tab.end();}
    size_t getSize() const{
        ///Renvoie le nombre de tâches liées au projet.
        return tab.size();}
    const QDateTime& getDisponibilite()const{
        ///Renvoie la date de disponibilité du projet.
        return date_dispo;}
    QDateTime getEcheance();
    const QString& getTitre()const{
        ///Renvoie le titre du projet.
        return titre;}
    const QString& getId()const{
        ///Renvoie l'identificateur du projet.
        return identificateur;}
    bool possede(const Tache& t);
    void setId(const QString& i){
        ///Met à jour l'identificateur du projet.
        identificateur = i;}
    void setTitre(const QString& t){
        ///Met à jour le titre du projet.
        titre = t;}
    void setDisponibilite(const QDateTime& t){
        ///Met à jour la date de disponibilité du projet.
        date_dispo = t;}
    void ajouterTache(Tache* t);
    void ajouterTache(const QString& id);
    void retirerTache(Tache* t);
    void retirerTache(const QString& id);
    virtual void afficher();
};

///La classe Precedence établit une relation de Precedence entre deux tâches. Une Precedence ne peut être instanciée que par le biais du PrecedenceManager.
class Precedence{
    friend class PrecedenceManager;
    friend class Manager<Precedence,PrecedenceManager>;
    const Tache* pred;
    const Tache* succ;
    Precedence(const Tache& t1, const Tache& t2):pred(&t1), succ(&t2){}
    ~Precedence(){}
public:
    const Tache& getSuccesseur()const{
        ///Renvoie la tâche successeur associée à la précédence.
        return *succ;}
    const Tache& getPredecesseur()const{
        ///Renvoie la tâche prédécesseur associée à la précédence.
        return *pred;}
};

#endif // EVENEMENT_H
