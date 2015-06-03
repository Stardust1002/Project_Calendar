#ifndef AJOUTERPROJET_H
#define AJOUTERPROJET_H

#include <QDialog>
#include "fonctions.h"

namespace Ui {
class ajouterProjet;
}

class ajouterProjet : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterProjet(QWidget *parent = 0);
    ~ajouterProjet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ajouterProjet *ui;
};

#endif // AJOUTERPROJET_H
