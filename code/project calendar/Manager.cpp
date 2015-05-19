//
//  Manager.cpp
//  project calendar
//
//  Created by Antoine Jeannot on 01/05/2015.
//  Copyright (c) 2015 Antoine Jeannot. All rights reserved.
//

#include "Manager.h"


template<class T> Handler<T> Manager<T>::handler = Handler<T>::Handler();
template<class T>Manager<T>::Manager():nb(0),max(0),tab(0){}
template<class T>Manager<T>::~Manager(){
    for(int i = 0; i < nb; i++)
        delete tab[i];
    delete[] tab;
    nb = 0;
    max = 0;
    tab = 0;
}
template<class T> Manager<T>& Manager<T>::getInstance(){
if(handler.instance == 0)
    handler.instance = new Manager<T>;
    return *handler.instance;
}
template<class T> void Manager<T>::freeInstance(){
    delete handler.instance;
    handler.instance = 0;
}
template<class T> void Manager<T>::addItem(T *t){
    if(nb == max){
        max+=10;
        T** tmp = new T*[max];
        T** old = tab;
        if(nb > 0) // Si le tableau est non vide, on copie les adresses des objets pointés dans tmp
            memcpy(tmp, tab, nb*sizeof(T*));
        tab = tmp;
        delete[] old;
        old = 0;
        tmp = 0;
    }
    tab[nb++] = t;
}


/*
Handler Manager::handler = Handler::Handler();
Manager::Manager():nb(0),max(0),tab(0){std::cout << "Manager créé\n";}
Manager::~Manager(){
    for(int i = 0; i < nb; i++)
        delete tab[i];
    delete[] tab;
    nb = 0;
    max = 0;
    tab = 0;
    std::cout << "Manager supprimé\n";
}
Manager& Manager::getInstance(){
    if(handler.instance == 0)
        handler.instance = new Manager;
    return *handler.instance;
}
void Manager::freeInstance(){
    std::cout << "Appel de Free Instance\n";
    delete handler.instance;
    handler.instance = 0;
}
void Manager::addItem(int *t){
    if(nb == max){
        max+=10;
        int** tmp = new int*[max];
        int** old = tab;
        if(nb > 0) // Si le tableau est non vide, on copie les adresses des objets pointés dans tmp
            memcpy(tmp, tab, nb*sizeof(int*));
        tab = tmp;
        delete[] old;
        old = 0;
        tmp = 0;
    }
    tab[nb++] = t;
}

*/