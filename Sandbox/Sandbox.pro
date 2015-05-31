#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T09:17:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sandbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ajouteractivite.cpp \
    fonctions.cpp \
    tacheediteur.cpp \
    calendar.cpp \
    programmationtache.cpp \
    ajouterprojet.cpp \
    ajoutertachecomposite.cpp \
    programmationactivite.cpp

HEADERS  += mainwindow.h \
    ajouteractivite.h \
    fonctions.h \
    tacheediteur.h \
    calendar.h \
    programmationtache.h \
    ajouterprojet.h \
    ajoutertachecomposite.h \
    programmationactivite.h

FORMS    += mainwindow.ui \
    ajouteractivite.ui \
    programmationtache.ui \
    ajouterprojet.ui \
    ajoutertachecomposite.ui \
    programmationactivite.ui
