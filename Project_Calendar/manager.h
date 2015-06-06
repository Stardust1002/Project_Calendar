#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include "evenement.h"
#include "qtimespan.h"

using namespace std;

template<class T, class U> class Manager{
private:
    struct Handler{
        U* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){U::freeInstance();}
    };
    Manager& operator=(const Manager&);
protected:    
    vector<T*> tab;
    static Handler handler;
    void addItem(T& t){tab.push_back(&t);}

    Manager(){}
    ~Manager();
public:
    class iterator : public vector<T*>::iterator{
    public:
        iterator():vector<T*>::iterator(){}
        iterator(typename vector<T*>::iterator it):vector<T*>::iterator(it){}
    };
    class const_iterator : public vector<T*>::const_iterator{
    public:
        const_iterator():vector<T*>::const_iterator(){}
        const_iterator(typename vector<T*>::const_iterator it):vector<T*>::const_iterator(it){}
    };

    unsigned int getSize() const {return tab.size();}
    T* getItem(const QString& id);
    void deleteItem(T& t);
    void deleteItem(const QString& id);
    void deleteItem(iterator it);
    static U& getInstance();
    static void freeInstance();

    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}
    const_iterator begin()const{return tab.begin();}
    const_iterator end()const{return tab.end();}
};

template <class T, class U> typename Manager<T,U>::Handler Manager<T,U>::handler;

template<class T, class U> U& Manager<T,U>::getInstance(){
    if(handler.instance == 0)
        handler.instance = new U();
    return *handler.instance;
}

template<class T, class U> void Manager<T,U>::freeInstance(){
    delete handler.instance;
    handler.instance = 0;
}

template <class T, class U> Manager<T,U>::~Manager(){
    if(!tab.empty()){
        for(iterator it = this->begin(); it != this->end(); ++it)
            delete *it;
        tab.clear();
    }
}
template <class T,class U> T* Manager<T,U>::getItem(const QString& id){
    for(iterator it = this->begin(); it != this->end(); ++it)
        if((*it)->getId() == id)
            return *it;
    return nullptr;
}

template <class T, class U> void Manager<T,U>::deleteItem(T& item){
    deleteItem(item.getId());
}
template <class T, class U> void Manager<T,U>::deleteItem(const QString& id){
    iterator it;
    for(it = this->tab.begin(); it != this->tab.end() && (*it)->getId() != id ; ++it);
    deleteItem(it);
}
template <class T, class U> void Manager<T,U>::deleteItem(iterator it){
    T* pt = *it;
    tab.erase(it);
    delete pt;
}

class TacheManager: public Manager<Tache,TacheManager>{
public:
    TacheUnitaire& ajouterTacheUnitaire(const QString& id, const QString& titre, const QString& duree,
                              bool preemptive, const QString& dispo, const QString& echeance);
    TacheUnitaire& ajouterTacheUnitaire(const QString& id, const QString& titre, const QTimeSpan& duree,
                              bool preemptive,const QDateTime& dispo, const QDateTime& echeance);
    TacheComposite& ajouterTacheComposite(const QString& id, const QString& titre,const QString& dispo,
                               const QString& echeance,vector<Tache*> liste = vector<Tache*>());
    TacheComposite& ajouterTacheComposite(const QString& id, const QString& titre,const QDateTime& dispo,
                               const QDateTime& echeance,vector<Tache*> liste = vector<Tache*>());

};

class ProjetManager: public Manager<Projet,ProjetManager>{
public:
    Projet& ajouterProjet(const QString& id, const QString& titre, const QString& dispo);
    Projet& ajouterProjet(const QString& id, const QString& titre, const QDateTime& dispo);
    void supprimerProjet(QString id);

};

class PrecedenceManager: public Manager<Precedence,PrecedenceManager>{
public:
    Precedence&  ajouterPrecedence(const Tache& t1,const Tache& t2);
    void supprimerPrecedence(const QString& id);
    bool isPredecesseur(const Tache& t1, const Tache& t2)const;
};

class ActiviteManager: public Manager<Activite,ActiviteManager>{
public:
    Activite& ajouterActivite(const QString& id, const QString& t, const Activite::TypeActivite& ty, const QTimeSpan& d);
    Activite& ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QString &d);
};

class ProgrammationManager:public Manager<Programmation,ProgrammationManager>{
public:
    Programmation& ajouterProgrammation(Evenement& evenement,const QDateTime& horaire,const QTimeSpan& duree);
    Programmation& ajouterProgrammation(Evenement& evenement,const QString& horaire,const QString& duree);
    bool isProgrammee(const Evenement&)const;
    bool isProgrammable(const Evenement& t, const QDateTime& horaire,const QTimeSpan& duree)const;
    QTimeSpan dureeProgrammee(const Evenement& e)const;

};
#endif // MANAGER_H

