#include "import-export.h"
#include "manager.h"

XML::Handler XML::handler;
Memento::Handler Memento::handler;


void XML::freeInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

void Memento::freeInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

XML& XML::getInstance(const QString& pathname){
    if(handler.instance == nullptr)
        return * new XML(pathname);
    return *handler.instance;
}

Memento& Memento::getInstance(Format &strategie){
    if(handler.instance == nullptr)
        return * new Memento(strategie);
    return *handler.instance;
}


void XML::saveProjet(QXmlStreamWriter& stream, const Projet& proj)const{
    stream.writeStartElement("Projet");
    stream.writeAttribute("identificateur",proj.getId());
    stream.writeAttribute("titre",proj.getTitre());
    stream.writeAttribute("disponibilite",proj.getDisponibilite().toString("dd-MM-yyyy HH:mm"));
    //Sauvegarde de l'ensemble des tâches du projet
    stream.writeStartElement("Taches");
    for(Projet::const_iterator it = proj.begin() ; it != proj.end() ; it++){
        saveTache(stream, **it);
    }
    stream.writeEndElement();
    //Fin du bloc de tâches
    stream.writeEndElement();
}
void XML::saveTache(QXmlStreamWriter& stream, const Tache& tache)const{
    bool isTacheUnitaire = (typeid(tache) == typeid(TacheUnitaire));
    stream.writeStartElement("Tache");
    if(isTacheUnitaire)
        stream.writeAttribute("identificateur",QString("u_")+tache.getId());
    else
        stream.writeAttribute("identificateur",QString("c_")+tache.getId());
    stream.writeAttribute("titre",tache.getTitre());
    if(isTacheUnitaire)
    {
        const TacheUnitaire& tu = dynamic_cast<const TacheUnitaire&>(tache);
        stream.writeAttribute("duree",tu.getDuree().toString("hh:mm"));
        if(tu.isPreemptive())
            stream.writeAttribute("preemptive","true");
        else
            stream.writeAttribute("preemptive","false");
    }
    stream.writeAttribute("disponibilite",tache.getDisponibilite().toString("dd-MM-yyyy HH:mm"));
    stream.writeAttribute("echeance",tache.getEcheance().toString("dd-MM-yyyy HH:mm"));
    if(!isTacheUnitaire)
    {
        const TacheComposite& tc = dynamic_cast<const TacheComposite&>(tache);
        // Sauvegarde de l'ensemble des sous tâches
        stream.writeStartElement("Sous_Taches");
        for(TacheComposite::const_iterator it = tc.begin() ; it != tc.end() ; it++)
            saveTache(stream,**it);
        stream.writeEndElement();
        // Fin du bloc des sous tâches
    }
    stream.writeEndElement();
}

void XML::saveActivite(QXmlStreamWriter& stream, const Activite& act)const{
    stream.writeStartElement("Activite");
    stream.writeAttribute("identificateur",act.getId());
    stream.writeAttribute("titre",act.getTitre());
    stream.writeAttribute("type",act.getTypeToString());
    stream.writeAttribute("duree",act.getDuree().toString("hh:mm"));
    stream.writeEndElement();
}

void XML::saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const{
    bool isActivite = (typeid(prog.getEvenement()) == typeid(Activite&));

    stream.writeStartElement("Programmation");
    if(isActivite)
        stream.writeAttribute("id_evenement",QString("a_")+prog.getEvenement().getId());
    else
        stream.writeAttribute("id_evenement",QString("t_")+prog.getEvenement().getId());
    stream.writeAttribute("date",prog.getDate().toString("dd-MM-yyyy HH:mm"));
    stream.writeAttribute("duree",prog.getDuree().toString("hh:mm"));
    stream.writeEndElement();
}

void XML::savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const{
    stream.writeStartElement("Precedence");
    stream.writeAttribute("id_predecesseur",prec.getPredecesseur().getId());
    stream.writeAttribute("id_successeur",prec.getSuccesseur().getId());
    stream.writeEndElement();

}


