/* QtIRC - Qt based IRC client
 * Copyright (C) 2012-2015 Jacob Dawid (jacob@omg-it.works)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Own includes
#include "ircclient.h"
#include "ircserverwidget.h"
#include "chatmessagetextedit.h"

// Qt includes
#include <QWidget>
#include <QSet>
#include <QSplitter>
#include <QTabWidget>
#include <QPushButton>

class IRCWidget : public QWidget {
    Q_OBJECT

public:
    explicit IRCWidget(QWidget *parent = 0);
    ~IRCWidget();

    void connectToServer(QString nick,
                         QString url,
                         quint16 port = 6667,
                         QString autoJoinChannel = QString());

    void joinChannel(QString channel);

public slots:
    void showChangeUserNickPopup();
    void sendMessage(QString message);
    void handleConnected(QString server);

signals:
    void connected();

private:
    QSplitter *             _splitter;
    QTabWidget *            _tabWidget;
    QPushButton *           _pushButtonNick;
    IRCClient *             _ircClient;
    IRCServerWidget *       _ircServerWidget;
    ChatMessageTextEdit *   _chatMessageTextEdit;
    QSet<IRCChannel*>       _channels;
    QString                 _autoJoinChannel;
};
