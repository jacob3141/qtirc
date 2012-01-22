#-------------------------------------------------
#
# Project created by QtCreator 2012-01-22T20:00:09
#
#-------------------------------------------------

QT       += core gui

TARGET = qirc
TEMPLATE = app

INCLUDEPATH += ../libqirc

LIBS += -L../libqirc -lqirc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
