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

#ifndef QIRCWIDGET_H
#define QIRCWIDGET_H

#include <QWidget>
#include <QSet>
#include "IRCClientImpl.h"
#include "IRCServerView.h"

namespace Ui {
    class QIRCWidget;
}

class QIRCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QIRCWidget(QWidget *parent = 0);
    ~QIRCWidget();

    void connectToServer(QString url, QString nick, QString channelAutoJoin = QString());
    void joinChannel(QString channel);

public slots:
    void showChangeUserNickPopup();
    void sendMessage(QString message);
    void handleConnected(QString server);

signals:
    void connected();

private:
    Ui::QIRCWidget *ui;
    IRCClientInterface *m_ircClient;
    IRCServerView *m_ircServerView;
    QSet<IRCChannelProxyInterface*> m_trackedChannels;
    QString m_channelAutoJoin;
};

#endif // QIRCWIDGET_H
