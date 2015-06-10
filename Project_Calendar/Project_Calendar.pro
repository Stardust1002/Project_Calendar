#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T09:17:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_Calendar
TEMPLATE = app


SOURCES += main.cpp\
    GUI/mainwindow.cpp \
    GUI/ajouteractivite.cpp \
    GUI/fonctions.cpp \
    GUI/tacheediteur.cpp \
    GUI/programmationtache.cpp \
    GUI/ajouterprojet.cpp \
    GUI/ajoutertachecomposite.cpp \
    GUI/programmationactivite.cpp \
    GUI/vueglobale.cpp \
    evenement.cpp \
    manager.cpp \
    qtimespan.cpp \
    import-export.cpp \
    GUI/ouvrirsave.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/ajouteractivite.h \
    GUI/fonctions.h \
    GUI/tacheediteur.h \
    GUI/programmationtache.h \
    GUI/ajouterprojet.h \
    GUI/ajoutertachecomposite.h \
    GUI/programmationactivite.h \
    GUI/vueglobale.h \
    evenement.h \
    manager.h \
    qtimespan.h \
    import-export.h \
    GUI/ouvrirsave.h

FORMS    += GUI/mainwindow.ui \
    GUI/ajouteractivite.ui \
    GUI/programmationtache.ui \
    GUI/ajouterprojet.ui \
    GUI/ajoutertachecomposite.ui \
    GUI/programmationactivite.ui \
    GUI/vueglobale.ui \
    GUI/ouvrirsave.ui
