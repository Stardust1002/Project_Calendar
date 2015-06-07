#include "import-export.h"
#include "manager.h"

XML::Handler XML::handler;
Export::Handler Export::handler;


void XML::freeInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

void Export::freeInstance(){
    delete handler.instance;
    handler.instance = nullptr;
}

XML& XML::getInstance(){
    if(handler.instance == nullptr)
        return * new XML;
    return *handler.instance;
}

Export& Export::getInstance(){
    if(handler.instance == nullptr)
        return * new Export;
    return *handler.instance;
}

void XML::saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const{
   /* stream.writeStartElement("Programmation");
    stream.writeAttribute("id_evenement",prog.getEvenement().getId());
    stream.writeAttribute("date",prog.getDate());
    stream.writeAttribute("duree",prog.getDuree());
    stream.writeEndElement();*/
}

void XML::savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const{
   /*stream.writeStartElement("Precedence");
    stream.writeAttribute("id_predecesseur",prec.getPredecesseur().getId());
    stream.writeAttribute("id_successeur",prec.getSuccesseur());
    stream.writeEndElement();*/

}
void XML::saveActivite(QXmlStreamWriter& stream, const Activite& act)const{

}
void XML::saveProjet(QXmlStreamWriter& stream, const Projet& proj)const{

}
void XML::saveTache(QXmlStreamWriter& stream, const Tache& tache)const{

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
        stream.writeStartElement("Programmations");
        for(ProgrammationManager::iterator it = progM.begin() ; it != progM.end() ; it++);


        stream.writeStartElement("Projets");





    }

}
