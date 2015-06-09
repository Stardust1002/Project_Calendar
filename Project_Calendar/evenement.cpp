#include "evenement.h"
#include "manager.h"


/* ------------------------------- */
/* ----------- TACHE ------------ */
/* ------------------------------- */

const Tache& Tache::operator=(const Tache& t){
    identificateur = t.getId();
    titre = t.getTitre();
    date_echeance = t.getEcheance();
    date_dispo = t.getDisponibilite();
    return *this;
}
void Tache::setDisponibilite(const QString& d){
    /*!
      La méthode setDisponibilite() permet de modifier la date de disponibilite de la tâche.
    */
    qDebug()<<d;
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime dispo = QDateTime::fromString(d,format);
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    qDebug()<<dispo;
    setDisponibiliteDT(dispo);
}
void Tache::setEcheance(const QString& e){
    /*!
      La méthode setEcheance() permet de modifier la date d'écheance de la tâche.
    */
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime echeance = QDateTime::fromString(e,format);
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    setEcheanceDT(echeance);
}
void Tache::afficher()const{
    /*!
      La méthode afficher() permet d'afficher en mode debug les attributs de la tâche.
    */
    qDebug() << "ID: " << getId() <<
              "\nTitre: " << getTitre();
    qDebug() << "Date de disponibilité: " << getDisponibilite().toString();
  qDebug() << "Date d'echeance: " << getEcheance().toString();
}

Projet* Tache::getProjet()const{
    /*!
      La méthode getProjet() renvoie un pointeur sur le projet lié à la tâche.
      Si la tache n'est dans aucun projet, getProjet() renvoie un pointeur null.
    */
    ProjetManager& PM = ProjetManager::getInstance();
    ProjetManager::iterator it = PM.begin();
    while(it != PM.end() && !(*it)->possede(*this))++it;
    if(it == PM.end())return static_cast<Projet*>(nullptr);
    return *it;
    }
void Tache::setProjet(Projet& p){
    /*!
      La méthode setProjet permet de lier une tâche à un projet.
      Si cette dernière est déjà liée, cette liaison sera supprimée puis remplacée.
    */
    if(p.getDisponibilite() <= getDisponibilite()){
    Projet* old = getProjet();
    if(old != nullptr)old->retirerTache(this); //on retire la tache de son ancien projet
    p.ajouterTache(this); //on la rajoute dans le nouveau projet
    }
    else
        ouvrirWarning("Attention, la date de disponibilité de la tache est inférieure à celle du projet !\nAucun projet n'a donc été affecté/réaffecté","Erreur");
}

void Tache::setProjet(const QString& id){
    /*!
      Voir setProjet(Projet& P).
    */
    ProjetManager& PM = ProjetManager::getInstance();
    Projet* p = PM.getItem(id);
    setProjet(*p);
}

vector<Precedence*> Tache::getPrecedences()const{
    /*!
      La méthode getPrecedences() renvoie un vecteur contenant les précédences de la tache.
    */
    vector<Precedence*> Liste;
    PrecedenceManager& PrM = PrecedenceManager::getInstance();
    for(PrecedenceManager::const_iterator it = PrM.begin(); it != PrM.end(); ++it){
        if(&((*it)->getSuccesseur()) == this)
           Liste.push_back(*it);
    }
    return Liste;
}

TacheComposite* Tache::getComposite()const{
    /*!
      La méthode getComposite() renvoie un pointeur sur la tâche composite composé de la tâche.
      Si cette dernière ne compose pas de tâche composite, un pointeur null sera renvoyé.
    */
    TacheManager& TM = TacheManager::getInstance();
    for(TacheManager::iterator it = TM.begin(); it != TM.end() ; it++){
        if(typeid(**it) == typeid(TacheComposite)){
            TacheComposite& tc = dynamic_cast<TacheComposite&>(**it);
            for(TacheComposite::iterator itC = tc.begin(); itC != tc.end() ; itC++){
                if(*itC == this)
                    return &tc;
            }
        }

    }
    return 0;
}

void TacheUnitaire::afficher()const{
    /*!
      La méthode afficher() permet d'afficher en mode debug les attributs de la tâche.
    */
    qDebug() << "\nTache Unitaire:";
    Tache::afficher();
    qDebug() << "Duree: " << getDuree();
    if(isPreemptive())qDebug()<< "Preemptive: oui\n";
    else qDebug()<< "Preemptive: non\n";
}

vector<Programmation*> Evenement::getProgrammations()const{ //renvoi les prog par date croissante
    /*!
      La méthode getProgrammations() renvoie un vecteur de pointeurs sur les éventuelles programmations de l'évènement.
    - Si ce dernier n'a pas été programmé, un vecteur vide sera retourné.
    - Egalement, si une tâche préemptive appelle cette méthode, plusieurs pointeurs de programmation sont susceptibles d'être retournés au sein du vecteur.
    - Sinon un seul pointeur de programmation sera retourné dans le vecteur.
    */
    vector<Programmation*> liste;
    ProgrammationManager& ProM = ProgrammationManager::getInstance();
    for(ProgrammationManager::const_iterator it = ProM.begin(); it != ProM.end(); ++it){
        if(&((*it)->getEvenement()) == this){
            vector<Programmation*>::iterator it2 = liste.begin();
            while(it2 != liste.end() && (*it2)->getDate() < (*it)->getDate())++it2;
                liste.push_back(*it);
        }
    }
    return liste;
}

void TacheComposite::afficher(){
    /*!
La méthode afficher() permet d'afficher en mode debug les attributs et tâches composantes de la tâche composite.
    */
    qDebug() << "\nTache Composite:";
    Tache::afficher();
    for(iterator it = this->begin(); it != this->end(); ++it)
        (*it)->afficher();
}
TacheComposite::~TacheComposite(){
    /*!

    */
    for(iterator it = this->tab.begin(); it != this->tab.end(); ++it){
        TacheManager::getInstance().deleteItem(**it);
    }
    this->tab.clear();
}




