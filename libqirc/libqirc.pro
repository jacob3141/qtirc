
QT += network gui

TEMPLATE = lib
TARGET = qirc
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += staticlib

# Input
HEADERS += IRCClientImpl.h IRCClientInterface.h IRCCodes.h IRCWidget.h \
    IRCServerMessage.h \
    IRCChannelProxyInterface.h \
    IRCCommand.h \
    IRCReply.h \
    IRCError.h \
    IRCChannelProxyImpl.h
SOURCES += IRCClientImpl.cpp IRCWidget.cpp \
    IRCServerMessage.cpp \
    IRCChannelProxyImpl.cpp
