/********************************************************************************
** Form generated from reading UI file 'ajouterprojet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTERPROJET_H
#define UI_AJOUTERPROJET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ajouterProjet
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *identificateur;
    QLabel *label_2;
    QPlainTextEdit *titre;
    QLabel *label_3;
    QPushButton *annuler;
    QPushButton *pushButton;
    QDateTimeEdit *dispo;

    void setupUi(QWidget *ajouterProjet)
    {
        if (ajouterProjet->objectName().isEmpty())
            ajouterProjet->setObjectName(QStringLiteral("ajouterProjet"));
        ajouterProjet->resize(493, 275);
        formLayout = new QFormLayout(ajouterProjet);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(ajouterProjet);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        identificateur = new QLineEdit(ajouterProjet);
        identificateur->setObjectName(QStringLiteral("identificateur"));

        formLayout->setWidget(0, QFormLayout::FieldRole, identificateur);

        label_2 = new QLabel(ajouterProjet);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        titre = new QPlainTextEdit(ajouterProjet);
        titre->setObjectName(QStringLiteral("titre"));
        titre->setMinimumSize(QSize(0, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, titre);

        label_3 = new QLabel(ajouterProjet);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        annuler = new QPushButton(ajouterProjet);
        annuler->setObjectName(QStringLiteral("annuler"));

        formLayout->setWidget(3, QFormLayout::LabelRole, annuler);

        pushButton = new QPushButton(ajouterProjet);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(3, QFormLayout::FieldRole, pushButton);

        dispo = new QDateTimeEdit(ajouterProjet);
        dispo->setObjectName(QStringLiteral("dispo"));
        dispo->setCalendarPopup(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, dispo);


        retranslateUi(ajouterProjet);

        QMetaObject::connectSlotsByName(ajouterProjet);
    } // setupUi

    void retranslateUi(QWidget *ajouterProjet)
    {
        ajouterProjet->setWindowTitle(QApplication::translate("ajouterProjet", "Cr\303\251ation d'un Projet", 0));
        label->setText(QApplication::translate("ajouterProjet", "Identificateur:", 0));
        label_2->setText(QApplication::translate("ajouterProjet", "Titre:", 0));
        label_3->setText(QApplication::translate("ajouterProjet", "Date de disponibilit\303\251", 0));
        annuler->setText(QApplication::translate("ajouterProjet", "Annuler", 0));
        pushButton->setText(QApplication::translate("ajouterProjet", "Cr\303\251er !", 0));
    } // retranslateUi

};

namespace Ui {
    class ajouterProjet: public Ui_ajouterProjet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTERPROJET_H
