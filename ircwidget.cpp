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
#include "ircwidget.h"
#include "ircchannelwidget.h"
#include "ircserverwidget.h"

// Qt includes
#include <QDebug>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

IRCWidget::IRCWidget(QWidget *parent) :
    QWidget(parent)
{
    _ircClient = new IRCClient;
    _tabWidget = new QTabWidget;

    _ircServerWidget = new IRCServerWidget(_ircClient);
    _tabWidget->addTab(_ircServerWidget, tr("Server"));

    QWidget *messageWidget = new QWidget;
    _pushButtonNick = new QPushButton;
    _pushButtonNick->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    _chatMessageTextEdit = new ChatMessageTextEdit;
    _chatMessageTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    messageWidget->setMaximumHeight(80);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(_pushButtonNick);
    hBoxLayout->addWidget(_chatMessageTextEdit);
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    messageWidget->setLayout(hBoxLayout);

    _splitter = new QSplitter;
    _splitter->setOrientation(Qt::Vertical);
    _splitter->addWidget(_tabWidget);
    _splitter->addWidget(messageWidget);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(_splitter);
    setLayout(vBoxLayout);


    connect(_pushButtonNick, SIGNAL(clicked()), this, SLOT(showChangeUserNickPopup()));
    connect(_chatMessageTextEdit, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(_ircClient, SIGNAL(loggedIn(QString)), this, SLOT(handleConnected(QString)));

    _autoJoinChannel = QString();
}

IRCWidget::~IRCWidget()
{

    delete _ircClient;
}

void IRCWidget::joinChannel(QString channel)
{
    IRCChannel *ircChannel = _ircClient->ircChannel(channel);
    if(!_channels.contains(ircChannel)) {
        _channels.insert(ircChannel);

        IRCChannelWidget *ircChannelWidget = new IRCChannelWidget(ircChannel);
        int tabIndex = _tabWidget->addTab(ircChannelWidget, channel);
        _tabWidget->setCurrentIndex(tabIndex);

        ircChannel->sendJoinRequest();
    }
}

void IRCWidget::connectToServer(QString nick,
                                QString url,
                                quint16 port,
                                QString autoJoinChannel)
{
    _autoJoinChannel = autoJoinChannel;
    _pushButtonNick->setText(nick);

    QHostInfo hostInfo = QHostInfo::fromName(url);
    QList<QHostAddress> hostAddresses = hostInfo.addresses();
    if(hostAddresses.isEmpty()) {
    } else {
        _ircClient->connectToHost(hostAddresses.at(0), port, nick);
    }
}

void IRCWidget::showChangeUserNickPopup()
{
    bool ok;
    QString newNick =
            QInputDialog::getText(this, QString("Nickname"),
                                   QString("Type in your nickname:"),
                                   QLineEdit::Normal, _ircClient->nickname(), &ok);
    if(ok) {
        _ircClient->sendNicknameChangeRequest(newNick);
    }
}

void IRCWidget::sendMessage(QString message)
{
    // Do not send empty messages.
    if (message.isEmpty())
        return;

    // Remove trailing spaces.
    while(message.at(0).isSpace())
        message.remove(0, 1);

    if(message.startsWith("/")) {
        QStringList line = message.split(QRegExp ("\\s+"), QString::SkipEmptyParts);
        QString command = line.at(0);

        if(command == "/join" || command == "/j") {
            joinChannel(line.at(1));
        } else if(command == "/nick") {
            _ircClient->sendNicknameChangeRequest(line.at(1));
        } else if(command == "/msg") {
            QString recipient = line.at(1);
            // Since we splitted the message before, we have to glue it together again.
            QString pmsg = "";
            for (int i = 2; i < line.length (); i++) {
                pmsg += line.at(i);
                pmsg += " ";
            }
            _ircClient->sendPrivateMessage(recipient, pmsg);
        }
    } else { // Not a command.
        QWidget *widget = _tabWidget->currentWidget();
        if(widget) {
            IRCChannelWidget *ircChannelWidget =
                    dynamic_cast<IRCChannelWidget*>(widget);
            if(ircChannelWidget) {
                IRCChannel *ircChannelProxy = ircChannelWidget->ircChannelProxy();
                if(ircChannelProxy) {
                    ircChannelProxy->sendMessage(message);
                }
                ircChannelWidget->scrollToBottom();
            }
        }
    }
}

void IRCWidget::handleConnected(QString server)
{
    Q_UNUSED(server);
    if(!_autoJoinChannel.isEmpty()) {
        joinChannel(_autoJoinChannel);
    }
    emit connected();
}
