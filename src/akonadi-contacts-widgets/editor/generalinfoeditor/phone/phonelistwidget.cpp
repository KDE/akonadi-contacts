/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonelistwidget.h"
#include "phonewidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace ContactEditor;

PhoneListWidget::PhoneListWidget(QWidget *parent)
    : QWidget(parent)
    , mPhoneWidgetLister(new ContactEditor::PhoneWidgetLister(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18n("Phone"), this);
    label->setObjectName(QStringLiteral("phonelistlabel"));
    topLayout->addWidget(label);

    mPhoneWidgetLister->setObjectName(QStringLiteral("phonewidgetlister"));
    topLayout->addWidget(mPhoneWidgetLister);
}

PhoneListWidget::~PhoneListWidget() = default;

void PhoneListWidget::loadContact(const KContacts::Addressee &contact)
{
    mPhoneWidgetLister->loadContact(contact);
}

void PhoneListWidget::storeContact(KContacts::Addressee &contact) const
{
    mPhoneWidgetLister->storeContact(contact);
}

void PhoneListWidget::setReadOnly(bool readOnly)
{
    mPhoneWidgetLister->setReadOnly(readOnly);
}

#include "moc_phonelistwidget.cpp"
