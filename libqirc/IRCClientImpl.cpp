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

#include "IRCClientImpl.h"

IRCClientImpl::IRCClientImpl (QObject *parent)
    : IRCClientInterface (parent)
{
    m_loggedIn = false;
    connect (&m_tcpSocket, SIGNAL (connected ()), this, SLOT (handleConnected ()));
    connect (&m_tcpSocket, SIGNAL (disconnected ()), this, SLOT (handleDisconnected ()));
    connect (&m_tcpSocket, SIGNAL (readyRead ()), this, SLOT (handleReadyRead ()));
}

IRCClientImpl::~IRCClientImpl ()
{
    foreach (IRCChannelProxyInterface *ircChannelProxy, m_channels)
    {
        delete ircChannelProxy;
    }
}

void
IRCClientImpl::connectToHost (const QHostAddress& host, int port, const QString& initialNick)
{
    m_host = host;
    m_nickname = initialNick;
    m_tcpSocket.connectToHost(host, port);
}

void
IRCClientImpl::disconnect ()
{
    m_tcpSocket.disconnect ();
}

void
IRCClientImpl::reconnect ()
{
    disconnect ();
    connectToHost (m_host, m_port, m_nickname);
}

bool
IRCClientImpl::isConnected ()
{
    return m_connected;
}

bool
IRCClientImpl::isLoggedIn ()
{
    return m_loggedIn;
}

const QHostAddress&
IRCClientImpl::host()
{
    return m_host;
}

int
IRCClientImpl::port()
{
    return m_port;
}

IRCChannelProxyInterface *
IRCClientImpl::ircChannelProxy (const QString &channel)
{
    if (!m_channels.contains (channel))
        m_channels[channel] = new IRCChannelProxyImpl(this, channel);
    return m_channels[channel];
}

void
IRCClientImpl::sendNicknameChangeRequest (const QString &nickname)
{
    sendIRCCommand (IRCCommand::Nick, QStringList (nickname));
}

void
IRCClientImpl::sendPrivateMessage (const QString &recipient, const QString &message)
{
    QStringList arguments;
    arguments << recipient;
    arguments << message;
    sendIRCCommand (IRCCommand::PrivateMessage, arguments);
}

const QString&
IRCClientImpl::nickname ()
{
    return m_nickname;
}

void
IRCClientImpl::handleConnected ()
{
    m_connected = true;
    QStringList arguments;
    arguments << "na" << "0" << "0" << "na";
    sendIRCCommand (IRCCommand::User, arguments);
    sendNicknameChangeRequest (m_nickname);
    emit connected (m_host.toString ());
}

void
IRCClientImpl::handleDisconnected ()
{
    m_connected = false;
    emit disconnected ();
}

void
IRCClientImpl::handleReadyRead ()
{
    QByteArray line;
    do
    {
        line = m_tcpSocket.readLine();
        if (line.size ())
            handleIncomingLine(QString::fromUtf8(line.data ()));
        else
            break;
    }
    while (true);
}

void
IRCClientImpl::handleNicknameChanged (const QString &oldNick, const QString &newNick)
{
    // Check if our nickname changed.
    if (oldNick == m_nickname)
    {
        m_nickname = newNick;
        emit userNicknameChanged (m_nickname);
    }
    emit nicknameChanged (oldNick, newNick);
}

void
IRCClientImpl::handleUserJoined (const QString &nick, const QString &channel)
{
    ircChannelProxy (channel)->handleJoin (nick);
    emit userJoined (nick, channel);
}

void
IRCClientImpl::handleUserQuit (const QString &nick, const QString &reason)
{
    emit userQuit (nick, reason);
}

