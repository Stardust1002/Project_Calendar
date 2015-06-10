#ifndef OUVRIRSAVE_H
#define OUVRIRSAVE_H

#include <QDialog>

namespace Ui {
class ouvrirsave;
}

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
