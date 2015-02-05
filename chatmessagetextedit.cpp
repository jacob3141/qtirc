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
#include "chatmessagetextedit.h"

// Qt includes
#include <QAbstractItemView>

ChatMessageTextEdit::ChatMessageTextEdit (QWidget *parent)
    : QPlainTextEdit (parent), m_completer (new QCompleter())
{
    setMaximumHeight (50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

ChatMessageTextEdit::~ChatMessageTextEdit ()
{
}

void
ChatMessageTextEdit::setCompleter (QCompleter *completer)
{
    if (m_completer)
        QObject::disconnect (m_completer, 0, this, 0);

    m_completer = completer;

    if (!m_completer)
        return;

    m_completer->setWidget (this);
    m_completer->setCompletionMode (QCompleter::PopupCompletion);
    m_completer->setCaseSensitivity (Qt::CaseInsensitive);
    QObject::connect (m_completer, SIGNAL (activated (QString)),
                      this, SLOT (insertCompletion (QString)));
}

QCompleter *
ChatMessageTextEdit::completer () const
{
    return m_completer;
}

void
ChatMessageTextEdit::insertCompletion(const QString& completion)
{

    if (m_completer->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - m_completer->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString
ChatMessageTextEdit::textUnderCursor () const
{
    QTextCursor tc = textCursor ();
    tc.select (QTextCursor::WordUnderCursor);
    return tc.selectedText ();
}

void
ChatMessageTextEdit::focusInEvent (QFocusEvent *e)
{
    if (m_completer)
        m_completer->setWidget (this);
    QPlainTextEdit::focusInEvent (e);
}

void
ChatMessageTextEdit::keyPressEvent (QKeyEvent *keyPressEvent)
{
    if (m_completer) {
        switch (keyPressEvent->key ()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (! (keyPressEvent->modifiers () & Qt::ShiftModifier))
            {
                emit sendMessage (document ()->toPlainText ());
                document ()->setPlainText ("");
            }
            else
            {
                QPlainTextEdit::keyPressEvent (keyPressEvent);
            }
            break;
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            keyPressEvent->ignore ();
            return;
        default:
            QPlainTextEdit::keyPressEvent(keyPressEvent);
            break;
        }

        QString completionPrefix = textUnderCursor ();
        if (completionPrefix != m_completer->completionPrefix ())
        {
            m_completer->setCompletionPrefix(completionPrefix);
        }

        if (completionPrefix.length() > 2)
        {
            m_completer->popup ()->setCurrentIndex (m_completer->completionModel ()->index (0, 0));
            m_completer->complete ();
        }
        else
        {
            m_completer->popup ()->hide ();
        }
    }
}
