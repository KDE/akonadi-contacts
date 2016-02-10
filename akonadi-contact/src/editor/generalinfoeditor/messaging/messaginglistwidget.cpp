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

#include "messaginglistwidget.h"
#include "messagingwidgetlister.h"
#include <QLabel>
#include <QVBoxLayout>
#include <KLocalizedString>
#include <KContacts/Addressee>
using namespace Akonadi;

MessagingListWidget::MessagingListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->setMargin(0);
    topLayout->setSpacing(0);
    setLayout(topLayout);

    QLabel *label = new QLabel(i18n("Messaging"), this);
    label->setObjectName(QStringLiteral("messaginglistlabel"));
    topLayout->addWidget(label);

    mMessagingWidgetLister = new Akonadi::MessagingWidgetLister(this);
    mMessagingWidgetLister->setObjectName(QStringLiteral("messagingwidgetlister"));
    topLayout->addWidget(mMessagingWidgetLister);
}

MessagingListWidget::~MessagingListWidget()
{

}

void MessagingListWidget::loadContact(const KContacts::Addressee &contact)
{
    mMessagingWidgetLister->loadContact(contact);
}

void MessagingListWidget::storeContact(KContacts::Addressee &contact) const
{
    mMessagingWidgetLister->storeContact(contact);
}

void MessagingListWidget::setReadOnly(bool readOnly)
{
    mMessagingWidgetLister->setEnabled(!readOnly);
}
