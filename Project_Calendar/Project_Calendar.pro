#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T21:54:10
#
#-------------------------------------------------

QT += widgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_Calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    manager.cpp \
    timing.cpp \
    evenement.cpp

HEADERS  += mainwindow.h \
    manager.h \
    evenement.h \
    timing.h

FORMS    += mainwindow.ui