void
IRCClientImpl::handleIncomingLine (const QString &line)
{
    if (m_connected && !line.isEmpty())
    {
        IRCServerMessage ircServerMessage(line);
        if (ircServerMessage.isNumeric () == true)
        {
            switch (ircServerMessage.numericValue ())
            {
            case IRCReply::Welcome:
                m_loggedIn = true;
                emit userNicknameChanged(nickname ());
                emit loggedIn(nickname ());
                break;
            case IRCError::NicknameInUse:
            case IRCError::NickCollision:
                // If we are already logged in, the user attempted to
                // switch to a username that is already existing.
                // In that case warn him.
                if (isLoggedIn ())
                {
                    emit error ("The nickname is already in use.");
                }
                // Otherwise we are attempting to log in to the server.
                // Change the nick so that we can at least log in.
                else
                {
                    m_nickname += "_";
                    sendNicknameChangeRequest (m_nickname);
                }
                break;
            case IRCError::PasswordMismatch:
                emit error ("The password you provided is not correct.");
                break;
            case IRCReply::MessageOfTheDayStart:
            case IRCReply::MessageOfTheDay:
            case IRCReply::MessageOfTheDayEnd:
            case IRCError::NoMessageOfTheDay:
                break;
            case IRCReply::NoTopic:
            case IRCReply::Topic:
                break;
            case IRCReply::NameReply:
                QString channel = ircServerMessage.parameter (2);
                QString nickList = ircServerMessage.parameter (3);
                ircChannelProxy(channel)
                    ->nameReply(nickList.split(
                        QRegExp ("\\s+"), QString::SkipEmptyParts));
                break;
            }
        }
        else
        {
            QString command = ircServerMessage.command ();
            if (command == IRCCommand::Nick)
            {
                handleNicknameChanged (ircServerMessage.nick(), ircServerMessage.parameter (0));
            }
            else if (command == IRCCommand::Quit)
            {
                handleUserQuit (ircServerMessage.nick (), ircServerMessage.parameter (0));
            }
            else if (command == IRCCommand::Join)
            {
                handleUserJoined(ircServerMessage.nick (), ircServerMessage.parameter (0));
            }
            else if (command == IRCCommand::Part)
            {
                emit debugMessage ("WRITEME: Received part.");
                //emit part (ircEvent.getNick ().toStdString ().c_str (),
                //           ircEvent.getParam (0).toStdString ().c_str (),
                //           ircEvent.getParam (1).toStdString ().c_str ());
            }
            else if (command == IRCCommand::Mode)
            {
                emit debugMessage ("WRITEME: Received mode.");
                //emit mode (&ircEvent);
            }
            else if (command == IRCCommand::Topic)
            {
                emit debugMessage
                        (QString("WRITEME: Received topic: %1")
                         .arg (ircServerMessage.parameter (0)));
            }
            else if (command == IRCCommand::Kick)
            {
                emit debugMessage ("WRITEME: Received kick command.");
            }
            else if (command == IRCCommand::Invite)
            {
                emit debugMessage ("WRITEME: Received invite command.");

            }
            else if (command == IRCCommand::PrivateMessage)
            {
                IRCChannelProxyInterface *ircChannel = ircChannelProxy(ircServerMessage.parameter(0));
                if(ircChannel) {
                    ircChannel->handleMessage(ircServerMessage.nick(), ircServerMessage.parameter(1));
                }
            }
            else if (command == IRCCommand::Notice)
            {
                emit notification(ircServerMessage.nick(), ircServerMessage.parameter(1));
            }
            else if (command == IRCCommand::Ping)
            {
                sendIRCCommand (IRCCommand::Pong, QStringList (m_nickname));
            }
            else if (command == IRCCommand::Error)
            {
                emit error (ircServerMessage.parameter (0));
            }
            else
            {
                emit debugMessage (QString("FIXME: Received unknown reply: %1").arg(command));
            }
        }
    }
}

void
IRCClientImpl::sendLine (const QString &line)
{
    if (m_connected)
        m_tcpSocket.write ( (line +  + "\r\n").toUtf8 ());
}

void
IRCClientImpl::sendIRCCommand (const QString &command, const QStringList &arguments)
{
    QString line = command;
    for (int i = 0; i < arguments.size (); i++)
    {
        bool applyColon = false;
        // Usually all parameters are separated by spaces.
        // The last parameter of the message may contain spaces, it is usually used
        // to transmit messages. In order to parse it correctly, if needs to be prefixed
        // with a colon, so the server knows to ignore all forthcoming spaces and has to treat
        // all remaining characters as a single parameter. If we detect any whitespace in the
        // last argument, prefix it with a colon:
        if ((i == arguments.size () - 1) && arguments.at (i).contains (QRegExp("\\s")))
            applyColon = true;
        line += QString (" %1%2").arg (applyColon ? ":" : "").arg (arguments.at (i));
    }
    sendLine (line);
}
