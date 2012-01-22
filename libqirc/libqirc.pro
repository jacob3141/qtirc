
QT += network gui

TEMPLATE = lib
TARGET = qirc
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += staticlib

# Input
HEADERS += IRCClientImpl.h IRCClientInterface.h IRCCodes.h IRCWidget.h
SOURCES += IRCClientImpl.cpp IRCWidget.cpp
