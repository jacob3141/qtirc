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
#include "ircserverwidget.h"
#include "ui_ircserverwidget.h"

IRCServerWidget::IRCServerWidget(IRCClient *ircClient, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IRCServerWidget)
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

IRCServerWidget::~IRCServerWidget()
{
    delete ui;
}

void IRCServerWidget::handleNotification(QString sender, QString message)
{
    ui->serverTextEdit->append(sender + ": " + message);
}

void IRCServerWidget::handleDebugMessage(QString message)
{
    ui->serverTextEdit->append(message);
}

void IRCServerWidget::handleErrorMessage(QString message)
{
    ui->serverTextEdit->append(message);
}
