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

#include "IRCServerView.h"
#include "ui_IRCServerView.h"

IRCServerView::IRCServerView(IRCClientInterface *ircClient, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IRCServerView)
{
    ui->setupUi(this);
    m_ircClient = ircClient;

    connect(m_ircClient, SIGNAL(notification(QString,QString)),
            this, SLOT(handleNotification(QString,QString)));

    connect(m_ircClient, SIGNAL(debugMessage(QString)),
            this, SLOT(handleDebugMessage(QString)));

    connect(m_ircClient, SIGNAL(error(QString)),
            this, SLOT(handleErrorMessage(QString)));
}

IRCServerView::~IRCServerView()
{
    delete ui;
}

void IRCServerView::handleNotification(QString sender, QString message)
{
    ui->serverTextEdit->append(sender + ": " + message);
}

void IRCServerView::handleDebugMessage(QString message)
{
    ui->serverTextEdit->append(message);
}

void IRCServerView::handleErrorMessage(QString message)
{
    ui->serverTextEdit->append(message);
}
