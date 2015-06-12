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
#include <QFileDialog>
#include "vueglobale.h"
#include "import-export.h"

namespace Ui {
class MainWindow;
}
///Fenêtre Principale du calendrier
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void refresh_calendar(const QDate& date);
    void refresh_calendar();
    const QDate& MainWindow::getCurrentDate()const;

    ~MainWindow();

private slots:

    void on_newActivity_triggered(Activite *a = 0);

    void on_actionUnitaire_triggered(TacheUnitaire *t = 0);

    void on_actionCr_er_un_Projet_triggered(Projet *p = 0);

    void on_actionComposite_triggered();

    void on_actionProgrammer_une_Tache_triggered();

    void on_actionProgrammer_une_Activit_triggered();

    void on_pushButton_2_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_voir_clicked();

    void on_actionVue_Globale_triggered();


    void on_actionOuvrir_triggered();

    void on_actionEnregistrer_Sous_triggered();

private:
    Ui::MainWindow *ui;
    QDate date_calendrier;

    enum JOUR{
        LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
    };
};

#endif // MAINWINDOW_H
