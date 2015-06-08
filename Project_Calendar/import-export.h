#ifndef IMPORTEXPORT
#define IMPORTEXPORT

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "evenement.h"
#include <QFile>

class Format{
protected:
    QString pathname;
    Format(const QString& p):pathname(p){}
    Format(const Format &){}
    Format& operator=(const Format&){}
    virtual ~Format()=0{}

public:
    void setPathname(const QString& p){pathname = p;}
    const QString& getPathname(){return pathname;}
    virtual void save()const=0;
    virtual void load()const=0;
};

class XML : public Format{
    struct Handler{
        XML* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){XML::freeInstance();}
    };
    static Handler handler;
    XML(const QString &p):Format(p){}
public:
    static XML& getInstance(const QString& p = "auto-save.xml");
    static void freeInstance();
    void save() const override;
    void saveProjet(QXmlStreamWriter& stream, const Projet& proj)const;
    void saveTache(QXmlStreamWriter& stream, const Tache& tache)const;
    void saveActivite(QXmlStreamWriter& stream, const Activite& act)const;
    void saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const;
    void savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const;

    void load()const override;
    void loadProjet(QXmlStreamReader& stream)const;
    Tache& loadTache(QXmlStreamReader& stream)const;
    void loadActivite(QXmlStreamReader& stream)const;
    void loadProgrammation(QXmlStreamReader& stream)const;
    void loadPrecedence(QXmlStreamReader& stream)const;
};

class Memento{
    Format* strategie;
    Memento(Format &s):strategie(&s){}
    Memento(const Memento &){}
    Memento& operator=(const Memento&){}
    struct Handler{
        Memento* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){Memento::freeInstance();}
    };
    static Handler handler;
public:
    static void freeInstance();
    static Memento& getInstance(Format &strategie = XML::getInstance());
    void setStrategie(Format* strat){strategie = strat;}
    void save()const{strategie->save();}
    void load()const{strategie->load();}
};

#endif // IMPORTEXPORT

