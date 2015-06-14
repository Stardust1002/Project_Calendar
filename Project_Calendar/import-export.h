#ifndef IMPORTEXPORT
#define IMPORTEXPORT

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "manager.h"
#include <QFile>

///Format est une classe virtuelle pure permettant la mise en place du pattern design Strategy et Template Method. Elle défini la structure du comportement d'importation et d'exportation mais laisse aux classes filles qui en héritent le choix du type d'exportation ou d'importation. Il est ainsi possible d'exporter sous un autre format ou bien sous le même format mais avec une structure de fichier différente et mieux adaptée à l'utilisation.
class Format{
protected:

    Format(){}
    Format(const Format &){}
    Format& operator=(const Format&){}
    virtual ~Format()=0{}

public:
    virtual void save(const QString& path)const;
    virtual void saveWeek(int week, int year,const QString& path)const =0;
    virtual void saveProjet(const Projet& proj,const QString& path)const =0;
    virtual void saveProjet(QXmlStreamWriter& stream, const Projet& proj)const=0;
    virtual void saveTache(QXmlStreamWriter& stream, const Tache& tache)const=0;
    virtual void saveActivite(QXmlStreamWriter& stream, const Activite& act)const =0;
    virtual void saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const=0;
    virtual void saveProgrammationExterne(QXmlStreamWriter& stream, const Programmation& prog)const=0;
    virtual void savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const=0;

    virtual void load(const QString& path)const;
    virtual void loadProjet(QXmlStreamReader& stream)const =0;
    virtual Tache& loadTache(QXmlStreamReader& stream)const =0;
    virtual void loadActivite(QXmlStreamReader& stream)const =0;
    virtual void loadProgrammation(QXmlStreamReader& stream)const =0;
    virtual void loadPrecedence(QXmlStreamReader& stream)const =0;

};

///La classe XML est un Format et permet d'exporter l'ensemble des données du calendrier sous forme XML.
class XML : public Format{
    struct Handler{
        XML* instance;
        Handler():instance(nullptr){}
        ~Handler(){XML::freeInstance();}
    };
    static Handler handler;
    XML():Format(){}
    XML& operator=(const XML&){}
public:
    static XML& getInstance();
    static void freeInstance();
    void saveWeek(int week, int year, const QString& path)const override;
    void saveProjet(const Projet& proj, const QString& path)const override;
    void saveProjet(QXmlStreamWriter& stream, const Projet& proj)const override;
    void saveTache(QXmlStreamWriter& stream, const Tache& tache)const override;
    void saveActivite(QXmlStreamWriter& stream, const Activite& act)const override;
    void saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const override;
    void saveProgrammationExterne(QXmlStreamWriter& stream, const Programmation& prog)const override;
    void savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const override;

    void loadProjet(QXmlStreamReader& stream)const override;
    Tache& loadTache(QXmlStreamReader& stream)const override;
    void loadActivite(QXmlStreamReader& stream)const override;
    void loadProgrammation(QXmlStreamReader& stream)const override;
    void loadPrecedence(QXmlStreamReader& stream)const override;
};
///La classe Memento est un singleton memento permettant de charger et de sauvegarder l'ensemble des informations du calendrier. Elle les exporter selon une stratégie particulière, correspondant au format d'exportation. Cette stratégie peut être changée à tout moment par le biais de la méthode setStrategie. De plus, elle ne peut être instanciée directement mais peut être récupérer par le biais d'une référence ou d'un pointeur grâce à la méthode getInstance(). Un Handler a été mis en place afin désalloué automatiquement l'instance en fin de processus.
class Memento{
    QString pathname;
    Format* strategie;
    Memento(Format &s,const QString& p):strategie(&s),pathname(p){}
    Memento(const Memento &){}
    Memento& operator=(const Memento&){}
    struct Handler{
        Memento* instance;
        Handler():instance(nullptr){}
        virtual ~Handler(){Memento::freeInstance();}
    };
    static Handler handler;
public:
    void setPathname(const QString& p){
            ///Modifie le chemin courant du fichier de sauvegarde.
            pathname = p;}
    const QString& getPathname(){
            ///Renvoie le chemin courant du fichier de sauvegarde.
            return pathname;}
    static void freeInstance();
    static Memento& getInstance(
            ///Renvoie une reference sur l'instance de Memento.
            Format &strategie = XML::getInstance(),const QString& path="auto-save.xml");
    void setStrategie(Format* strat){
        ///Modifie la stratégie avec celle passée en paramètre
        strategie = strat;}
    void save()const{
        ///Sauve toutes les informations du calendrier à l'aide de la méthode de la stratégie actuelle.
        strategie->save(pathname);}
    void saveWeek(int week, int year)const{
        ///Sauve toutes les programmations relatives à une semaine particulière ainsi que les évenements associés.
        strategie->saveWeek(week,year,pathname);
    }
    void saveProject(const QString& id)const;
        ///Sauve toutes les programmations relatives à un projet ainsi que les évenements associés. Le projet est repéré par son identificateur.
    void saveProject(const Projet& proj)const{
        ///Sauve toutes les programmations relatives à un projet ainsi que les évenements associés.
        strategie->saveProjet(proj,pathname);
    }
    void load()const{
        ///Charge toutes les informations d'un fichier externe dans l'application à l'aide de la méthode load() de la stratégie actuelle. Les données antérieures sont écrasées.
        ProgrammationManager::freeInstance();
        PrecedenceManager::freeInstance();
        TacheManager::freeInstance();
        ActiviteManager::freeInstance();
        ProjetManager::freeInstance();

        strategie->load(pathname);}
};

#endif // IMPORTEXPORT

