#ifndef AJOUTERTACHECOMPOSITE_H
#define AJOUTERTACHECOMPOSITE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class ajouterTacheComposite;
}
///Fenêtre d'ajout et de modification de TacheComposite
class ajouterTacheComposite : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterTacheComposite(TacheComposite *tache = 0, QWidget *parent = 0);
    ~ajouterTacheComposite();

private slots:
    void on_pushButton_clicked();

    void on_projet_currentIndexChanged(const QString &arg1);

private:
    TacheComposite* tache_composite;
    bool updatable;
    Ui::ajouterTacheComposite *ui;
};

#endif // AJOUTERTACHECOMPOSITE_H
