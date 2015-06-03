#ifndef AJOUTERACTIVITE_H
#define AJOUTERACTIVITE_H

#include <QDialog>
#include "fonctions.h"

namespace Ui {
class ajouterActivite;
}

class ajouterActivite : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterActivite(QWidget *parent = 0);
    ~ajouterActivite();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ajouterActivite *ui;
};

#endif // AJOUTERACTIVITE_H
