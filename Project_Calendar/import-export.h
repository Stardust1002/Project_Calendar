#ifndef IMPORTEXPORT
#define IMPORTEXPORT

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "evenement.h"
#include <QFile>

///Format est une classe virtuelle pure permettant la mise en place du pattern design Strategy.
///Les classes fillent qui en héritent peuvent alors être utiliser par le Memento afin de réaliser divers types d'exportations.
class Format{
protected:
    QString pathname;
    Format(const QString& p):pathname(p){}
    Format(const Format &){}
    Format& operator=(const Format&){}
    virtual ~Format()=0{}

public:
    void setPathname(const QString& p){
            ///Modifie le chemin courant du fichier de sauvegarde.
            pathname = p;}
    const QString& getPathname(){
            ///Renvoie le chemin courant du fichier de sauvegarde.
            return pathname;}
    virtual void save()const=0;
    virtual void load()const=0;
};

///la classe XML est un Format et permet d'exporter l'ensemble des données du calendrier sous forme XML.
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
///La classe Memento est un singleton memento permettant de charger et de sauvegarder l'ensemble des informations du calendrier.
///Elle les exporter selon une stratégie particulière, correspondant au format d'exportation.
///Cette stratégie peut être changée à tout moment par le biais de la méthode setStrategie.
///De plus, elle ne peut être instanciée directement mais peut être récupérer par le biais d'une référence ou d'un pointeur grâce à la méthode getInstance().
///Un Handler a été mis en place afin désalloué automatiquement l'instance en fin de processus.
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
    static Memento& getInstance(
            ///Renvoie une reference sur l'instance de Memento.
            Format &strategie = XML::getInstance());
    void setStrategie(Format* strat){
        ///Modifie la stratégie avec celle passée en paramètre
        strategie = strat;}
    void save()const{
        ///Sauve toutes les informations du calendrier à l'aide de la méthode de la stratégie actuelle.
        strategie->save();}
    void load()const{
        ///Charge toutes les informations du calendrier à l'aide de la méthode load() de la stratégie actuelle.
        strategie->load();}
};

#endif // IMPORTEXPORT

