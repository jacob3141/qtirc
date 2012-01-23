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

#include <QDebug>
#include <QInputDialog>
#include "QIRCWidget.h"
#include "ui_QIRCWidget.h"
#include "IRCChannelView.h"
#include "IRCServerView.h"

QIRCWidget::QIRCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QIRCWidget)
{
    ui->setupUi(this);
    m_ircClient = new IRCClientImpl();

    connect(ui->nickPushButton, SIGNAL(clicked()), this, SLOT(showChangeUserNickPopup()));
    connect(ui->chatMessageTextEdit, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(m_ircClient, SIGNAL(loggedIn(QString)), this, SLOT(handleConnected(QString)));

    m_ircServerView = new IRCServerView(m_ircClient);
    ui->channelsTabWidget->addTab(m_ircServerView, "Server status");
}

QIRCWidget::~QIRCWidget()
{
    delete ui;
    delete m_ircClient;
}

void QIRCWidget::joinChannel(QString channel)
{
    IRCChannelProxyInterface *ircChannelProxy = m_ircClient->ircChannelProxy(channel);
    if(!m_trackedChannels.contains(ircChannelProxy)) {
        m_trackedChannels.insert(ircChannelProxy);

        IRCChannelView *ircChannelView = new IRCChannelView(ircChannelProxy);
        int tabIndex = ui->channelsTabWidget->addTab(ircChannelView, channel);
        ui->channelsTabWidget->setCurrentIndex(tabIndex);

        ircChannelProxy->sendJoinRequest();
    }
}

void QIRCWidget::connectToServer(QString url, QString nick)
{
    ui->nickPushButton->setText(nick);

    QHostInfo hostInfo = QHostInfo::fromName(url);
    QList<QHostAddress> hostAddresses = hostInfo.addresses();
    if(hostAddresses.isEmpty ()) {
    } else {
        m_ircClient->connectToHost(hostAddresses.at(0), 6667, nick);
    }
}

void QIRCWidget::showChangeUserNickPopup()
{
    bool ok;
    QString newNick =
            QInputDialog::getText(this, QString("Nickname"),
                                   QString("Type in your nickname:"),
                                   QLineEdit::Normal, m_ircClient->nickname(), &ok);
    if(ok) {
        m_ircClient->sendNicknameChangeRequest(newNick);
    }
}

void QIRCWidget::sendMessage(QString message)
{
    // Do not send empty messages.
    if (message.isEmpty ())
        return;

    // Remove trailing spaces.
    while(message.at(0).isSpace())
        message.remove(0, 1);

    if(message.startsWith("/")) {
        QStringList line = message.split(QRegExp ("\\s+"), QString::SkipEmptyParts);
        QString command = line.at(0);

        if(command == "/join") {
            joinChannel(line.at(1));
        } else if(command == "/nick") {
            m_ircClient->sendNicknameChangeRequest(line.at(1));
        } else if(command == "/msg") {
            QString recipient = line.at(1);
            // Since we splitted the message before, we have to glue it together again.
            QString pmsg = "";
            for (int i = 2; i < line.length (); i++) {
                pmsg += line.at(i);
                pmsg += " ";
            }
            m_ircClient->sendPrivateMessage(recipient, pmsg);
        }
    } else { // Not a command.
        QWidget *widget = ui->channelsTabWidget->currentWidget();
        if(widget) {
            IRCChannelView *ircChannelView =
                    dynamic_cast<IRCChannelView*>(widget);
            if(ircChannelView) {
                IRCChannelProxyInterface *ircChannelProxy = ircChannelView->ircChannelProxy();
                if(ircChannelProxy) {
                    ircChannelProxy->sendMessage(message);
                }
                ircChannelView->scrollToBottom();
            }
        }
    }
}

void QIRCWidget::handleConnected(QString server)
{
    Q_UNUSED(server);
    emit connected();
}
