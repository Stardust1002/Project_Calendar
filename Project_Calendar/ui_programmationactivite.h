/********************************************************************************
** Form generated from reading UI file 'programmationactivite.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMMATIONACTIVITE_H
#define UI_PROGRAMMATIONACTIVITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_programmationActivite
{
public:
    QGroupBox *groupBox;
    QFormLayout *formLayout_3;
    QLabel *label_2;
    QComboBox *type;
    QLabel *label_3;
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_projj;
    QComboBox *statut;
    QComboBox *activite;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QDateTimeEdit *programmation;
    QPushButton *annuler;
    QPushButton *deprogrammer;
    QPushButton *programmer;

    void setupUi(QDialog *programmationActivite)
    {
        if (programmationActivite->objectName().isEmpty())
            programmationActivite->setObjectName(QStringLiteral("programmationActivite"));
        programmationActivite->resize(426, 309);
        groupBox = new QGroupBox(programmationActivite);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(9, 43, 408, 200));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 200));
        groupBox->setFlat(false);
        formLayout_3 = new QFormLayout(groupBox);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_2);

        type = new QComboBox(groupBox);
        type->setObjectName(QStringLiteral("type"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, type);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_3);

        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(0, 100));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, textEdit);

        widget = new QWidget(programmationActivite);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 401, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_projj = new QLabel(widget);
        label_projj->setObjectName(QStringLiteral("label_projj"));

        horizontalLayout->addWidget(label_projj);

        statut = new QComboBox(widget);
        statut->setObjectName(QStringLiteral("statut"));

        horizontalLayout->addWidget(statut);

        activite = new QComboBox(widget);
        activite->setObjectName(QStringLiteral("activite"));

        horizontalLayout->addWidget(activite);

        widget1 = new QWidget(programmationActivite);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 250, 401, 51));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        programmation = new QDateTimeEdit(widget1);
        programmation->setObjectName(QStringLiteral("programmation"));
        programmation->setCalendarPopup(true);

        gridLayout->addWidget(programmation, 0, 1, 1, 2);

        annuler = new QPushButton(widget1);
        annuler->setObjectName(QStringLiteral("annuler"));

        gridLayout->addWidget(annuler, 1, 0, 1, 1);

        deprogrammer = new QPushButton(widget1);
        deprogrammer->setObjectName(QStringLiteral("deprogrammer"));

        gridLayout->addWidget(deprogrammer, 1, 1, 1, 1);

        programmer = new QPushButton(widget1);
        programmer->setObjectName(QStringLiteral("programmer"));

        gridLayout->addWidget(programmer, 1, 2, 1, 1);


        retranslateUi(programmationActivite);

        QMetaObject::connectSlotsByName(programmationActivite);
    } // setupUi

    void retranslateUi(QDialog *programmationActivite)
    {
        programmationActivite->setWindowTitle(QApplication::translate("programmationActivite", "Programmation d'une Activit\303\251", 0));
        groupBox->setTitle(QApplication::translate("programmationActivite", "Activit\303\251 choisie:", 0));
        label_2->setText(QApplication::translate("programmationActivite", "Type:", 0));
        type->clear();
        type->insertItems(0, QStringList()
         << QApplication::translate("programmationActivite", "RDV", 0)
         << QApplication::translate("programmationActivite", "R\303\251union", 0)
        );
        label_3->setText(QApplication::translate("programmationActivite", "Titre:", 0));
        label_projj->setText(QApplication::translate("programmationActivite", "Activit\303\251", 0));
        statut->clear();
        statut->insertItems(0, QStringList()
         << QApplication::translate("programmationActivite", "Non-Programm\303\251e", 0)
         << QApplication::translate("programmationActivite", "Programm\303\251e", 0)
        );
        activite->clear();
        activite->insertItems(0, QStringList()
         << QApplication::translate("programmationActivite", "Entretien Anglais", 0)
        );
        label_5->setText(QApplication::translate("programmationActivite", "Date de la Programmation:", 0));
        annuler->setText(QApplication::translate("programmationActivite", "Annuler", 0));
        deprogrammer->setText(QApplication::translate("programmationActivite", "D\303\251programmer", 0));
        programmer->setText(QApplication::translate("programmationActivite", "Programmer !", 0));
    } // retranslateUi

};

namespace Ui {
    class programmationActivite: public Ui_programmationActivite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMMATIONACTIVITE_H
