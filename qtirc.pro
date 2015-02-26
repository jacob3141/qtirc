QT += network gui widgets

TEMPLATE = lib

CONFIG += staticlib

HEADERS += \
    chatmessagetextedit.h \
    irccodes.h \
    irccommand.h \
    ircerror.h \
    ircreply.h \
    ircservermessage.h \
    ircwidget.h \
    ircchannel.h \
    ircclient.h \
    ircchannelwidget.h \
    ircserverwidget.h

SOURCES += \
    chatmessagetextedit.cpp \
    ircservermessage.cpp \
    ircwidget.cpp \
    ircchannel.cpp \
    ircclient.cpp \
    ircchannelwidget.cpp \
    ircserverwidget.cpp

FORMS += \
    ircchannelwidget.ui \
    ircserverwidget.ui
