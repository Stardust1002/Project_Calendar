#include "fonctions.h"
void ouvrirInformation(const QString& chaine, const QString& titre, QWidget* parent)
{
    QMessageBox::information(parent,titre,chaine);
}
void ouvrirWarning(const QString& chaine, const QString& titre, QWidget* parent)
{
    QMessageBox::warning(parent,titre,chaine);
}
int ouvrirQuestion(const QString& chaine, const QString& titre, QWidget* parent)
{
    return QMessageBox::question(parent,titre,chaine);
}
