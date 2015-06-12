#ifndef PROGRAMMATIONACTIVITE_H
#define PROGRAMMATIONACTIVITE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class programmationActivite;
}
///Fenêtre d'ajout et de modification de Programmation d'Activite.
class programmationActivite : public QDialog
{
    Q_OBJECT

public:
    explicit programmationActivite(Activite *activite, QWidget *parent = 0);
    ~programmationActivite();

private slots:
    void on_programmer_clicked();

    void on_deprogrammer_clicked();

    void on_activity_activated(const QString &arg1);

    void on_status_activated(int index);

    void on_pushButton_clicked();

private:
    Ui::programmationActivite *ui;
    Activite* activite;
    QWidget* parent;
    bool actualisation_autorisee;
};

#endif // PROGRAMMATIONACTIVITE_H
