
QT += network gui

TEMPLATE = lib
TARGET = qirc
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += staticlib

# Input
HEADERS += IRCClientImpl.h IRCClientInterface.h IRCCodes.h \
    IRCServerMessage.h \
    IRCChannelProxyInterface.h \
    IRCCommand.h \
    IRCReply.h \
    IRCError.h \
    IRCChannelProxyImpl.h \
    ChatMessageTextEdit.h \
    QIRCWidget.h \
    IRCChannelView.h \
    IRCServerView.h
SOURCES += IRCClientImpl.cpp \
    IRCServerMessage.cpp \
    IRCChannelProxyImpl.cpp \
    ChatMessageTextEdit.cpp \
    QIRCWidget.cpp \
    IRCChannelView.cpp \
    IRCServerView.cpp

FORMS += \
    QIRCWidget.ui \
    IRCChannelView.ui \
    IRCServerView.ui
