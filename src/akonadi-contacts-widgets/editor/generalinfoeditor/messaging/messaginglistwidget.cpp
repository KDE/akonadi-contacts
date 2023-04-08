/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messaginglistwidget.h"
#include "messagingwidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace ContactEditor;

MessagingListWidget::MessagingListWidget(QWidget *parent)
    : QWidget(parent)
    , mMessagingWidgetLister(new ContactEditor::MessagingWidgetLister(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18n("Messaging"), this);
    label->setObjectName(QStringLiteral("messaginglistlabel"));
    topLayout->addWidget(label);
    mMessagingWidgetLister->setObjectName(QStringLiteral("messagingwidgetlister"));
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
