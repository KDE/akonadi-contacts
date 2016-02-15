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

#include "messagingwidget.h"
#include "../../im/improtocols.h"
#include <KComboBox>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <KLineEdit>
#include <QToolButton>
#include <QDebug>

using namespace Akonadi;
MessagingWidget::MessagingWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);


    mMessagingEdit = new KLineEdit(this);
    mMessagingEdit->setTrapReturnKey(true);
    mMessagingEdit->setPlaceholderText(i18n("Add an identifier"));
    mMessagingEdit->setObjectName(QStringLiteral("phonenumber"));
    layout->addWidget(mMessagingEdit);


    mProtocolCombo = new KComboBox(this);
    mProtocolCombo->setObjectName(QStringLiteral("protocol"));
    mProtocolCombo->addItem(i18nc("@item:inlistbox select from a list of IM protocols",
                                  "Select..."));
    layout->addWidget(mProtocolCombo);

    const QStringList protocols = IMProtocols::self()->protocols();
    foreach (const QString &protocol, protocols) {
        mProtocolCombo->addItem(QIcon::fromTheme(IMProtocols::self()->icon(protocol)),
                                IMProtocols::self()->name(protocol),
                                protocol);
    }

    mAddButton = new QToolButton(this);
    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &MessagingWidget::slotAddMessaging);
    layout->addWidget(mAddButton);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    connect(mRemoveButton, &QToolButton::clicked, this, &MessagingWidget::slotRemoveMessaging);
    layout->addWidget(mRemoveButton);
}

MessagingWidget::~MessagingWidget()
{

}

void MessagingWidget::setIMAddress(const IMAddress &address)
{
    mProtocolCombo->setCurrentIndex(
        IMProtocols::self()->protocols().indexOf(address.protocol()) + 1);
    mMessagingEdit->setText(address.name());
}

IMAddress MessagingWidget::imAddress() const
{
    return IMAddress(mProtocolCombo->itemData(mProtocolCombo->currentIndex()).toString(),
                     mMessagingEdit->text().trimmed(), false);
}

void MessagingWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

void MessagingWidget::slotAddMessaging()
{
    Q_EMIT addWidget(this);
}

void MessagingWidget::slotRemoveMessaging()
{
    Q_EMIT removeWidget(this);
}

void MessagingWidget::clearWidget()
{
    mProtocolCombo->setCurrentIndex(0);
    mMessagingEdit->clear();
}
