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

#include "IRCChannelView.h"
#include "ui_IRCChannelView.h"

IRCChannelView::IRCChannelView(IRCChannelProxyInterface *ircChannelProxy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IRCChannelView)
{
    ui->setupUi(this);
    m_ircChannelProxy = ircChannelProxy;

    ui->chatTextEdit->setDocument(m_ircChannelProxy->conversationModel());
    ui->usersListView->setModel(m_ircChannelProxy->userListModel());
}

IRCChannelView::~IRCChannelView()
{
    delete ui;
}

IRCChannelProxyInterface *IRCChannelView::ircChannelProxy()
{
    return m_ircChannelProxy;
}

void IRCChannelView::scrollToBottom()
{
    if(ui->chatTextEdit->verticalScrollBar()) {
        ui->chatTextEdit->verticalScrollBar()->setValue(
                    ui->chatTextEdit->verticalScrollBar()->maximum());
    }
}

