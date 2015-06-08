#ifndef PROGRAMMATIONACTIVITE_H
#define PROGRAMMATIONACTIVITE_H

#include <QDialog>
#include "fonctions.h"
#include "../evenement.h"
#include "../manager.h"

namespace Ui {
class programmationActivite;
}

class programmationActivite : public QDialog
{
    Q_OBJECT

public:
    explicit programmationActivite(Activite *activite, QWidget *parent = 0);
    ~programmationActivite();

private slots:
    void on_programmer_clicked();


    void on_deprogrammer_clicked();

    void on_status_currentIndexChanged(int index);

    void on_activity_currentIndexChanged(const QString &arg1);

private:
    Ui::programmationActivite *ui;
    Activite* activite;
    QWidget* parent;
};

#endif // PROGRAMMATIONACTIVITE_H
