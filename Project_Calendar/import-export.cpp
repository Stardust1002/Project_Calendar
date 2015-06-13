#include "import-export.h"
#include "manager.h"

XML::Handler XML::handler;
Memento::Handler Memento::handler;


void XML::freeInstance(){
    ///Libère l'instance de la stratégie XML et entraine sa désallocation mémoire.
    delete handler.instance;
    handler.instance = nullptr;
}

void Memento::freeInstance(){
    ///Libère l'instance du Memento et entraine sa désallocation mémoire.
    delete handler.instance;
    handler.instance = nullptr;
}

XML& XML::getInstance(const QString& pathname){
    ///Instancie un objet de la classe XML si aucune instanciation n'a été faite au préalable, et retourne sa référence.

    if(handler.instance == nullptr)
        return * new XML(pathname);
    return *handler.instance;
}

Memento& Memento::getInstance(Format &strategie){
    ///Instancie un objet de la classe Memento si aucune instanciation n'a été faite au préalable, et retourne sa référence.
    if(handler.instance == nullptr)
        return * new Memento(strategie);
    return *handler.instance;
}

void Memento::saveProject(const QString& id)const{
    ProjetManager& projM = ProjetManager::getInstance();
    ProjetManager::iterator it;
    for(it = projM.begin() ; it != projM.end() && (*it)->getId() != id; it++);
    if(it != projM.end())
        saveProject(**it);
}


void XML::saveProjet(QXmlStreamWriter& stream, const Projet& proj)const{
    ///Sauvegarde le projet dans le stream QXmlStreamWriter, tous deux passés en paramètre.
    ///La méthode sauvegarde également les tâches liées au projet en appelant saveTache().
    stream.writeStartElement("Projet");
    stream.writeAttribute("identificateur",proj.getId());
    stream.writeAttribute("titre",proj.getTitre());
    stream.writeAttribute("disponibilite",proj.getDisponibilite().toString("dd:MM:yyyy:HH:mm"));
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
    ///Sauvegarde la tâche dans le stream QXmlStreamWriter, tous deux passés en paramètre.

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
    stream.writeAttribute("disponibilite",tache.getDisponibilite().toString("dd:MM:yyyy:HH:mm"));
    stream.writeAttribute("echeance",tache.getEcheance().toString("dd:MM:yyyy:HH:mm"));
    if(!isTacheUnitaire)
    {
        const TacheComposite& tc = dynamic_cast<const TacheComposite&>(tache);
        // Sauvegarde de l'ensemble des sous tâches
        for(TacheComposite::const_iterator it = tc.begin() ; it != tc.end() ; it++)
            saveTache(stream,**it);
        // Fin du bloc des sous tâches
    }
    stream.writeEndElement();
}

void XML::saveActivite(QXmlStreamWriter& stream, const Activite& act)const{
    ///Sauvegarde l'activité dans le stream QXmlStreamWriter, tous deux passés en paramètre.
    stream.writeStartElement("Activite");
    stream.writeAttribute("identificateur",act.getId());
    stream.writeAttribute("titre",act.getTitre());
    stream.writeAttribute("type",act.getTypeToString());
    stream.writeAttribute("duree",act.getDuree().toString("hh:mm"));
    stream.writeEndElement();
}

void XML::saveProgrammation(QXmlStreamWriter& stream, const Programmation& prog)const{
    ///Sauvegarde la programmation dans le stream QXmlStreamWriter, tous deux passés en paramètre.

    bool isActivite = (typeid(prog.getEvenement()) == typeid(Activite&));

    stream.writeStartElement("Programmation");
    if(isActivite)
        stream.writeAttribute("id_evenement",QString("a_")+prog.getEvenement().getId());
    else
        stream.writeAttribute("id_evenement",QString("t_")+prog.getEvenement().getId());
    stream.writeAttribute("date",prog.getDate().toString("dd:MM:yyyy:HH:mm"));
    stream.writeAttribute("duree",prog.getDuree().toString("hh:mm"));
    stream.writeEndElement();
}

void XML::saveProgrammationExterne(QXmlStreamWriter& stream, const Programmation& prog)const{
    ///Sauvegarde la programmation et les informations de l'évenement correspondant dans le stream QXmlStreamWriter, tous deux passés en paramètre.

    bool isActivite = (typeid(prog.getEvenement()) == typeid(Activite&));
    stream.writeStartElement("Programmation");
    if(isActivite){
        const Activite& act = dynamic_cast<const Activite&>(prog.getEvenement());
        stream.writeAttribute("nom_evenement",act.getId());
        stream.writeAttribute("description",act.getTitre());
        stream.writeAttribute("type",act.getTypeToString());
    }
    else{
        const TacheUnitaire& tache = dynamic_cast<const TacheUnitaire&>(prog.getEvenement());
        stream.writeAttribute("nom_evenement",tache.getId());
        stream.writeAttribute("description",tache.getTitre());
    }
    stream.writeAttribute("date",prog.getDate().toString("dd:MM:yyyy:HH:mm"));
    stream.writeAttribute("duree",prog.getDuree().toString("hh:mm"));
    stream.writeAttribute("type","Tâche");
    stream.writeEndElement();
}

