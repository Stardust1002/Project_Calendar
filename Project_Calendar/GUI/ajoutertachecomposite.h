#ifndef AJOUTERTACHECOMPOSITE_H
#define AJOUTERTACHECOMPOSITE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class ajouterTacheComposite;
}

class ajouterTacheComposite : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterTacheComposite(TacheComposite *tache = 0, QWidget *parent = 0);
    ~ajouterTacheComposite();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ajouterTacheComposite *ui;
};

#endif // AJOUTERTACHECOMPOSITE_H