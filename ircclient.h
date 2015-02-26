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
#include "ircservermessage.h"
#include "irccommand.h"
#include "ircreply.h"
#include "ircerror.h"
#include "ircchannel.h"

// Qt includes
#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QStringList>
#include <QTextDocument>
#include <QStringListModel>

/**
  * \class IRCClient
  * Implements an IRC client. This class can maintain a connection to one server.
  * In order to interface an IRC channel, use the ircChannelProxy-method to retrieve
  * a handle.
  */
class IRCClient :
    public QObject {
    Q_OBJECT
public:
    IRCClient(QObject *parent = 0);
    ~IRCClient();

    const QString& nickname ();
    bool isConnected ();
    bool isLoggedIn ();
    const QHostAddress& host();
    int port();
    IRCChannel *ircChannel(const QString& channel);
    void sendIRCCommand (const QString& command, const QStringList& arguments);

public slots:
    void connectToHost (const QHostAddress& host, quint16 port, const QString& initialNick);
    void disconnect ();
    void reconnect ();

    void sendNicknameChangeRequest (const QString &nickname);
    void sendPrivateMessage (const QString &recipient, const QString &message);

signals:
    /**
    * Sent upon the arrival of a new message.
    * \arg channel The channel this message was sent from.
    * \arg sender The nickname of the sender.
    * \arg message The message that has been sent.
    */
    void message (const QString& channel, const QString& sender, const QString& message);

    /**
    * Sent when the connection to a server has been established.
    * \arg server The name of the server that the connection has been established to.
    */
    void connected (const QString& server);

    /** Sent when the connection to the server has been interrupted. */
    void disconnected ();

    /**
    * Sent when an error occurs.
    * \arg message A descriptive message of the error that occured.
    */
    void error (const QString& message);

    /**
    * Sent when a notification arrives.
    * \arg sender The source of the notification.
    * \arg message The notification.
    */
    void notification (const QString& sender, const QString& message);

    /**
    * Sent when a nickname changed.
    * \arg oldNick The previous nickname.
    * \arg newNick The new nickname.
    */
    void nicknameChanged (const QString& oldNick, const QString& newNick);

    /**
    * Sent when the nickname of this client changed.
    * \arg nick The new nickname of this client.
    */
    void userNicknameChanged (const QString& nick);

    /**
    * Sent when a user has joined a channel.
    * \arg nick Nickname of the user that joined the channel.
    * \arg channel Channel that this user joined.
    */
    void userJoined (const QString& nick, const QString& channel);

    /**
    * Sent when a user quits.
    * \arg nick Nickname of the user that quit.
    * \arg reason Reason of the user to quit.
    */
    void userQuit (const QString& nick, const QString& reason);

    /**
    * Sent when a user logged in.
    * \arg nick The nickname of the user that logged in.
    */
    void loggedIn (const QString& nick);

    /**
    * Sent when the server provides a userlist for a channel.
    * \arg channel The channel that userlist applies to.
    * \arg list The actual userlist.
    */
    void userList (const QString& channel, const QStringList& list);

    void debugMessage (const QString& message);

private slots:
    void handleConnected ();
    void handleDisconnected ();
    void handleReadyRead ();

private:
    void handleNicknameChanged (const QString& oldNick, const QString& newNick);
    void handleUserJoined (const QString& nick, const QString& channel);
    void handleUserQuit (const QString& nick, const QString& reason);
    void handleIncomingLine (const QString& line);
    void sendLine (const QString& line);

    QHostAddress                              m_host;
    int                                       m_port;
    QString                                   m_nickname;
    bool                                      m_connected;
    bool                                      m_loggedIn;
    QTcpSocket                                m_tcpSocket;
    QMap<QString, IRCChannel*>       m_channels;
};
