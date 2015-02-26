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
#include "ircchannelwidget.h"
#include "ui_ircchannelwidget.h"

IRCChannelWidget::IRCChannelWidget(IRCChannel *ircChannelProxy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IRCChannelWidget)
{
    ui->setupUi(this);
    m_ircChannelProxy = ircChannelProxy;

    ui->chatTextEdit->setDocument(m_ircChannelProxy->conversationModel());
    ui->usersListView->setModel(m_ircChannelProxy->userListModel());
}

IRCChannelWidget::~IRCChannelWidget()
{
    delete ui;
}

IRCChannel *IRCChannelWidget::ircChannelProxy()
{
    return m_ircChannelProxy;
}

void IRCChannelWidget::scrollToBottom()
{
    if(ui->chatTextEdit->verticalScrollBar()) {
        ui->chatTextEdit->verticalScrollBar()->setValue(
                    ui->chatTextEdit->verticalScrollBar()->maximum());
    }
}

