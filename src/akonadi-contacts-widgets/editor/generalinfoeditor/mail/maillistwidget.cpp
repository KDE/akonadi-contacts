/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "maillistwidget.h"
#include "mailwidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace Akonadi;

MailListWidget::MailListWidget(QWidget *parent)
    : QWidget(parent)
    , mMailWidgetLister(new Akonadi::MailWidgetLister(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18n("Email"), this);
    label->setObjectName(QStringLiteral("emaillistlabel"));
    topLayout->addWidget(label);

    mMailWidgetLister->setObjectName(QStringLiteral("emailwidgetlister"));
    topLayout->addWidget(mMailWidgetLister);
}

MailListWidget::~MailListWidget() = default;

void MailListWidget::loadContact(const KContacts::Addressee &contact)
{
    mMailWidgetLister->loadContact(contact);
}

void MailListWidget::storeContact(KContacts::Addressee &contact) const
{
    mMailWidgetLister->storeContact(contact);
}

void MailListWidget::setReadOnly(bool readOnly)
{
    mMailWidgetLister->setReadOnly(readOnly);
}

#include "moc_maillistwidget.cpp"
