/********************************************************************************
** Form generated from reading UI file 'ajoutertachecomposite.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTERTACHECOMPOSITE_H
#define UI_AJOUTERTACHECOMPOSITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ajouterTacheComposite
{
public:
    QGridLayout *gridLayout;
    QFrame *line;
    QLabel *label_9;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *annuler;
    QListWidget *composants;
    QPushButton *pushButton;
    QComboBox *projet;
    QLineEdit *identificateur;
    QTextEdit *titre;
    QDateTimeEdit *dispo;
    QLabel *labelech;
    QLabel *label_6;
    QDateTimeEdit *echeance;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_10;
    QListWidget *liste_taches_projet;
    QListWidget *liste;
    QListWidget *pred;
    QLabel *label_4;
    QLabel *label_8;

    void setupUi(QDialog *ajouterTacheComposite)
    {
        if (ajouterTacheComposite->objectName().isEmpty())
            ajouterTacheComposite->setObjectName(QStringLiteral("ajouterTacheComposite"));
        ajouterTacheComposite->resize(703, 550);
        gridLayout = new QGridLayout(ajouterTacheComposite);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        line = new QFrame(ajouterTacheComposite);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 6, 0, 1, 5);

        label_9 = new QLabel(ajouterTacheComposite);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 7, 4, 1, 1);

        label = new QLabel(ajouterTacheComposite);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(ajouterTacheComposite);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(ajouterTacheComposite);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        annuler = new QPushButton(ajouterTacheComposite);
        annuler->setObjectName(QStringLiteral("annuler"));

        gridLayout->addWidget(annuler, 9, 0, 1, 2);

        composants = new QListWidget(ajouterTacheComposite);
        composants->setObjectName(QStringLiteral("composants"));
        composants->setEditTriggers(QAbstractItemView::NoEditTriggers);
        composants->setDragEnabled(true);
        composants->setDragDropOverwriteMode(true);
        composants->setDragDropMode(QAbstractItemView::DragDrop);
        composants->setDefaultDropAction(Qt::MoveAction);
        composants->setAlternatingRowColors(true);

        gridLayout->addWidget(composants, 8, 0, 1, 3);

        pushButton = new QPushButton(ajouterTacheComposite);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 9, 2, 1, 3);

        projet = new QComboBox(ajouterTacheComposite);
        projet->setObjectName(QStringLiteral("projet"));

        gridLayout->addWidget(projet, 0, 4, 1, 1);

        identificateur = new QLineEdit(ajouterTacheComposite);
        identificateur->setObjectName(QStringLiteral("identificateur"));

        gridLayout->addWidget(identificateur, 0, 1, 1, 2);

        titre = new QTextEdit(ajouterTacheComposite);
        titre->setObjectName(QStringLiteral("titre"));
        titre->setMaximumSize(QSize(16777215, 150));
        titre->setAutoFillBackground(false);

        gridLayout->addWidget(titre, 1, 1, 1, 4);

        dispo = new QDateTimeEdit(ajouterTacheComposite);
        dispo->setObjectName(QStringLiteral("dispo"));
        dispo->setCalendarPopup(true);

        gridLayout->addWidget(dispo, 2, 1, 1, 2);

        labelech = new QLabel(ajouterTacheComposite);
        labelech->setObjectName(QStringLiteral("labelech"));

        gridLayout->addWidget(labelech, 2, 3, 1, 1);

        label_6 = new QLabel(ajouterTacheComposite);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        echeance = new QDateTimeEdit(ajouterTacheComposite);
        echeance->setObjectName(QStringLiteral("echeance"));
        echeance->setCalendarPopup(true);

        gridLayout->addWidget(echeance, 2, 4, 1, 1);

        label_5 = new QLabel(ajouterTacheComposite);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        label_7 = new QLabel(ajouterTacheComposite);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 2);

        label_10 = new QLabel(ajouterTacheComposite);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 7, 2, 1, 2);

        liste_taches_projet = new QListWidget(ajouterTacheComposite);
        liste_taches_projet->setObjectName(QStringLiteral("liste_taches_projet"));
        liste_taches_projet->setEditTriggers(QAbstractItemView::NoEditTriggers);
        liste_taches_projet->setDragEnabled(true);
        liste_taches_projet->setDragDropOverwriteMode(true);
        liste_taches_projet->setDragDropMode(QAbstractItemView::DragDrop);
        liste_taches_projet->setDefaultDropAction(Qt::MoveAction);
        liste_taches_projet->setAlternatingRowColors(true);

        gridLayout->addWidget(liste_taches_projet, 8, 3, 1, 2);

        liste = new QListWidget(ajouterTacheComposite);
        liste->setObjectName(QStringLiteral("liste"));
        liste->setEditTriggers(QAbstractItemView::NoEditTriggers);
        liste->setDragEnabled(true);
        liste->setDragDropOverwriteMode(true);
        liste->setDragDropMode(QAbstractItemView::DragDrop);
        liste->setDefaultDropAction(Qt::MoveAction);
        liste->setAlternatingRowColors(true);
        liste->setSortingEnabled(true);

        gridLayout->addWidget(liste, 5, 3, 1, 2);

        pred = new QListWidget(ajouterTacheComposite);
        pred->setObjectName(QStringLiteral("pred"));
        pred->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pred->setDragEnabled(true);
        pred->setDragDropOverwriteMode(true);
        pred->setDragDropMode(QAbstractItemView::DragDrop);
        pred->setDefaultDropAction(Qt::MoveAction);
        pred->setAlternatingRowColors(true);

        gridLayout->addWidget(pred, 5, 0, 1, 3);

        label_4 = new QLabel(ajouterTacheComposite);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 4, 1, 1);

        label_8 = new QLabel(ajouterTacheComposite);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 2, 1, 2);


        retranslateUi(ajouterTacheComposite);

        QMetaObject::connectSlotsByName(ajouterTacheComposite);
    } // setupUi

    void retranslateUi(QDialog *ajouterTacheComposite)
    {
        ajouterTacheComposite->setWindowTitle(QApplication::translate("ajouterTacheComposite", "Dialog", 0));
        label_9->setText(QApplication::translate("ajouterTacheComposite", "Taches du Projet", 0));
        label->setText(QApplication::translate("ajouterTacheComposite", "Identificateur:", 0));
        label_2->setText(QApplication::translate("ajouterTacheComposite", "Titre:", 0));
        label_3->setText(QApplication::translate("ajouterTacheComposite", "Date de disponibilit\303\251:", 0));
        annuler->setText(QApplication::translate("ajouterTacheComposite", "Annuler", 0));
        pushButton->setText(QApplication::translate("ajouterTacheComposite", "Cr\303\251er !", 0));
        projet->clear();
        projet->insertItems(0, QStringList()
         << QApplication::translate("ajouterTacheComposite", "LO21", 0)
        );
        labelech->setText(QApplication::translate("ajouterTacheComposite", "Date d'\303\251ch\303\251ance:", 0));
        label_6->setText(QApplication::translate("ajouterTacheComposite", "Projet:", 0));
        label_5->setText(QApplication::translate("ajouterTacheComposite", "Taches composantes", 0));
        label_7->setText(QApplication::translate("ajouterTacheComposite", "Pr\303\251d\303\251cesseurs", 0));
        label_10->setText(QApplication::translate("ajouterTacheComposite", "<--------------------------------------------------", 0));
        label_4->setText(QApplication::translate("ajouterTacheComposite", " Liste de toutes les taches ", 0));
        label_8->setText(QApplication::translate("ajouterTacheComposite", "<-------------------------------------------------", 0));
    } // retranslateUi

};

namespace Ui {
    class ajouterTacheComposite: public Ui_ajouterTacheComposite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTERTACHECOMPOSITE_H
