#include "ouvrirsave.h"
#include "ui_ouvrirsave.h"

ouvrirsave::ouvrirsave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ouvrirsave)
{
    ui->setupUi(this);
}

ouvrirsave::~ouvrirsave()
{
    delete ui;
}
