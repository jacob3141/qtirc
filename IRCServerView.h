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

#ifndef IRCSERVERVIEW_H
#define IRCSERVERVIEW_H

#include <QWidget>
#include "IRCClientImpl.h"

namespace Ui {
    class IRCServerView;
}

class IRCServerView : public QWidget
{
    Q_OBJECT

public:
    explicit IRCServerView(IRCClientInterface *ircClient, QWidget *parent = 0);
    ~IRCServerView();

public slots:
    void handleNotification(QString sender, QString message);
    void handleDebugMessage(QString message);
    void handleErrorMessage(QString message);

private:
    Ui::IRCServerView *ui;
    IRCClientInterface *m_ircClient;
};

#endif // IRCSERVERVIEW_H