void XML::savePrecedence(QXmlStreamWriter& stream, const Precedence& prec)const{
    ///Sauvegarde la précédence dans le stream QXmlStreamWriter, tous deux passés en paramètre.
    stream.writeStartElement("Precedence");
    stream.writeAttribute("id_predecesseur",prec.getPredecesseur().getId());
    stream.writeAttribute("id_successeur",prec.getSuccesseur().getId());
    stream.writeEndElement();

}


void XML::save()const{
    ///Effectue la sauvegarde totale de l'ensemble des informations du calendrier au sein d'un fichier XML:
    ///- Projets: en appellant saveProjet()
    ///- Tâches: en appellant saveTache()
    ///- Activités: en appellant saveActivite()
    ///- Précédences: en appellant savePrecedence()
    ///- Programmations: en appellant saveProgrammation()
    ///
    ///Pour sauvegarder chaque item, la méthode save() parcourt les différents manager à l'aide d'un iterator.
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
        stream.writeStartElement("root");

        //   ****************************************
        //   *** Sauvegarde des projets et tâches ***
        //   ****************************************
        stream.writeStartElement("Projets");
        for(ProjetManager::iterator it = projM.begin() ; it != projM.end() ; it++)
            saveProjet(stream,**it);
        stream.writeEndElement();

        stream.writeStartElement("TacheNonDefini");
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

        stream.writeEndElement();
        stream.writeEndDocument();
    }
}

void XML::saveWeek(int week, int year)const{
    ///Effectue la sauvegarde de l'ensemble des programmations pour une semaine donnée en ajoutant les informations de l'evenement : nom, description, durée
    QXmlStreamWriter stream;
    QFile file(pathname);
    if (!file.open(QIODevice::WriteOnly))
    {
      throw "Error : Impossible d'ouvrir le fichier";
    }
    else
    {
        ProgrammationManager& progM = ProgrammationManager::getInstance();

        stream.setAutoFormatting(true);
        stream.setDevice(&file);

        stream.writeStartDocument();
        stream.writeStartElement("Programmations");
        stream.writeAttribute("Semaine",QString::number(week));
        stream.writeAttribute("Annee",QString::number(year));
        vector<Programmation*> progs = progM.getProgrammations(week,year);
        for(vector<Programmation*>::iterator it = progs.begin() ; it != progs.end() ; it++)
            saveProgrammationExterne(stream,**it);

        stream.writeEndElement();
        stream.writeEndDocument();
    }
}

void XML::saveProjet(const Projet& proj)const{
    ///Effectue la sauvegarde de l'ensemble des programmations pour un projet donnée en ajoutant les informations de l'evenement : nom, description, durée

    QXmlStreamWriter stream;
    QFile file(pathname);
    if (!file.open(QIODevice::WriteOnly))
    {
      throw "Error : Impossible d'ouvrir le fichier";
    }
    else
    {
        stream.setAutoFormatting(true);
        stream.setDevice(&file);

        stream.writeStartDocument();
        stream.writeStartElement("Projet");
        stream.writeAttribute("Nom",proj.getId());
        for(Projet::const_iterator it = proj.begin() ; it != proj.end() ; it++){
            if(typeid(**it) == typeid(TacheUnitaire)){
                const TacheUnitaire& tache = dynamic_cast<const TacheUnitaire&>(**it);
                vector<Programmation*> progs = tache.getProgrammations();
                for(vector<Programmation*>::iterator it = progs.begin(); it != progs.end() ; it++)
                    saveProgrammationExterne(stream,**it);
            }
        }

        stream.writeEndElement();
        stream.writeEndDocument();
    }

}



void XML::loadProjet(QXmlStreamReader& stream)const{
///Charge tous les projets au sein du ProjetManager depuis le stream de type QXmlStreamReader.
    if(!(stream.name().toString() == "Projet"))
        throw "Error : Fichier XML corrompu";
    QString& id = stream.attributes().value("identificateur").toString();
    QString& titre = stream.attributes().value("titre").toString();
    QString& dispo = stream.attributes().value("disponibilite").toString();
    Projet& proj = ProjetManager::getInstance().ajouterProjet(id,titre,dispo);
    if(stream.readNextStartElement() && stream.name().toString() == "Taches"){
        while(stream.readNextStartElement())
            proj.ajouterTache(&loadTache(stream));
        stream.readNextStartElement();
    }
    else
        throw "Error : Fichier XML corrompu";
}