void XML::save()const{
    QXmlStreamWriter stream;
    QFile file(pathname);

    if (!file.open(QIODevice::WriteOnly))
    {
      throw "Error : Impossible d'ouvrir le fichier";
    }
    else
    {
        ProgrammationManager& progM = ProgrammationManager::getInstance();
        PrecedenceManager& precM = PrecedenceManager::getInstance();
        ActiviteManager& actM = ActiviteManager::getInstance();
        ProjetManager& projM = ProjetManager::getInstance();
        TacheManager& tacheM = TacheManager::getInstance();

        stream.setAutoFormatting(true);
        stream.setDevice(&file);

        stream.writeStartDocument();

        //   ****************************************
        //   *** Sauvegarde des projets et tâches ***
        //   ****************************************
        stream.writeStartElement("Projets");
        for(ProjetManager::iterator it = projM.begin() ; it != projM.end() ; it++)
            saveProjet(stream,**it);
        stream.writeEndElement();

        stream.writeStartElement("Tache non defini");
        for(TacheManager::iterator it = tacheM.begin() ; it != tacheM.end() ; it++){
            if(!(*it)->getProjet())
                saveTache(stream,**it);
        }
        stream.writeEndElement();


        //   ********************************
        //   *** Sauvegarde des activites ***
        //   ********************************
        stream.writeStartElement("Activites");
        for(ActiviteManager::iterator it = actM.begin() ; it != actM.end() ; it++)
            saveActivite(stream,**it);
        stream.writeEndElement();


        //   **********************************
        //   *** Sauvegarde des precedences ***
        //   **********************************
        stream.writeStartElement("Precedences");
        for(PrecedenceManager::iterator it = precM.begin() ; it != precM.end() ; it++)
            savePrecedence(stream,**it);
        stream.writeEndElement();


        //   *************************************
        //   *** Sauvegarde des programmations ***
        //   *************************************
        stream.writeStartElement("Programmations");
        for(ProgrammationManager::iterator it = progM.begin() ; it != progM.end() ; it++)
            saveProgrammation(stream,**it);
        stream.writeEndElement();

        stream.writeEndDocument();
    }
}

void XML::loadActivite(QXmlStreamReader& stream)const{
    if(!(stream.name().toString() == "Activite"))
        throw "Error : Fichier XML corrompu";
    Activite::TypeActivite type;
    QString& id = stream.attributes().value("identificateur").toString();
    QString& titre = stream.attributes().value("titre").toString();
    QString& s_type = stream.attributes().value("type").toString();
    (s_type == "Rendez-vous")?type=Activite::RDV : type=Activite::REUNION;
    QString& duree = stream.attributes().value("duree").toString();
    ActiviteManager::getInstance().ajouterActivite(id,titre,type,duree);
    stream.readNext();
}
void XML::loadProjet(QXmlStreamReader& stream)const{
    /*if(!(stream.name().toString() == "Projet"))
        throw "Error : Fichier XML corrompu";
    QString& id = stream.attributes().value("identificateur").toString();
    QString& titre = stream.attributes().value("titre").toString();
    QString& dispo = stream.attributes().value("disponibilite").toString();
    Projet& proj = ProjetManager::getInstance().ajouterProjet(id,titre,dispo);
    if(stream.readNextStartElement() && stream.name().toString() == "Taches"){
        while(stream.readNextStartElement()){
            Tache& tache = loadTache(stream);
        }

        // Ajouter contraintes de Precedence dans ajouter Programmation !!!!!!!

    }*/


}
Tache& XML::loadTache(QXmlStreamReader& stream)const{
    if(!(stream.name().toString() == "Tache"))
        throw "Error : Fichier XML corrompu";

}

void XML::loadProgrammation(QXmlStreamReader& stream)const{
    if(!(stream.name().toString() == "Programmation"))
        throw "Error : Fichier XML corrompu";
    Evenement* event;
    QString& id = stream.attributes().value("id_evenement").toString();
    if(id.startsWith("a"))
        event = ActiviteManager::getInstance().getItem(id.remove(0,2));
    else
        event = dynamic_cast<TacheUnitaire*>(TacheManager::getInstance().getItem(id.remove(0,2)));
    QString& date = stream.attributes().value("date").toString();
    QString& duree = stream.attributes().value("duree").toString();
    ProgrammationManager::getInstance().ajouterProgrammation(*event,date,duree);
}
void XML::loadPrecedence(QXmlStreamReader& stream)const{
    if(!(stream.name().toString() == "Precedence"))
        throw "Error : Fichier XML corrompu";
    QString& pred = stream.attributes().value("id_predecesseur").toString();
    QString& succ = stream.attributes().value("id_successeur").toString();
    TacheManager& tacheM = TacheManager::getInstance();
    PrecedenceManager::getInstance().ajouterPrecedence(*tacheM.getItem(pred), *tacheM.getItem(succ));
}


void XML::load()const{
}
