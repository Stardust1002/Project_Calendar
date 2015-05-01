//
//  Manager.h
//  project calendar
//
//  Created by Antoine Jeannot on 01/05/2015.
//  Copyright (c) 2015 Antoine Jeannot. All rights reserved.
//

#ifndef __project_calendar__Manager__
#define __project_calendar__Manager__

#include <iostream>
using namespace std;

template<class T>class Manager;
template<class T> class Handler{
    friend class Manager<T>;
    Manager<T>* instance;
public:
    Handler():instance(0){}
    virtual ~Handler(){Manager<T>::freeInstance();}
    
};

template<class T> class Manager{
    friend class Handler<T>;
    T** tab;
    unsigned int nb;
    unsigned int max;
    static Handler<T> handler;
    
    Manager& operator=(const Manager& m);
    Manager();
    ~Manager();
    
public:
    class iterator{
        T* current;
        
    public:
        iterator();
        void operator++();
        const T& end();
        T& operator*()const{return *current;};
    };
    
    static Manager& getInstance();
    static void freeInstance();
    void addItem(T* t);
    void deleteItem(T* t);
    T& getItem(const string& id)const;
    iterator begin() const;
    
};


/*
class Handler;

class Manager{
    friend class Handler;
    int** tab;
    unsigned int nb;
    unsigned int max;
    static Handler handler;
    
    Manager& operator=(const Manager& m);
    Manager();
    ~Manager();
    
public:
    class iterator{
        int* current;
        
    public:
        iterator();
        void operator++();
        const int& end();
        int& operator*()const{return *current;};
    };
    
    static Manager& getInstance();
    static void freeInstance();
    void addItem(int* t);
    void deleteItem(int* t);
    int& getItem(const string& id)const;
    iterator begin() const;
    
};

class Handler{
    friend class Manager;
    Manager* instance;
public:
    Handler():instance(0){}
    virtual ~Handler(){Manager::freeInstance();}
    
};

*/
#endif /* defined(__project_calendar__Manager__) */
