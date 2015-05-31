#ifndef PROGRAMMATIONACTIVITE_H
#define PROGRAMMATIONACTIVITE_H

#include <QDialog>
#include "fonctions.h"

namespace Ui {
class programmationActivite;
}

class programmationActivite : public QDialog
{
    Q_OBJECT

public:
    explicit programmationActivite(QWidget *parent = 0);
    ~programmationActivite();

private slots:
    void on_programmer_clicked();

private:
    Ui::programmationActivite *ui;
};

#endif // PROGRAMMATIONACTIVITE_H
