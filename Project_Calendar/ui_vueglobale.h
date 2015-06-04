/********************************************************************************
** Form generated from reading UI file 'vueglobale.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VUEGLOBALE_H
#define UI_VUEGLOBALE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_vueGlobale
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;

    void setupUi(QDialog *vueGlobale)
    {
        if (vueGlobale->objectName().isEmpty())
            vueGlobale->setObjectName(QStringLiteral("vueGlobale"));
        vueGlobale->resize(691, 481);
        verticalLayout = new QVBoxLayout(vueGlobale);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(vueGlobale);
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem5);
        __qtreewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem7);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem8);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setAutoExpandDelay(-1);
        treeWidget->setIndentation(40);
        treeWidget->setRootIsDecorated(true);
        treeWidget->setUniformRowHeights(false);
        treeWidget->setSortingEnabled(true);
        treeWidget->setAnimated(true);
        treeWidget->setAllColumnsShowFocus(false);
        treeWidget->header()->setCascadingSectionResizes(true);
        treeWidget->header()->setDefaultSectionSize(350);
        treeWidget->header()->setHighlightSections(true);

        verticalLayout->addWidget(treeWidget);


        retranslateUi(vueGlobale);

        QMetaObject::connectSlotsByName(vueGlobale);
    } // setupUi

    void retranslateUi(QDialog *vueGlobale)
    {
        vueGlobale->setWindowTitle(QApplication::translate("vueGlobale", "Vue Globale", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("vueGlobale", "Dur\303\251e", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("vueGlobale", "Programmation", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("vueGlobale", "Identificateur", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("vueGlobale", "Projets", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("vueGlobale", "NA17", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("vueGlobale", "LO21", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("vueGlobale", "Taches Unitaires", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem3->child(0);
        ___qtreewidgetitem4->setText(0, QApplication::translate("vueGlobale", "Programm\303\251es", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(3, QApplication::translate("vueGlobale", "00:20", 0));
        ___qtreewidgetitem5->setText(2, QApplication::translate("vueGlobale", "10/06/2015 10:00", 0));
        ___qtreewidgetitem5->setText(1, QApplication::translate("vueGlobale", "Rendu Projet", 0));
        ___qtreewidgetitem5->setText(0, QApplication::translate("vueGlobale", "Tache Unitaire 1", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("vueGlobale", "Predecesseurs", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(1, QApplication::translate("vueGlobale", "Connexion au GUI", 0));
        ___qtreewidgetitem7->setText(0, QApplication::translate("vueGlobale", "Tache Unitaire 2", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem3->child(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("vueGlobale", "Non-Programm\303\251es", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(2, QApplication::translate("vueGlobale", "Pr\303\251-emptive", 0));
        ___qtreewidgetitem9->setText(1, QApplication::translate("vueGlobale", "Connexion au GUI", 0));
        ___qtreewidgetitem9->setText(0, QApplication::translate("vueGlobale", "Tache Unitaire 2", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QApplication::translate("vueGlobale", "Predecesseurs", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem9->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("vueGlobale", "1\303\250re Programmation", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem12->setText(0, QApplication::translate("vueGlobale", "Taches Composites", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(1, QApplication::translate("vueGlobale", "Project Calendar", 0));
        ___qtreewidgetitem13->setText(0, QApplication::translate("vueGlobale", "TC1", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(0, QApplication::translate("vueGlobale", "Taches composantes", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem14->child(0);
        ___qtreewidgetitem15->setText(1, QApplication::translate("vueGlobale", "Connexion au GUI", 0));
        ___qtreewidgetitem15->setText(0, QApplication::translate("vueGlobale", "Tache Unitaire 2", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem14->child(1);
        ___qtreewidgetitem16->setText(3, QApplication::translate("vueGlobale", "00:20", 0));
        ___qtreewidgetitem16->setText(2, QApplication::translate("vueGlobale", "10/06/2015 10:00", 0));
        ___qtreewidgetitem16->setText(1, QApplication::translate("vueGlobale", "Rendu Projet", 0));
        ___qtreewidgetitem16->setText(0, QApplication::translate("vueGlobale", "Tache Unitaire 1", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem13->child(1);
        ___qtreewidgetitem17->setText(0, QApplication::translate("vueGlobale", "Predecesseurs", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class vueGlobale: public Ui_vueGlobale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VUEGLOBALE_H
