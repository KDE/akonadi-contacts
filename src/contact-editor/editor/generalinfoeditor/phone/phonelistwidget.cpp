/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonelistwidget.h"
#include "phonewidgetlister.h"
#include <QLabel>
#include <QVBoxLayout>
#include <KLocalizedString>
#include <KContacts/Addressee>
using namespace ContactEditor;

PhoneListWidget::PhoneListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    QLabel *label = new QLabel(i18n("Phone"), this);
    label->setObjectName(QStringLiteral("phonelistlabel"));
    topLayout->addWidget(label);

    mPhoneWidgetLister = new ContactEditor::PhoneWidgetLister(this);
    mPhoneWidgetLister->setObjectName(QStringLiteral("phonewidgetlister"));
    topLayout->addWidget(mPhoneWidgetLister);
}

PhoneListWidget::~PhoneListWidget()
{
}

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
