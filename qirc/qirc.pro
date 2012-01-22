QT       += core gui network

TARGET = qirc
TEMPLATE = app

INCLUDEPATH += ../libqirc

LIBS += -L../libqirc -lqirc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
