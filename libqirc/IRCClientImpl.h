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

#ifndef IRCCLIENTIMPL_H
#define IRCCLIENTIMPL_H

#include <QTcpSocket>
#include <QHostInfo>
#include <QStringList>
#include <QTextDocument>
#include <QStringListModel>

#include "IRCServerMessage.h"
#include "IRCClientInterface.h"
#include "IRCCommand.h"
#include "IRCReply.h"
#include "IRCError.h"
#include "IRCChannelProxyImpl.h"

/**
  * \class IRCClientImpl
  * Implements an IRC client. This class can maintain a connection to one server.
  * In order to interface an IRC channel, use the ircChannelProxy-method to retrieve
  * a handle.
  */
class IRCClientImpl : public IRCClientInterface
{
  Q_OBJECT
public:
  IRCClientImpl (QObject *parent = 0);
  ~IRCClientImpl ();

  const QString& nickname ();
  bool isConnected ();
  bool isLoggedIn ();
  const QHostAddress& host();
  int port();
  IRCChannelProxyInterface *ircChannelProxy(const QString& channel);
  void sendIRCCommand (const QString& command, const QStringList& arguments);

public slots:
  void connectToHost (const QHostAddress& host, int port, const QString& initialNick);
  void disconnect ();
  void reconnect ();

  void sendNicknameChangeRequest (const QString &nickname);
  void sendPrivateMessage (const QString &recipient, const QString &message);

signals:
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
  QMap<QString, IRCChannelProxyInterface*>  m_channels;
};

#endif // IRCCLIENTIMPL_H
