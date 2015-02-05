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

/**
  * \class IRCServerMessage
  * The IRCServerMessage class is a wrapper for server messages.
  * It parses the server message into its single bits and makes these
  * available through Getter-methods.
  */
class IRCServerMessage {
public:
  IRCServerMessage (const QString& serverMessage);

  bool isNumeric ()
  { return m_isNumeric; }

  QString nick ()
  { return m_nick; }

  QString command ()
  { return m_command; }

  int numericValue ();
  QString parameter (int index);

private:
  int         m_codeNumber;
  bool        m_isNumeric;
  QString     m_nick;
  QString     m_user;
  QString     m_host;
  QString     m_command;
  QStringList m_parameters;
};
