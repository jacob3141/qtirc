QT += network gui widgets

TEMPLATE = lib

CONFIG += staticlib

HEADERS += \
    chatmessagetextedit.h \
    ircchannelproxyinterface.h \
    ircchannelview.h \
    ircclientimpl.h \
    ircclientinterface.h \
    irccodes.h \
    irccommand.h \
    ircerror.h \
    ircreply.h \
    ircservermessage.h \
    ircserverview.h \
    ircwidget.h \
    ircchannelproxyimpl.h

SOURCES += \
    chatmessagetextedit.cpp \
    ircchannelproxyimpl.cpp \
    ircchannelview.cpp \
    ircclientimpl.cpp \
    ircservermessage.cpp \
    ircserverview.cpp \
    ircwidget.cpp

FORMS += \
    ircchannelview.ui \
    ircserverview.ui \
    ircwidget.ui
