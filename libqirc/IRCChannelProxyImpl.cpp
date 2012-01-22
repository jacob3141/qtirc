/* qirc - Qt based IRC client
 * Copyright (C) 2012 Jacob Dawid (jacob.dawid@googlemail.com)
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

#include "IRCClientInterface.h"
#include "IRCChannelProxyImpl.h"
#include "IRCCommand.h"

IRCChannelProxyImpl::IRCChannelProxyImpl (IRCClientInterface *clientInterface, const QString& channelName, QObject *parent)
    : IRCChannelProxyInterface (clientInterface, channelName, parent),
      m_clientInterface (clientInterface)
{
    m_channelName = channelName;
    connect (clientInterface, SIGNAL (nicknameChanged (QString,QString)),
             this, SLOT (handleNickChange (QString,QString)));
}

QTextDocument *
IRCChannelProxyImpl::conversationModel ()
{
    return &m_conversationModel;
}

QStringListModel *
IRCChannelProxyImpl::userListModel ()
{
    return &m_userListModel;
}

QString
IRCChannelProxyImpl::channelName ()
{
    return m_channelName;
}

void
IRCChannelProxyImpl::setNickList (const QStringList &nickList)
{
    m_userList = nickList;
    m_userListModel.setStringList (nickList);
}

void
IRCChannelProxyImpl::sendMessage (const QString& message)
{
    QStringList arguments;
    arguments << m_channelName;
    arguments << message;
    m_clientInterface->sendIRCCommand (IRCCommand::PrivateMessage, arguments);
}

void
IRCChannelProxyImpl::sendJoinRequest ()
{
    m_clientInterface->sendIRCCommand (IRCCommand::Join, QStringList (m_channelName));
}


void
IRCChannelProxyImpl::leave (const QString& reason)
{
    Q_UNUSED (reason);
}

void
IRCChannelProxyImpl::handleNickChange (const QString &oldNick, const QString &newNick)
{
    m_userList = m_userListModel.stringList ();
    m_userList.removeAll (oldNick);
    m_userList.append (newNick);
    m_userListModel.setStringList (m_userList);
}

void
IRCChannelProxyImpl::handleJoin (const QString &nick)
{
    m_userList = m_userListModel.stringList ();
    m_userList.append (nick);
    m_userListModel.setStringList (m_userList);
}
