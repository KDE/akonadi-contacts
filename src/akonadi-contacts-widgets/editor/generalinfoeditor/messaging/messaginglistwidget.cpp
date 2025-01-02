/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messaginglistwidget.h"
#include "messagingwidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace Akonadi;

MessagingListWidget::MessagingListWidget(QWidget *parent)
    : QWidget(parent)
    , mMessagingWidgetLister(new Akonadi::MessagingWidgetLister(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18nc("@label:textbox", "Messaging"), this);
    label->setObjectName(QLatin1StringView("messaginglistlabel"));
    topLayout->addWidget(label);
    mMessagingWidgetLister->setObjectName(QLatin1StringView("messagingwidgetlister"));
    topLayout->addWidget(mMessagingWidgetLister);
}

MessagingListWidget::~MessagingListWidget() = default;

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
    mMessagingWidgetLister->setReadOnly(readOnly);
}

#include "moc_messaginglistwidget.cpp"
