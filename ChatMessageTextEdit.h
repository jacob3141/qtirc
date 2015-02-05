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

#ifndef CHATMESSAGETEXTEDIT_H
#define CHATMESSAGETEXTEDIT_H

#include <QPlainTextEdit>
#include <QCompleter>

/**
  * \class ChatMessageTextEdit
  * Subclass QPlainTextEdit to provide extra functionality.
  */
class ChatMessageTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ChatMessageTextEdit(QWidget *parent = 0);
    ~ChatMessageTextEdit();

    void setCompleter(QCompleter *m_completer);
    QCompleter *completer() const;

signals:
    void sendMessage (const QString& message);

protected:
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);

private slots:
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;

private:
    QCompleter *m_completer;
};

#endif // CHATMESSAGETEXTEDIT_H
