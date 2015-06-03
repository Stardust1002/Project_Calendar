#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include "evenement.h"

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

    typedef typename vector<T*>::iterator iterator;
    unsigned int getSize() const {return tab.size();}
    T& getItem(const QString& id) const;
    void deleteItem(T& t);
    void deleteItem(const QString& id);
    void deleteItem(iterator it);
    static U& getInstance();
    static void freeInstance();
    iterator begin(){return tab.begin();}
    iterator end(){return tab.end();}
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
    qDebug()<<"Destruction TacheManager \n";
    if(!tab.empty()){
        qDebug()<<"Tab non empty \n";
        qDebug()<<"\nTaille : "<<tab.size();
        for(Manager<T,U>::iterator it = this->begin(); it != this->end(); ++it)
            delete *it;
        tab.clear();
    }
    qDebug()<<"Fin de Destruction TacheManager \n";
}
template <class T,class U> T& Manager<T,U>::getItem(const QString& id)const{
    for(Manager<T,U>::iterator it = this->begin(); it != this->end(); ++it)
        if(*it.getId() == id)
            return *it;
    throw "Exception: pas d'Item correspondant";
    return 0;
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
    TacheComposite& ajouterTacheComposite(const QString& id, const QString& titre,const QString& dispo = "01:01:0001:00:00",
                               const QString& echeance = "01:01:3000:00:00",vector<Tache*> liste = vector<Tache*>());
};

class ProjetManager: public Manager<Projet,ProjetManager>{
public:
    void ajouterProjet(const QString& id, const QString& titre, const QString& dispo){
       QString format = "dd:MM:yyyy:HH:mm";
       QDateTime date_dispo = QDateTime::fromString(dispo,format);
    Projet* t = new Projet(id, titre, date_dispo);
    addItem(*t);
    }
    void supprimerProjet(QString id);

};

class PrecedenceManager: public Manager<Precedence,PrecedenceManager>{
   public:
   void  ajouterPrecedence(Tache& t1, Tache& t2){
    Precedence* t = new Precedence(t1,t2);
    addItem(*t);
    }
    void supprimerPrecedence(const QString& id);
};

#endif // MANAGER_H

