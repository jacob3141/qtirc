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

// Qt includes
#include <QString>
#include <QStringList>
#include <QTextDocument>
#include <QStringListModel>

class IRCClientInterface;
/**
  * \class IRCChannelProxyInterface
  * Interface for a handle to an IRC channel.
  */
class IRCChannelProxyInterface : public QObject
{
    Q_OBJECT
public:
    IRCChannelProxyInterface (IRCClientInterface *, const QString&, QObject *parent = 0) : QObject (parent) { }
    virtual ~IRCChannelProxyInterface () { }

    /** Returns the conversation model part. */
    virtual QTextDocument *conversationModel () = 0;

    /** Returns a string list model for the user list. */
    virtual QStringListModel *userListModel () = 0;

    /** Returns the name of this channel. */
    virtual QString channelName () = 0;

public slots:
    /**
    * Name reply from the server.
    * \arg nickList The nick list from the server.
    */
    virtual void nameReply (const QStringList& nickList) = 0;

    /**
    * Sends a public message onto this channel.
    * \arg message The message that should be sent.
    */
    virtual void sendMessage (const QString& message) = 0;

    /** Requests to join this channel. */
    virtual void sendJoinRequest () = 0;

    /**
    * Requests to leave this channel.
    * \arg reason Reason for leaving the channel.
    */
    virtual void leave (const QString& reason) = 0;

    virtual void handleMessage(const QString& nick, const QString& message) = 0;
    virtual void handleNickChange (const QString& oldNick, const QString& newNick) = 0;
    virtual void handleJoin (const QString& nick) = 0;
};
