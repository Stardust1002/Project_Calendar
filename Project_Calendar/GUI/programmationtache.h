#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"
#include "mainwindow.h"
namespace Ui {
class programmationTache;
}
///Fenêtre d'ajout et de modification de Programmation de Tache.
class programmationTache : public QDialog
{
    Q_OBJECT

public:
    explicit programmationTache(TacheUnitaire *tache = 0, QWidget *parent = 0);
    ~programmationTache();

private slots:
    void on_programmer_clicked();
    void on_deprog_clicked();

    void on_statut_activated(int index);

    void on_tache_activated(const QString &arg1);

    void on_listeprogrammation_activated(const QString &arg1);

private:
    TacheUnitaire* tache;
    QWidget* parent;
    Ui::programmationTache *ui;
};

#endif // PROGRAMMATIONTACHE_H
