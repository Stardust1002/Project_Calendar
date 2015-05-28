#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <QObject>
#include <QDebug>
using namespace std;
template<class T> class Manager;
template<class T>class Handler{
    friend class Manager<T>;
    Manager<T>* instance;
public:
    Handler():instance(0){}
    virtual ~Handler(){Manager<T>::freeInstance();}
};
template<class T> class Manager
{
    friend class Handler<T>;
    vector<T*> tab;
    static Handler<T> handler;
    Manager(){}
    Manager& operator=(const Manager&);
    virtual ~Manager();

public:
   // virtual void deleteItem(T* t);
    unsigned int getSize() const {return tab.size();}
    T* getItem(const QString&) const;
    static Manager& getInstance();
    static void freeInstance();
    void addItem(T* t){tab.push_back(t);}
    template<class T> class iterator{
        T* current;

     public:
        iterator(const iterator& it):current(it.current){}
        iterator(T* ptr):current(ptr){}
        iterator(unsigned int indice = 0):current(Manager::getInstance().tab[indice]){}

        iterator& operator++(){++current; return *this;}
        bool operator!=(const iterator<T>& it){return it.current != current;}
        bool operator==(const iterator<T>& it){return it.current == current;}
        T& operator*()const{return *current;}
    };
    const iterator<T> begin() const {return iterator<T>();}
    const iterator<T> end()const{return iterator<T>(getSize());}

};
template <class T>Handler<T> Manager<T>::handler = Handler<T>::Handler();
template <class T>Manager<T>& Manager<T>::getInstance(){
    if(handler.instance == 0)
        handler.instance = new Manager<T>();
    return *handler.instance;
}
template <class T>void Manager<T>::freeInstance(){

    delete handler.instance;
    handler.instance = 0;
}
template <class T> Manager<T>::~Manager(){
    if(!tab.empty()){
    for(Manager<T>::iterator<T> it = this->begin(); it != this->end(); ++it)
        delete &(*it);
    tab.clear();}
}
template <class T> T* Manager<T>::getItem(const QString& id)const{
    for(Manager<T>::iterator it = this->begin(); it != this->end(); ++it)
        if(*it.getId() == id)return &(*it);
    throw "Exception: pas d'Item correspondant";
    return 0;
}



#endif // MANAGER_H

class TacheManager: private Manager<Tache>{
   private:

   public:
    ajouterTacheUnitaire(const QString& id, const QString& titre, const Horaire& duree,
                         const QString& preemptive, const QDate& date_dispo, const QDate& date_echeance){
    TacheUnitaire* t = new TacheUnitaire(id, titre, duree, preemptive, date_dispo, date_echeance);
    addItem(t);
    }
    ajouterTacheComposite(const QString& id, const QString& titre, vector<Tache> liste){
    TacheComposite* t = new TacheComposite(id, titre, liste);
    addItem(t);
    }

};
