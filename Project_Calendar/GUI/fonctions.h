#ifndef FONCTIONS
#define FONCTIONS
#include <QMessageBox>
///Ouvre une fenêtre d'information dont le titre, la description et le parents sont passés en paramètre.
void ouvrirInformation(const QString& chaine, const QString& titre = "Information", QWidget* parent = 0);
///Ouvre une fenêtre d'avertissement dont le titre, la description et le parents sont passés en paramètres.
void ouvrirWarning(const QString& chaine, const QString& titre = "Attention", QWidget* parent = 0);
///Ouvre une fenêtre modale dont le titre, la description et le parents sont passés en paramètres.
int ouvrirQuestion(const QString& chaine, const QString& titre = "Question", QWidget* parent = 0);


#endif // FONCTIONS

