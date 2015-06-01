#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include "time.h"
#include "evenement.h"

using namespace std;

template<class T, class U> class Manager{
    typedef typename vector<T*>::iterator iterator;

private:
    Manager& operator=(const Manager&);
    struct Handler{
        U* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){U::freeInstance();}
    };

protected:    
    vector<T*> tab;
    static Handler handler;
    Manager(){}
    ~Manager();

public:
   // virtual void deleteItem(T* t);
    unsigned int getSize() const {return tab.size();}
    T* getItem(const QString&) const;
    static U& getInstance();
    static void freeInstance();
    void addItem(T* t){tab.push_back(t);}
    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}
};

template <class T, class U>
typename Manager<T,U>::Handler Manager<T,U>::handler;

template<class T, class U>
U& Manager<T,U>::getInstance(){
    if(handler.instance == 0)
        handler.instance = new U();
    return *handler.instance;
}

template<class T, class U>
void Manager<T,U>::freeInstance(){
    delete handler.instance;
    handler.instance = 0;
}

template <class T, class U> Manager<T,U>::~Manager(){
    if(!tab.empty()){
    for(Manager<T,U>::iterator it = this->begin(); it != this->end(); ++it)
        delete &(*it);
    tab.clear();}
}
template <class T,class U> T* Manager<T,U>::getItem(const QString& id)const{
    for(Manager<T,U>::iterator it = this->begin(); it != this->end(); ++it)
        if(*it.getId() == id)return &(*it);
    throw "Exception: pas d'Item correspondant";
    return 0;
}

class TacheManager: public Manager<Tache, TacheManager>{
public:
   void  ajouterTacheUnitaire(QString id, QString titre, TIME::Duree duree,
                          bool preemptive, QString dispo, QString echeance){
       QString format = "dd:MM:yyyy:HH:mm";
      QDateTime date_dispo = QDateTime::fromString(dispo,format);
      QDateTime date_echeance = QDateTime::fromString(echeance,format);
        TacheUnitaire* t = new TacheUnitaire(id, titre, duree, preemptive, date_dispo, date_echeance);
        addItem(t);
    }
   void ajouterTacheComposite(const QString& id, const QString& titre, vector<Tache*> liste, QString dispo = "00:00:0000:00:00", QString echeance = "00:00:0000:00:00"){
       QString format = "dd:MM:yyyy:HH:mm";
       QDateTime date_dispo = QDateTime::fromString(dispo,format);
       QDateTime date_echeance = QDateTime::fromString(echeance,format);
       TacheComposite* t = new TacheComposite(id, titre, liste, date_dispo, date_echeance);
        addItem(t);
    }
    void supprimerTache(QString id);
};

class ProjectManager: public Manager<Projet,ProjectManager>{
public:
   void  ajouterProjet(QString id, QString titre,
                         QString dispo){
       QString format = "dd:MM:yyyy:HH:mm";
       QDateTime date_dispo = QDateTime::fromString(dispo,format);
    Projet* t = new Projet(id, titre, date_dispo);
    addItem(t);
    }
    void supprimerProjet(QString id);

};
class PrecedenceManager: public Manager<Precedence,PrecedenceManager>{
   public:
   void  ajouterPrecedence(Tache* t1, Tache* t2){
    Precedence* t = new Precedence(t1,t2);
    addItem(t);
    }
    void supprimerPrecedence(QString id);
};

#endif // MANAGER_H

