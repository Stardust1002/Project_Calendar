#ifndef IMPORTEXPORT
#define IMPORTEXPORT

#include <QXmlStreamWriter>
#include "evenement.h"
#include <QFile>

class Format{
protected:
    QString pathname;
    Format(){}
    Format(const Format &){}
    Format& operator=(const Format&){}
    virtual ~Format()=0{}

public:
    void setPathname(const QString& p){pathname = p;}
    const QString& getPathname(){return pathname;}
    virtual void save()const=0;
};

class XML : public Format{
    struct Handler{
        XML* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){XML::freeInstance();}
    };
    static Handler handler;
public:
    static XML& getInstance();
    static void freeInstance();
    void save() const override;
    void saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const;
    void savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const;
    void saveActivite(QXmlStreamWriter& stream, const Activite& act)const;
    void saveProjet(QXmlStreamWriter& stream, const Projet& proj)const;
    void saveTache(QXmlStreamWriter& stream, const Tache& tache)const;
};

class Export{
    Format* strategie;
    Export(){}
    Export(const Export &){}
    Export& operator=(const Export&){}
    struct Handler{
        Export* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){Export::freeInstance();}
    };
    static Handler handler;
public:
    static void freeInstance();
    static Export& getInstance();
    void setStrategie(Format* strat){strategie = strat;}
    void save()const{strategie->save();}
};

#endif // IMPORTEXPORT

