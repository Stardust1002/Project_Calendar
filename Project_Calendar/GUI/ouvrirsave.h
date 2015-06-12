#ifndef OUVRIRSAVE_H
#define OUVRIRSAVE_H

#include <QDialog>

namespace Ui {
class ouvrirsave;
}
///Fenêtre du choix de fichier de sauvegarde.
class ouvrirsave : public QDialog
{
    Q_OBJECT

public:
    explicit ouvrirsave(QWidget *parent = 0);
    ~ouvrirsave();

private:
    Ui::ouvrirsave *ui;
};

#endif // OUVRIRSAVE_H
