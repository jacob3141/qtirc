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

#ifndef IRCCOMMAND_H
#define IRCCOMMAND_H

#include <QString>

/**
  * \namespace IRCCommand
  * This namespace includes all IRC commands.
  */
namespace IRCCommand
{
  const QString Password = "PASS";
  const QString Nick = "NICK";
  const QString User = "USER";
  const QString Operation = "OPER";
  const QString Service = "SERVICE";
  const QString Quit = "QUIT";
  const QString ServerQuit = "SQUIT";

  const QString Join = "JOIN";
  const QString Part = "PART";
  const QString Mode = "MODE";
  const QString Topic = "TOPIC";
  const QString Names = "NAMES";
  const QString List = "LIST";
  const QString Invite = "INVITE";
  const QString Kick = "KICK";

  const QString PrivateMessage = "PRIVMSG";
  const QString Notice = "NOTICE";

  const QString MessageOfTheDay = "MOTD";
  const QString ListUsers = "LUSERS";
  const QString Version = "VERSION";
  const QString Stats = "STATS";
  const QString Links = "LINKS";
  const QString Time = "TIME";
  const QString Command = "CONNECT";
  const QString Trace = "TRACE";
  const QString Admin = "ADMIN";
  const QString Info = "INFO";

  const QString ServerList = "SERVLIST";
  const QString ServerQuery = "SQUERY";

  const QString Who = "WHO";
  const QString WhoIs = "WHOIS";
  const QString WhoWas = "WHOWAS";

  const QString Kill = "KILL";
  const QString Ping = "PING";
  const QString Pong = "PONG";
  const QString Error = "ERROR";

  const QString Away = "AWAY";
  const QString Rehash = "REHASH";
  const QString Die = "DIE";
  const QString Restart = "RESTART";
  const QString Summon = "SUMMON";
  const QString Users = "USERS";
  const QString OperatorWall = "OPERWALL";
  const QString UserHost = "USERHOST";
  const QString IsOn = "ISON";
}

#endif // IRCCOMMAND_H
