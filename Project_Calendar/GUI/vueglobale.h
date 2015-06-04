#ifndef VUEGLOBALE_H
#define VUEGLOBALE_H

#include <QDialog>
#include "fonctions.h"
#include "tacheediteur.h"
#include "ajoutertachecomposite.h"
#include "programmationactivite.h"
#include "programmationtache.h"
#include "ajouterprojet.h"

#include <QTreeWidgetItem>
namespace Ui {
class vueGlobale;
}

class vueGlobale : public QDialog
{
    Q_OBJECT

public:
    explicit vueGlobale(QWidget *parent = 0);
    ~vueGlobale();

private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::vueGlobale *ui;
};

#endif // VUEGLOBALE_H