Tache& XML::loadTache(QXmlStreamReader& stream)const{
///Charge toutes les tâches au sein du TacheManager depuis le stream de type QXmlStreamReader.

    if(!(stream.name().toString() == "Tache"))
        throw "Error : Fichier XML corrompu";
    QString& id = stream.attributes().value("identificateur").toString();
    QString& titre = stream.attributes().value("titre").toString();
    QString& dispo = stream.attributes().value("disponibilite").toString();
    QString& echeance = stream.attributes().value("echeance").toString();

    if(id.startsWith("u_")){
        QString& duree = stream.attributes().value("duree").toString();
        QString& s_preempt = stream.attributes().value("preemptive").toString();
        bool preempt = (s_preempt == "true");
        stream.readNext();
        if(TacheManager::getInstance().isIdFree(id.remove(0,2)))
            return TacheManager::getInstance().ajouterTacheUnitaire(id,titre,duree,preempt,dispo,echeance);
        else
            return *TacheManager::getInstance().getItem(id);
    }
    else{
        if(TacheManager::getInstance().isIdFree(id.remove(0,2))){
            TacheComposite &tc = TacheManager::getInstance().ajouterTacheComposite(id,titre,dispo,echeance);
            while(stream.readNextStartElement())
                tc.push_back(loadTache(stream));
            return tc;
        }
        else{
                stream.skipCurrentElement();
                return *TacheManager::getInstance().getItem(id);
            }
    }
}

void XML::loadActivite(QXmlStreamReader& stream)const{
///Charge toutes les activités au sein du ActiviteManager depuis le stream de type QXmlStreamReader.

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

void XML::loadPrecedence(QXmlStreamReader& stream)const{
///Charge toutes les précédences au sein du PrecedenceManager depuis le stream de type QXmlStreamReader.

    if(!(stream.name().toString() == "Precedence"))
        throw "Error : Fichier XML corrompu";
    QString& pred = stream.attributes().value("id_predecesseur").toString();
    QString& succ = stream.attributes().value("id_successeur").toString();
    TacheManager& tacheM = TacheManager::getInstance();
    PrecedenceManager::getInstance().ajouterPrecedence(*tacheM.getItem(pred), *tacheM.getItem(succ));
    stream.readNext();
}

void XML::loadProgrammation(QXmlStreamReader& stream)const{
///Charge toutes les programmations au sein du ProgrammationManager depuis le stream de type QXmlStreamReader.

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
    stream.readNext();
}

void XML::load()const{
    ///Effectue le chargement total de l'ensemble des informations du calendrier stockés dans un fichier XML.
    ///- Projets
    ///- Tâches
    ///- Activités
    ///- Précédences
    ///- Programmations

    QXmlStreamReader stream;
    QFile file(pathname);

    ProgrammationManager::freeInstance();
    PrecedenceManager::freeInstance();
    TacheManager::freeInstance();
    ActiviteManager::freeInstance();
    ProjetManager::freeInstance();


    if (!file.open(QIODevice::ReadOnly))
    {
      throw "Error : Impossible d'ouvrir le fichier";
    }
    else
    {
        stream.setDevice(&file);

        if((stream.readNext())!=QXmlStreamReader::StartDocument)
            throw "Error : Fichier XML corrompu";

        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "root"))
            throw "Error : Fichier XML corrompu";

        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "Projets"))
            throw "Error : Fichier XML corrompu";
        while(stream.readNextStartElement())
            loadProjet(stream);

        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "TacheNonDefini"))
            throw "Error : Fichier XML corrompu";
        while(stream.readNextStartElement())
            loadTache(stream);


        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "Activites"))
            throw "Error : Fichier XML corrompu";
        while(stream.readNextStartElement())
            loadActivite(stream);

        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "Precedences"))
            throw "Error : Fichier XML corrompu";
        while(stream.readNextStartElement())
            loadPrecedence(stream);

        if(!(stream.readNextStartElement()) || !(stream.name().toString() == "Programmations"))
            throw "Error : Fichier XML corrompu";
        while(stream.readNextStartElement()){
            loadProgrammation(stream);
        }
        stream.skipCurrentElement();
        if(!(stream.name().toString() == "root"))
            throw "Error : Fichier XML corrompu";
        file.close();

    }

}

