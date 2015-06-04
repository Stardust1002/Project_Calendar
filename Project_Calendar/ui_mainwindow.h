/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionProgrammer_une_Tache;
    QAction *actionVue_Globale;
    QAction *actionCr_er_un_Projet;
    QAction *actionUnitaire;
    QAction *actionComposite;
    QAction *newActivity;
    QAction *actionProgrammer_une_Activit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QCalendarWidget *calendarWidget;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *identificateur;
    QLabel *label_3;
    QLabel *date;
    QLabel *label_4;
    QLabel *duree;
    QLabel *label_2;
    QTextEdit *titre;
    QPushButton *pushButton_2;
    QPushButton *voir;
    QMenuBar *menuBar;
    QMenu *menuHello_World;
    QMenu *menuProgrammer_une_Activit;
    QMenu *menuGestion_des_Projets;
    QMenu *menuCr_er_une_T_che;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1139, 588);
        actionProgrammer_une_Tache = new QAction(MainWindow);
        actionProgrammer_une_Tache->setObjectName(QStringLiteral("actionProgrammer_une_Tache"));
        actionVue_Globale = new QAction(MainWindow);
        actionVue_Globale->setObjectName(QStringLiteral("actionVue_Globale"));
        actionCr_er_un_Projet = new QAction(MainWindow);
        actionCr_er_un_Projet->setObjectName(QStringLiteral("actionCr_er_un_Projet"));
        actionUnitaire = new QAction(MainWindow);
        actionUnitaire->setObjectName(QStringLiteral("actionUnitaire"));
        actionComposite = new QAction(MainWindow);
        actionComposite->setObjectName(QStringLiteral("actionComposite"));
        newActivity = new QAction(MainWindow);
        newActivity->setObjectName(QStringLiteral("newActivity"));
        actionProgrammer_une_Activit = new QAction(MainWindow);
        actionProgrammer_une_Activit->setObjectName(QStringLiteral("actionProgrammer_une_Activit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(847, 0));
        tableWidget->setMaximumSize(QSize(842, 16777215));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setAlternatingRowColors(true);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));

        horizontalLayout->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setMaximumSize(QSize(300, 200));
        calendarWidget->setCursor(QCursor(Qt::ArrowCursor));
        calendarWidget->setLayoutDirection(Qt::LeftToRight);
        calendarWidget->setGridVisible(true);

        verticalLayout->addWidget(calendarWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(false);
        groupBox->setFlat(false);
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        identificateur = new QLabel(groupBox);
        identificateur->setObjectName(QStringLiteral("identificateur"));

        formLayout->setWidget(0, QFormLayout::FieldRole, identificateur);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        date = new QLabel(groupBox);
        date->setObjectName(QStringLiteral("date"));

        formLayout->setWidget(1, QFormLayout::FieldRole, date);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        duree = new QLabel(groupBox);
        duree->setObjectName(QStringLiteral("duree"));

        formLayout->setWidget(2, QFormLayout::FieldRole, duree);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        titre = new QTextEdit(groupBox);
        titre->setObjectName(QStringLiteral("titre"));
        titre->setEnabled(false);

        formLayout->setWidget(4, QFormLayout::SpanningRole, titre);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        formLayout->setWidget(5, QFormLayout::LabelRole, pushButton_2);

        voir = new QPushButton(groupBox);
        voir->setObjectName(QStringLiteral("voir"));

        formLayout->setWidget(5, QFormLayout::FieldRole, voir);


        verticalLayout->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1139, 21));
        menuHello_World = new QMenu(menuBar);
        menuHello_World->setObjectName(QStringLiteral("menuHello_World"));
        menuProgrammer_une_Activit = new QMenu(menuHello_World);
        menuProgrammer_une_Activit->setObjectName(QStringLiteral("menuProgrammer_une_Activit"));
        menuGestion_des_Projets = new QMenu(menuBar);
        menuGestion_des_Projets->setObjectName(QStringLiteral("menuGestion_des_Projets"));
        menuCr_er_une_T_che = new QMenu(menuGestion_des_Projets);
        menuCr_er_une_T_che->setObjectName(QStringLiteral("menuCr_er_une_T_che"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHello_World->menuAction());
        menuBar->addAction(menuGestion_des_Projets->menuAction());
        menuHello_World->addAction(menuProgrammer_une_Activit->menuAction());
        menuHello_World->addAction(actionProgrammer_une_Tache);
        menuProgrammer_une_Activit->addAction(newActivity);
        menuProgrammer_une_Activit->addAction(actionProgrammer_une_Activit);
        menuGestion_des_Projets->addAction(actionVue_Globale);
        menuGestion_des_Projets->addAction(menuCr_er_une_T_che->menuAction());
        menuGestion_des_Projets->addAction(actionCr_er_un_Projet);
        menuCr_er_une_T_che->addAction(actionUnitaire);
        menuCr_er_une_T_che->addAction(actionComposite);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Project Calendar", 0));
        actionProgrammer_une_Tache->setText(QApplication::translate("MainWindow", "Programmation des Taches", 0));
        actionVue_Globale->setText(QApplication::translate("MainWindow", "Vue Globale", 0));
        actionCr_er_un_Projet->setText(QApplication::translate("MainWindow", "Cr\303\251er un Projet", 0));
        actionUnitaire->setText(QApplication::translate("MainWindow", "Unitaire", 0));
        actionComposite->setText(QApplication::translate("MainWindow", "Composite", 0));
        newActivity->setText(QApplication::translate("MainWindow", "Cr\303\251er une Activit\303\251", 0));
        actionProgrammer_une_Activit->setText(QApplication::translate("MainWindow", "Programmation des Activit\303\251s", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "LUNDI", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "MARDI", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "MERCREDI", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "JEUDI", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "VENDREDI", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "SAMEDI", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "DIMANCHE", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Ev\303\250nement", 0));
        label->setText(QApplication::translate("MainWindow", "Identificateur:", 0));
        identificateur->setText(QApplication::translate("MainWindow", "/", 0));
        label_3->setText(QApplication::translate("MainWindow", "Date:", 0));
        date->setText(QApplication::translate("MainWindow", "/", 0));
        label_4->setText(QApplication::translate("MainWindow", "Dur\303\251e", 0));
        duree->setText(QApplication::translate("MainWindow", "/", 0));
        label_2->setText(QApplication::translate("MainWindow", "Titre:", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Programmation", 0));
        voir->setText(QApplication::translate("MainWindow", "+ d'Informations", 0));
        menuHello_World->setTitle(QApplication::translate("MainWindow", "Gestion de l'Agenda", 0));
        menuProgrammer_une_Activit->setTitle(QApplication::translate("MainWindow", "Activit\303\251s", 0));
        menuGestion_des_Projets->setTitle(QApplication::translate("MainWindow", "Gestion des Projets", 0));
        menuCr_er_une_T_che->setTitle(QApplication::translate("MainWindow", "Cr\303\251er une Tache", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
