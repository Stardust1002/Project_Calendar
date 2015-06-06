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
    qDebug()<<d;
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime dispo = QDateTime::fromString(d,format);
    if(!dispo.isValid())
        throw "Format DateTime de la disponibilite invalide";
    qDebug()<<dispo;
    setDisponibiliteDT(dispo);
}
void Tache::setEcheance(const QString& e){
    QString format = "dd:MM:yyyy:HH:mm";
    QDateTime echeance = QDateTime::fromString(e,format);
    if(!echeance.isValid())
        throw "Format DateTime de l'échéance invalide";
    setEcheanceDT(echeance);
}
void Tache::afficher()const{
    qDebug() << "ID: " << getId() <<
              "\nTitre: " << getTitre();
    qDebug() << "Date de disponibilité: " << getDisponibilite().toString();
  qDebug() << "Date d'echeance: " << getEcheance().toString();
}

Projet* Tache::getProjet()const{
    ProjetManager& PM = ProjetManager::getInstance();
    ProjetManager::iterator it = PM.begin();
    while(it != PM.end() && !(*it)->possede(*this))++it;
    if(it == PM.end())return static_cast<Projet*>(nullptr);
    return *it;
    }
void Tache::setProjet(Projet& p){

    if(p.getDisponibilite() <= getDisponibilite()){
    Projet* old = getProjet();
    if(old != nullptr)old->retirerTache(this); //on retire la tache de son ancien projet
    p.ajouterTache(this); //on la rajoute dans le nouveau projet
    }
    else
        ouvrirWarning("Attention, la date de disponibilité de la tache est inférieure à celle du projet !\nAucun projet n'a donc été affecté/réaffecté","Erreur");
}

void Tache::setProjet(const QString& id){
    ProjetManager& PM = ProjetManager::getInstance();
    Projet* p = PM.getItem(id);
    setProjet(*p);
}

TacheComposite* Tache::getComposite()const{
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
    return NULL;
}

void TacheUnitaire::afficher()const{
    qDebug() << "\nTache Unitaire:";
    Tache::afficher();
    qDebug() << "Duree: " << getDuree();
    if(isPreemptive())qDebug()<< "Preemptive: oui\n";
    else qDebug()<< "Preemptive: non\n";
}

void TacheComposite::afficher(){
    qDebug() << "\nTache Composite:";
    Tache::afficher();
    for(iterator it = this->begin(); it != this->end(); ++it)
        (*it)->afficher();
}
TacheComposite::~TacheComposite(){
    for(iterator it = this->tab.begin(); it != this->tab.end(); ++it){
        TacheManager::getInstance().deleteItem(**it);
    }
    this->tab.clear();
}
/*Projet::Projet(QString id, QString t, QDateTime d, vector<Tache*> t):identificateur(id), titre(t), date_dispo(d){
    for(vector<Tache*>::iterator it = t.begin(); it != t.end(); ++it){
       tab.push_back(*it);
    }
}
*/
TacheComposite::TacheComposite(const QString& id, const QString& title, vector<Tache*> t, const QDateTime& date_dispo, const QDateTime& date_echeance):Tache(id, title,date_dispo,date_echeance){
    for(iterator it = t.begin(); it != t.end(); ++it)
        tab.push_back(*it);
}


bool TacheComposite::isComposable(const Tache& t)const{
    if(t.getComposite() || t.getDisponibilite() < getDisponibilite() || t.getEcheance() > getEcheance() || PrecedenceManager::getInstance().isPredecesseur(t,*this))
        return false;
    return true;
}

void TacheComposite::push_back(Tache &t){
    if(!isComposable(t))
        throw "Error : Tache composite ne peut être composée de cette tâche";
    tab.push_back(&t);
}

void TacheComposite::setDisponibiliteDT(const QDateTime& dispo){
    iterator it = tab.begin();
    const QDateTime* minDispo = &(*it)->getDisponibilite();
    it++;
    for(;it != tab.end();it++)
        if((*it)->getDisponibilite() < *minDispo)
            minDispo = &(*it)->getDisponibilite();
    qDebug()<<"minDispo : "<<*minDispo<<"\tdispo : "<<dispo;
    if(*minDispo < dispo)
        throw "error : Tache Composite possédant une tache disponible avant elle même";
    Tache::setDisponibiliteDT(dispo);
}

void TacheComposite::setEcheanceDT(const QDateTime& echeance){
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
    TacheManager& TM = TacheManager::getInstance();
    if(t != 0 && TM.getItem(t->getId()))tab.push_back(t);
    else throw "Olalala: Tache inexistante";
}
void Projet::retirerTache(Tache* t){
    if(t == 0) throw "Olalala: Tache inexistance";
    for(iterator it = tab.begin(); it != tab.end(); ++it)
        if(*it == t){
            tab.erase(it);
            return;
        }
    throw "Olalala: Tache inexistante";
}
void Projet::ajouterTache(const QString& id){
  TacheManager& TM = TacheManager::getInstance();
  ajouterTache(TM.getItem(id));
}

void Projet::retirerTache(const QString& id){
      TacheManager& TM = TacheManager::getInstance();
      retirerTache(TM.getItem(id));
}

void Projet::afficher(){
    qDebug() << "Projet:\nId: " << getId();
    qDebug() << "Titre: " << getTitre();
    qDebug() << "Disponibilité: "<< getDisponibilite();
    qDebug() << "Echeance: " << getEcheance();
    qDebug() << "Nombre de tâches: " << getSize();

    for(iterator it = tab.begin(); it != tab.end(); ++it)
        (*it)->afficher();
}

bool Projet::possede(const Tache &t){
   iterator it = tab.begin();
   while(it != tab.end() && *it != &t)++it;
   if(it == tab.end())return false;
   return true;
}

/* ------------------------------- */
/* ---------- ACTIVITE ----------- */
/* ------------------------------- */

void Activite::afficher()const{
    qDebug() << "Activite: \nIdentificateur: " << getId();
    qDebug() << "Titre: " << getTitre();
    if(getType() == Activite::RDV)
        qDebug() << "Type: Rendez-vous";
    else
        qDebug() << "Type: Réunion";
    qDebug() << "Durée: " << getDuree();
}



