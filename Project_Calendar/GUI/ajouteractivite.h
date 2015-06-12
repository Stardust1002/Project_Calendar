#ifndef AJOUTERACTIVITE_H
#define AJOUTERACTIVITE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class ajouterActivite;
}
///Fenêtre d'ajout et de modification d'Activite
class ajouterActivite : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterActivite(Activite* activite = 0, QWidget *parent = 0);
    ~ajouterActivite();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Activite* activite;
    Ui::ajouterActivite *ui;
    QWidget* parent;
};

#endif // AJOUTERACTIVITE_H
