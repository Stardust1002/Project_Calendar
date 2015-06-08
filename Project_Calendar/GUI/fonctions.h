#ifndef FONCTIONS
#define FONCTIONS
#include <QMessageBox>
void ouvrirInformation(const QString& chaine, const QString& titre = "Information", QWidget* parent = 0);
void ouvrirWarning(const QString& chaine, const QString& titre = "Attention", QWidget* parent = 0);
int ouvrirQuestion(const QString& chaine, const QString& titre = "Question", QWidget* parent = 0);


#endif // FONCTIONS

