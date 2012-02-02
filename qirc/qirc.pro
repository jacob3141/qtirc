QT       += core gui network

TARGET = qirc
TEMPLATE = app

INCLUDEPATH += ../libqirc

win32-msvc*: include(../msvc.pri)
LIBS += -L../libqirc/$$LIBDIR_SUFFIX -lqirc

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