TacheComposite::TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance):Tache(id, title,date_dispo,date_echeance){
    for(iterator it = t.begin(); it != t.end(); ++it)
        tab.push_back(*it);
}


bool TacheComposite::isComposable(const Tache& t)const{
    /*!
La méthode isComposable() renvoie true si la tâche en paramètre peut être inclue dans la tâche composite.
    */
    if(t.getComposite() || t.getDisponibilite() < getDisponibilite() || t.getEcheance() > getEcheance() || PrecedenceManager::getInstance().isPredecesseur(t,*this))
        return false;
    return true;
}

void TacheComposite::push_back(Tache &t){
    /*!
La méthode push_back() vérifie si la tâche en paramètre peut être inclue dans la tâche composite.
Si oui, elle ajoute cette tâche dans cette dernière.    */
    if(!isComposable(t))
        throw "Error : Tache composite ne peut être composée de cette tâche";
    tab.push_back(&t);
}

void TacheComposite::setDisponibiliteDT(const QDateTime& dispo){
    /*!
La méthode setDisponibiliteDT() permet de modifier la date de disponibilité de la tâche composite.
    */
    iterator it = tab.begin();
    const QDateTime* minDispo = &(*it)->getDisponibilite();
    it++;
    for(;it != tab.end();it++)
        if((*it)->getDisponibilite() < *minDispo)
            minDispo = &(*it)->getDisponibilite();
    //qDebug()<<"minDispo : "<<*minDispo<<"\tdispo : "<<dispo;
    if(*minDispo < dispo)
        throw "error : Tache Composite possédant une tache disponible avant elle même";
    Tache::setDisponibiliteDT(dispo);
}

void TacheComposite::setEcheanceDT(const QDateTime& echeance){
    /*!
La méthode setDisponibiliteDT() permet de modifier la date d'échéance de la tâche composite.
    */

    iterator it = tab.begin();
    const QDateTime* maxEcheance = &(*it)->getDisponibilite();
    for(;it != tab.end();it++)
        if((*it)->getDisponibilite() > *maxEcheance)
            maxEcheance = &(*it)->getDisponibilite();
    if(*maxEcheance < echeance)
        throw "error : Tache Composite possédant une tache devant être terminée après elle même";
    Tache::setEcheanceDT(echeance);
}


/* ------------------------------- */
/* ----------- PROJET ------------ */
/* ------------------------------- */

 QDateTime Projet::getEcheance(){
     /*!
 La méthode getEcheance() renvoie la date d'échéance la plus lointaine parmi celles des tâches qui composent le projet..
     */

    if(tab.size() == 0)return QDateTime::fromString("01:01:1970 00:00", "dd:MM:yyyy HH:mm");
    iterator it = tab.begin();
    QDateTime maxEcheance = (*it)->getEcheance();
    ++it;
    for(;it != tab.end(); ++it){
        if((*it)->getEcheance() > maxEcheance)
            maxEcheance = (*it)->getEcheance();
    }
    return maxEcheance;
}
void Projet::ajouterTache(Tache* t){
    /*!
La méthode ajouterTache() ajoute la tâche correspondante dans le projet.
    */
    TacheManager& TM = TacheManager::getInstance();
    if(t != 0 && TM.getItem(t->getId()))tab.push_back(t);
    else throw "Olalala: Tache inexistante";
}
void Projet::retirerTache(Tache* t){
    /*!
La méthode retirerTache() retire la tâche correspondante du projet.
    */

    if(t == 0) throw "Olalala: Tache inexistance";
    for(iterator it = tab.begin(); it != tab.end(); ++it)
        if(*it == t){
            tab.erase(it);
            return;
        }
    throw "Olalala: Tache inexistante";
}
void Projet::ajouterTache(const QString& id){
    /*!
Voir ajouterTache(Tache* t);
    */

  TacheManager& TM = TacheManager::getInstance();
  ajouterTache(TM.getItem(id));
}

void Projet::retirerTache(const QString& id){
    /*!
Voir retirerTache(Tache* t);
    */
      TacheManager& TM = TacheManager::getInstance();
      retirerTache(TM.getItem(id));
}

void Projet::afficher(){
    /*!
La méthode afficher() permet d'afficher en mode debug les attributs et les tâches du projet.
    */
    qDebug() << "Projet:\nId: " << getId();
    qDebug() << "Titre: " << getTitre();
    qDebug() << "Disponibilité: "<< getDisponibilite();
    qDebug() << "Echeance: " << getEcheance();
    qDebug() << "Nombre de tâches: " << getSize();

    for(iterator it = tab.begin(); it != tab.end(); ++it)
        (*it)->afficher();
}

bool Projet::possede(const Tache &t){
    /*!
La méthode possede() renvoie true si le la tache en paramètre est liée au projet.
False sinon.
    */
   iterator it = tab.begin();
   while(it != tab.end() && *it != &t)++it;
   if(it == tab.end())return false;
   return true;
}

/* ------------------------------- */
/* ---------- ACTIVITE ----------- */
/* ------------------------------- */

void Activite::afficher()const{
    /*!
La méthode afficher() permet d'afficher en mode debug les attributs de l'activité.
    */
    qDebug() << "Activite: \nIdentificateur: " << getId();
    qDebug() << "Titre: " << getTitre();
    if(getType() == Activite::RDV)
        qDebug() << "Type: Rendez-vous";
    else
        qDebug() << "Type: Réunion";
    qDebug() << "Durée: " << getDuree();
}



