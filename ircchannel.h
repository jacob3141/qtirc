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
class IRCClient;

// Qt includes
#include <QObject>
#include <QVector>
#include <QColor>
#include <QTextDocument>
#include <QStringListModel>

/**
  * \class IRCChannel
  * Implements a handle to an IRC channel. This is usually provided by the
  * the IRC client class.
  */
class IRCChannel :
        public QObject {
    Q_OBJECT
public:
    IRCChannel(IRCClient *ircClient,
                        QString channelName,
                        QObject *parent = 0);
    QTextDocument *conversationModel();
    QStringListModel *userListModel();
    QString channelName();

public slots:
    void nameReply(const QStringList &nickList);
    void sendMessage(const QString& message);
    void sendJoinRequest();
    void leave(const QString &reason);

    void handleMessage(const QString &nick, const QString &message);
    void handleNickChange(const QString& oldNick, const QString& newNick);
    void handleJoin(const QString& nick);

private:
    void processUserList();
    void rebuildColorTable();

    QString             m_channelName;
    QStringList         m_userList;
    QStringListModel    m_userListModel;
    QTextDocument       m_conversationModel;
    IRCClient      *m_ircClient;
    QVector<QColor>     m_colorTable;
};
