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

///La classe Manager est un singleton conteneur d'items. Elle gère le cycle de vie de ses items, de la création à la destruction en passant par la modification. Une façade d'iterator a été mise en place pour empêcher l'accès direct au vecteur privé contenant les items. Celle-ci est virtuelle pure, ainsi seules ses classes filles peuvent être instanciées:
///- ProjetManager
///- ActiviteManager
///- TacheManager
///- ProgrammationManager
///- PrecedenceManager
///
///Un Handler a également été mis en place permettant la désallocation automatique du Manager à la fin du processus.
template<class T, class U> class Manager{
private:
    struct Handler{
        U* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){U::freeInstance();}
    };
    Manager& operator=(const Manager&);
    Manager(const Manager&){}
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

    unsigned int getSize() const{
   ///Retourne le nombre d'items contenus dans le vecteur.
         return tab.size();}
    T* getItem(const QString& id);
    bool isIdFree(const QString& id);
    void deleteItem(T& t);
    void deleteItem(const QString& id);
    void deleteItem(iterator it);
    static U& getInstance();
    static void freeInstance();

    iterator begin(){
        ///Renvoie un iterator sur le premier item du vecteur.
        return tab.begin();}
    iterator end(){
        ///Renvoie un iterator sur la fin du vecteur.
        return tab.end();}
    const_iterator begin()const{
      ///Renvoie un const_iterator sur le premier item du vecteur.
        return tab.cbegin();}
    const_iterator end()const{
        ///Renvoie un const_iterator sur la fin du vecteur.
        return tab.cend();}
};

template <class T, class U> typename Manager<T,U>::Handler Manager<T,U>::handler;
template<class T, class U> U& Manager<T,U>::getInstance(){
    ///Renvoie une référence sur l'instance du Manager.
    ///Si ce dernier n'est pas créé lors de l'appel, la méthode instancie le Manager et renvoie sa référence.
    if(handler.instance == 0)
        handler.instance = new U();
    return *handler.instance;
}
template<class T, class U> void Manager<T,U>::freeInstance(){
    ///Libère l'instance du Manager, et entraine sa désallocation mémoire.
    delete handler.instance;
    handler.instance = 0;
}

template <class T, class U> Manager<T,U>::~Manager(){
    if(!tab.empty()){
        while(!tab.empty()){
            deleteItem(tab.begin());
        }
    }
}

template <class T,class U> T* Manager<T,U>::getItem(const QString& id){
    ///Renvoie un pointeur sur l'item dont l'identificateur a été passé en paramètre
    ///Si ce dernier n'existe pas, nullptr est retourné.
    for(iterator it = this->begin(); it != this->end(); ++it){
        if((*it)->getId() == id)
            return *it;
    }
    return nullptr;
}
template <class T,class U> bool Manager<T,U>::isIdFree(const QString& id){
    ///Vérifie si l'identificateur passé en paramètre est déjà existant (il ne peut y avoir de doublon).
    ///Renvoie false si déjà existant, sinon retourne vrai.
    for(iterator it = tab.begin() ; it != tab.end() ; it++)
        if((*it)->getId() == id)
            return false;
    return true;
}
template <class T, class U> void Manager<T,U>::deleteItem(T& item){
    ///Supprime l'item dont la référence a été passée en paramètre.
    deleteItem(item.getId());
}
template <class T, class U> void Manager<T,U>::deleteItem(const QString& id){
    ///Supprime l'item dont l'identificateur a été passé en paramètre.
    iterator it;
    for(it = this->tab.begin(); it != this->tab.end() && (*it)->getId() != id ; ++it);
    if(it != this->tab.end())
        deleteItem(it);
}
template <class T, class U> inline void Manager<T,U>::deleteItem(iterator toDelete){
    ///Supprime l'item pointé par l'iterator passé en paramètre.
    T* pt = *toDelete;
    iterator Next = tab.erase(toDelete);
    delete pt;
}
template <> inline void Manager<Tache,TacheManager>::deleteItem(iterator toDelete){
    ///Supprime l'item pointé par l'iterator passé en paramètre.
    TacheComposite* tc;
    if(tc = (*toDelete)->getComposite())
        deleteItem(*tc);
    else{
        Tache* pt = *toDelete;
        tab.erase(toDelete);
        delete pt;
    }

}
///La classe TacheManager est un Manager qui gère les items de type Tache. Elle ne peut être instanciée à cause du singleton mis en place dans sa classe mère. Elle peut toutefois être récupérée dans une référence ou un pointeur à l'aide la méthode mère: getInstance().
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
///La classe ProjetManager est un Manager qui gère les items de type Projet. Elle ne peut être instanciée à cause du singleton mis en place dans sa classe mère. Elle peut toutefois être récupérée dans une référence ou un pointeur à l'aide la méthode mère: getInstance().
class ProjetManager: public Manager<Projet,ProjetManager>{
public:
    Projet& ajouterProjet(const QString& id, const QString& titre, const QString& dispo);
    Projet& ajouterProjet(const QString& id, const QString& titre, const QDateTime& dispo);
    void supprimerProjet(QString id);

};
///La classe PrecedenceManager est un Manager qui gère les items de type Precedence. Elle ne peut être instanciée à cause du singleton mis en place dans sa classe mère. Elle peut toutefois être récupérée dans une référence ou un pointeur à l'aide la méthode mère: getInstance().
class PrecedenceManager: public Manager<Precedence,PrecedenceManager>{
public:
    void deleteItem(Precedence* t);

    Precedence&  ajouterPrecedence(const Tache& t1,const Tache& t2);
    bool isPredecesseur(const Tache& t1, const Tache& t2)const;
};

///La classe ActiviteManager est un Manager qui gère les items de type activité. Elle ne peut être instanciée à cause du singleton mis en place dans sa classe mère. Elle peut toutefois être récupérée dans une référence ou un pointeur à l'aide la méthode mère: getInstance().
class ActiviteManager: public Manager<Activite,ActiviteManager>{
public:
    Activite& ajouterActivite(const QString& id, const QString& t, const Activite::TypeActivite& ty, const QTimeSpan& d);
    Activite& ajouterActivite(const QString &id, const QString &t, const Activite::TypeActivite &ty, const QString &d);
};

///La classe ProgrammationManager est un Manager qui gère les items de type Programmation. Elle ne peut être instanciée à cause du singleton mis en place dans sa classe mère. Elle peut toutefois être récupérée dans une référence ou un pointeur à l'aide la méthode mère: getInstance().
class ProgrammationManager:public Manager<Programmation,ProgrammationManager>{
public:
    Programmation& ajouterProgrammation(Evenement& evenement,const QDateTime& date,const QTimeSpan& duree);
    Programmation& ajouterProgrammation(Evenement& evenement,const QString& horaire,const QString& duree);
    bool isProgrammee(const Evenement& e)const;
    bool isProgrammee(const Tache& t, const QDateTime& date)const;
    bool isProgrammable(const Evenement& t, const QDateTime& date,const QTimeSpan& duree)const;
    QTimeSpan dureeProgrammee(const Evenement& e)const;
    QDateTime getFinTache(const TacheUnitaire& tache)const;
    vector<const Programmation*> getProgrammations(const TacheUnitaire& tache)const;
    const vector<Programmation*> getProgrammations(int week, int year)const;
    Programmation *getProgrammation(const QDateTime& date)const;
    void deleteItem(Programmation* p);


};
#endif // MANAGER_H

