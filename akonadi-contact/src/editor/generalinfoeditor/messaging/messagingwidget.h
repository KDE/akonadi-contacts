/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef MESSAGINGWIDGET_H
#define MESSAGINGWIDGET_H

#include <QWidget>

#include <editor/im/imaddress.h>
class KLineEdit;
class QToolButton;
class QComboBox;
namespace Akonadi
{
class MessagingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessagingWidget(QWidget *parent = Q_NULLPTR);
    ~MessagingWidget();

    void updateAddRemoveButton(bool addButtonEnabled);
    IMAddress imAddress() const;
    void setIMAddress(const IMAddress &address);

    void clearWidget();
Q_SIGNALS:
    void addWidget(MessagingWidget *);
    void removeWidget(MessagingWidget *);

private Q_SLOTS:
    void slotAddMessaging();
    void slotRemoveMessaging();

private:
    KLineEdit *mMessagingEdit;
    QToolButton *mAddButton;
    QToolButton *mRemoveButton;
    QComboBox *mProtocolCombo;
};
}
#endif // MESSAGINGWIDGET_H
