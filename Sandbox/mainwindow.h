#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include "ajouteractivite.h"
#include "tacheediteur.h"
#include "ajouterprojet.h"
#include "ajoutertachecomposite.h"
#include "programmationtache.h"
#include "programmationactivite.h"
#include <QDebug>
#include <QTableWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_newActivity_triggered();

    void on_actionUnitaire_triggered();

    void on_actionCr_er_un_Projet_triggered();

    void on_actionComposite_triggered();

    void on_actionProgrammer_une_Tache_triggered();

    void on_actionProgrammer_une_Activit_triggered();

    void on_pushButton_2_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_voir_clicked();

private:
    Ui::MainWindow *ui;
    enum JOUR{
        LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
    };
};

#endif // MAINWINDOW_H
