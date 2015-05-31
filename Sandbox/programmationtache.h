#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include <QDialog>
#include "fonctions.h"
#include "calendar.h"
namespace Ui {
class programmationTache;
}

class programmationTache : public QDialog
{
    Q_OBJECT

public:
    explicit programmationTache(Tache* tache = 0, QWidget *parent = 0);
    ~programmationTache();

private slots:
    void on_programmer_clicked();
    void on_deprog_clicked();

private:
    Ui::programmationTache *ui;
};

#endif // PROGRAMMATIONTACHE_H
