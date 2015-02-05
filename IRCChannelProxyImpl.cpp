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
#include <QPlainTextDocumentLayout>

IRCChannelProxyImpl::IRCChannelProxyImpl (IRCClientInterface *ircClient, const QString& channelName, QObject *parent)
    : IRCChannelProxyInterface(ircClient, channelName, parent),
      m_ircClient(ircClient)
{
    m_channelName = channelName;
    connect(ircClient, SIGNAL(nicknameChanged(QString, QString)),
             this, SLOT(handleNickChange(QString, QString)));
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
IRCChannelProxyImpl::nameReply(const QStringList &nickList)
{
    m_userList.append(nickList);
    processUserList();
}

void
IRCChannelProxyImpl::sendMessage(const QString& message)
{
    QStringList arguments;
    arguments << m_channelName;
    arguments << message;
    m_ircClient->sendIRCCommand(IRCCommand::PrivateMessage, arguments);
    handleMessage(m_ircClient->nickname(), message);
}

void
IRCChannelProxyImpl::sendJoinRequest ()
{
    m_ircClient->sendIRCCommand (IRCCommand::Join, QStringList (m_channelName));
}

void
IRCChannelProxyImpl::leave (const QString& reason)
{
    Q_UNUSED (reason);
}

void IRCChannelProxyImpl::handleMessage(const QString &nick, const QString &message)
{
    int i, colorTablePosition = 0;
    for(i = 0; i < m_userList.size(); i++) {
        if(m_userList.at(i) == nick) {
            colorTablePosition = i;
            break;
        }
    }

    QColor color = m_colorTable.at(colorTablePosition);

    QTextEdit textEdit;
    textEdit.setDocument(&m_conversationModel);
    textEdit.append(QString("<font color=\"%1\"><b>").arg(color.name()) + nick + "</b>: " + message + "</font>");
}

void
IRCChannelProxyImpl::handleNickChange (const QString &oldNick, const QString &newNick)
{
    m_userList = m_userListModel.stringList ();
    m_userList.removeAll (oldNick);
    processUserList();
}

void
IRCChannelProxyImpl::handleJoin (const QString &nick)
{
    m_userList = m_userListModel.stringList ();
    m_userList.append (nick);
    processUserList();
}

void
IRCChannelProxyImpl::processUserList()
{
    m_userList.removeDuplicates();
    m_userList.sort();
    m_userListModel.setStringList (m_userList);
    rebuildColorTable();
}

void
IRCChannelProxyImpl::rebuildColorTable()
{
    int i, size = m_userList.size();
    m_colorTable.clear();
    m_colorTable.resize(size);
    for(i = 0; i < size; i++) {
        m_colorTable[i] = QColor::fromHsv((double)i * 360.0 / (double)size, 255, 128);
    }
}
