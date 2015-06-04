/********************************************************************************
** Form generated from reading UI file 'programmationtache.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMMATIONTACHE_H
#define UI_PROGRAMMATIONTACHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_programmationTache
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout;
    QLabel *label_projj;
    QComboBox *projet;
    QLabel *label_8;
    QComboBox *statut;
    QLabel *label;
    QComboBox *tache;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QDateTimeEdit *dispo;
    QLabel *label_3;
    QDateTimeEdit *echeance;
    QLabel *label_4;
    QLabel *label_duree;
    QLabel *label_11;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_4;
    QLabel *label_7;
    QLabel *pred;
    QLabel *label_6;
    QLabel *identificateur;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLabel *label_duree_2;
    QLabel *label_12;
    QComboBox *comboBox;
    QLabel *label_10;
    QTimeEdit *duree;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QDateTimeEdit *programmation;
    QHBoxLayout *horizontalLayout;
    QPushButton *annuler;
    QPushButton *deprog;
    QPushButton *programmer;

    void setupUi(QWidget *programmationTache)
    {
        if (programmationTache->objectName().isEmpty())
            programmationTache->setObjectName(QStringLiteral("programmationTache"));
        programmationTache->resize(516, 464);
        gridLayout_4 = new QGridLayout(programmationTache);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_projj = new QLabel(programmationTache);
        label_projj->setObjectName(QStringLiteral("label_projj"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_projj);

        projet = new QComboBox(programmationTache);
        projet->setObjectName(QStringLiteral("projet"));

        formLayout->setWidget(0, QFormLayout::FieldRole, projet);

        label_8 = new QLabel(programmationTache);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_8);

        statut = new QComboBox(programmationTache);
        statut->setObjectName(QStringLiteral("statut"));

        formLayout->setWidget(1, QFormLayout::FieldRole, statut);

        label = new QLabel(programmationTache);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        tache = new QComboBox(programmationTache);
        tache->setObjectName(QStringLiteral("tache"));

        formLayout->setWidget(2, QFormLayout::FieldRole, tache);


        gridLayout_3->addLayout(formLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(programmationTache);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 1000000));
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        dispo = new QDateTimeEdit(groupBox);
        dispo->setObjectName(QStringLiteral("dispo"));
        dispo->setMinimumSize(QSize(0, 18));
        dispo->setReadOnly(true);
        dispo->setProperty("showGroupSeparator", QVariant(false));

        gridLayout->addWidget(dispo, 0, 1, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        echeance = new QDateTimeEdit(groupBox);
        echeance->setObjectName(QStringLiteral("echeance"));
        echeance->setMinimumSize(QSize(0, 18));
        echeance->setReadOnly(true);

        gridLayout->addWidget(echeance, 1, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_duree = new QLabel(groupBox);
        label_duree->setObjectName(QStringLiteral("label_duree"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_duree->setFont(font);

        gridLayout->addWidget(label_duree, 2, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 2, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(programmationTache);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        formLayout_4 = new QFormLayout(groupBox_3);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_7);

        pred = new QLabel(groupBox_3);
        pred->setObjectName(QStringLiteral("pred"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, pred);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_6);

        identificateur = new QLabel(groupBox_3);
        identificateur->setObjectName(QStringLiteral("identificateur"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, identificateur);


        gridLayout_3->addWidget(groupBox_3, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(programmationTache);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 2);

        label_duree_2 = new QLabel(groupBox_2);
        label_duree_2->setObjectName(QStringLiteral("label_duree_2"));
        label_duree_2->setFont(font);

        gridLayout_2->addWidget(label_duree_2, 0, 2, 1, 2);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 0, 4, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 1, 1, 1, 2);

        duree = new QTimeEdit(groupBox_2);
        duree->setObjectName(QStringLiteral("duree"));

        gridLayout_2->addWidget(duree, 1, 3, 1, 2);


        gridLayout_3->addWidget(groupBox_2, 3, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_5 = new QLabel(programmationTache);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        programmation = new QDateTimeEdit(programmationTache);
        programmation->setObjectName(QStringLiteral("programmation"));
        programmation->setCalendarPopup(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, programmation);


        gridLayout_3->addLayout(formLayout_2, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        annuler = new QPushButton(programmationTache);
        annuler->setObjectName(QStringLiteral("annuler"));

        horizontalLayout->addWidget(annuler);

        deprog = new QPushButton(programmationTache);
        deprog->setObjectName(QStringLiteral("deprog"));

        horizontalLayout->addWidget(deprog);

        programmer = new QPushButton(programmationTache);
        programmer->setObjectName(QStringLiteral("programmer"));

        horizontalLayout->addWidget(programmer);


        gridLayout_3->addLayout(horizontalLayout, 5, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(programmationTache);

        QMetaObject::connectSlotsByName(programmationTache);
    } // setupUi

    void retranslateUi(QWidget *programmationTache)
    {
        programmationTache->setWindowTitle(QApplication::translate("programmationTache", "Form", 0));
        label_projj->setText(QApplication::translate("programmationTache", "Projet:", 0));
        label_8->setText(QApplication::translate("programmationTache", "Statut de la tache:", 0));
        statut->clear();
        statut->insertItems(0, QStringList()
         << QApplication::translate("programmationTache", "Non-Programm\303\251e", 0)
         << QApplication::translate("programmationTache", "Programm\303\251e", 0)
         << QApplication::translate("programmationTache", "Pr\303\251emptive incompl\303\250te", 0)
        );
        label->setText(QApplication::translate("programmationTache", "Tache:", 0));
        groupBox->setTitle(QApplication::translate("programmationTache", "Tache choisie:", 0));
        label_2->setText(QApplication::translate("programmationTache", "Date de Disponibilit\303\251:", 0));
        label_3->setText(QApplication::translate("programmationTache", "Date d'Ech\303\251ance:", 0));
        label_4->setText(QApplication::translate("programmationTache", "Dur\303\251e:", 0));
        label_duree->setText(QApplication::translate("programmationTache", "dur\303\251e", 0));
        label_11->setText(QApplication::translate("programmationTache", "heures.", 0));
        groupBox_3->setTitle(QApplication::translate("programmationTache", "Predecesseur Direct:", 0));
        label_7->setText(QApplication::translate("programmationTache", "Programmation:", 0));
        pred->setText(QApplication::translate("programmationTache", "dispo", 0));
        label_6->setText(QApplication::translate("programmationTache", "Identificateur:", 0));
        identificateur->setText(QApplication::translate("programmationTache", "id", 0));
        groupBox_2->setTitle(QApplication::translate("programmationTache", "Attention, cette tache est pr\303\251emptive !", 0));
        label_9->setText(QApplication::translate("programmationTache", "Cette tache est pr\303\251emptive, il reste", 0));
        label_duree_2->setText(QApplication::translate("programmationTache", "3:00", 0));
        label_12->setText(QApplication::translate("programmationTache", "heures \303\240 programmer.", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("programmationTache", "Nouvelle Programmation", 0)
         << QApplication::translate("programmationTache", "Programmation n\302\2602", 0)
         << QApplication::translate("programmationTache", "Programmation n\302\2601", 0)
        );
        label_10->setText(QApplication::translate("programmationTache", "Dur\303\251e:", 0));
        label_5->setText(QApplication::translate("programmationTache", "Date de la Programmation:", 0));
        annuler->setText(QApplication::translate("programmationTache", "Annuler", 0));
        deprog->setText(QApplication::translate("programmationTache", "D\303\251programmer", 0));
        programmer->setText(QApplication::translate("programmationTache", "Programmer !", 0));
    } // retranslateUi

};

namespace Ui {
    class programmationTache: public Ui_programmationTache {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMMATIONTACHE_H
