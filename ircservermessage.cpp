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

// Own includes
#include "ircservermessage.h"

IRCServerMessage::IRCServerMessage (const QString& serverMessage)
{
    if (serverMessage.isEmpty ())
        return;

    int position = 0;
    QString buffer;

    m_nick = "";
    m_user = "";
    m_host = "";

    // A server message starting with a prefix indicates
    // a prefix. A prefix has the format:
    // :nick!user@host
    // followed by a space character.
    if (serverMessage.startsWith (":"))
    {
        position++;
        while ((position < serverMessage.size ())
               &&(serverMessage.at (position) != '!')
               && !serverMessage.at (position).isSpace ())
        {
            buffer.append (serverMessage.at (position));
            position++;
        }
        m_nick = buffer, buffer.clear (), position++;

        // If it belongs to the prefix, it must be concatenanted neatlessly without
        // any spaces.
        if (position < serverMessage.size())
            if (!serverMessage.at (position - 1).isSpace ())
            {
                while ((position < serverMessage.size ())
                       && serverMessage.at (position) != '@')
                {
                    buffer.append (serverMessage.at (position));
                    position++;
                }
                m_user = buffer, buffer.clear (), position++;
            }

        // If it belongs to the prefix, it must be concatenanted neatlessly without
        // any spaces.
        if (position < serverMessage.size())
            if (!serverMessage.at (position - 1).isSpace ())
            {
                while ((position < serverMessage.size ())
                       && serverMessage.at (position) != ' ')
                {
                    buffer.append (serverMessage.at (position));
                    position++;
                }
                m_host = buffer, buffer.clear (), position++;
            }
    }

    // The next part is the command. The command can either be numeric
    // or a written command.
    while ((position < serverMessage.size ())
           && !serverMessage.at (position).isSpace ())
    {
        buffer.append (serverMessage.at (position));
        position++;
    }
    m_command = buffer.toUpper (), buffer.clear (), position++;
    m_codeNumber = m_command.toInt (&m_isNumeric);

    // Next: a list of parameters. If any of these parameters
    // starts with a colon, we have to read everything that follows
    // as a single parameter.
    bool readUntilEnd = false;
    while (position < serverMessage.size ())
    {
        if (buffer.isEmpty () && !readUntilEnd && (serverMessage.at (position) == ':'))
        {
            readUntilEnd = true;
        }
        else
        {
            if (readUntilEnd)
            {
                buffer.append (serverMessage.at (position));
            }
            else
            {
                if (serverMessage.at (position).isSpace ())
                {
                    if (!buffer.isEmpty ())
                    {
                        m_parameters.append (buffer);
                        buffer.clear ();
                    }
                }
                else
                {
                    buffer.append (serverMessage.at (position));
                }
            }
        }
        position++;
    }

    if (!buffer.isEmpty ())
    {
        // We need to chop off \r\n here.
        buffer.chop (2);
        m_parameters.append (buffer);
    }
}

int
IRCServerMessage::numericValue ()
{
    if (m_isNumeric)
        return m_codeNumber;
    return -1;
}

QString
IRCServerMessage::parameter (int index)
{
    if (index >= 0 && index < m_parameters.size ())
        return m_parameters.at (index);
    return "";
}
