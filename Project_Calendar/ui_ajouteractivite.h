/********************************************************************************
** Form generated from reading UI file 'ajouteractivite.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTERACTIVITE_H
#define UI_AJOUTERACTIVITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ajouterActivite
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *identificateur;
    QLabel *label_2;
    QPlainTextEdit *titre;
    QLabel *label_4;
    QComboBox *type;
    QLabel *label_3;
    QTimeEdit *duree;
    QPushButton *annuler;
    QPushButton *pushButton;

    void setupUi(QWidget *ajouterActivite)
    {
        if (ajouterActivite->objectName().isEmpty())
            ajouterActivite->setObjectName(QStringLiteral("ajouterActivite"));
        ajouterActivite->resize(516, 334);
        horizontalLayout = new QHBoxLayout(ajouterActivite);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(ajouterActivite);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        identificateur = new QLineEdit(groupBox);
        identificateur->setObjectName(QStringLiteral("identificateur"));

        formLayout->setWidget(0, QFormLayout::FieldRole, identificateur);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        titre = new QPlainTextEdit(groupBox);
        titre->setObjectName(QStringLiteral("titre"));
        titre->setMinimumSize(QSize(0, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, titre);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        type = new QComboBox(groupBox);
        type->setObjectName(QStringLiteral("type"));

        formLayout->setWidget(2, QFormLayout::FieldRole, type);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        duree = new QTimeEdit(groupBox);
        duree->setObjectName(QStringLiteral("duree"));
        duree->setProperty("showGroupSeparator", QVariant(false));
        duree->setCalendarPopup(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, duree);

        annuler = new QPushButton(groupBox);
        annuler->setObjectName(QStringLiteral("annuler"));

        formLayout->setWidget(4, QFormLayout::LabelRole, annuler);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(ajouterActivite);

        QMetaObject::connectSlotsByName(ajouterActivite);
    } // setupUi

    void retranslateUi(QWidget *ajouterActivite)
    {
        ajouterActivite->setWindowTitle(QApplication::translate("ajouterActivite", "Cr\303\251ation d'une Activit\303\251", 0));
        groupBox->setTitle(QApplication::translate("ajouterActivite", "Cr\303\251ation d'une Activit\303\251", 0));
        label->setText(QApplication::translate("ajouterActivite", "Identificateur:", 0));
        label_2->setText(QApplication::translate("ajouterActivite", "Titre:", 0));
        label_4->setText(QApplication::translate("ajouterActivite", "Type:", 0));
        type->clear();
        type->insertItems(0, QStringList()
         << QApplication::translate("ajouterActivite", "RDV", 0)
         << QApplication::translate("ajouterActivite", "R\303\251union", 0)
        );
        label_3->setText(QApplication::translate("ajouterActivite", "Dur\303\251e:", 0));
        annuler->setText(QApplication::translate("ajouterActivite", "Annuler", 0));
        pushButton->setText(QApplication::translate("ajouterActivite", "Cr\303\251er !", 0));
    } // retranslateUi

};

namespace Ui {
    class ajouterActivite: public Ui_ajouterActivite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTERACTIVITE_H
