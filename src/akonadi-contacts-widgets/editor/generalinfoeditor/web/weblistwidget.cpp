/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "weblistwidget.h"
#include "webwidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>

using namespace Akonadi;

WebListWidget::WebListWidget(QWidget *parent)
    : QWidget(parent)
    , mWebWidgetLister(new Akonadi::WebWidgetLister(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18nc("@label:textbox", "Web"), this);
    label->setObjectName(QLatin1StringView("weblistlabel"));
    topLayout->addWidget(label);

    mWebWidgetLister->setObjectName(QLatin1StringView("webwidgetlister"));
    topLayout->addWidget(mWebWidgetLister);
}

WebListWidget::~WebListWidget() = default;

void WebListWidget::loadContact(const KContacts::Addressee &contact)
{
    mWebWidgetLister->loadContact(contact);
}

void WebListWidget::storeContact(KContacts::Addressee &contact) const
{
    mWebWidgetLister->storeContact(contact);
}

void WebListWidget::setReadOnly(bool readOnly)
{
    mWebWidgetLister->setReadOnly(readOnly);
}

#include "moc_weblistwidget.cpp"
