#ifndef AJOUTERPROJET_H
#define AJOUTERPROJET_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class ajouterProjet;
}
///Fenêtre d'ajout et de modification de Projet
class ajouterProjet : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterProjet(Projet *projet = 0, QWidget *parent = 0);
    ~ajouterProjet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ajouterProjet *ui;
    Projet* projet;
};

#endif // AJOUTERPROJET_H
