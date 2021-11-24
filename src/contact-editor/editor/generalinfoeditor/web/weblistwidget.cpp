/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "weblistwidget.h"
#include "webwidgetlister.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>

using namespace ContactEditor;

WebListWidget::WebListWidget(QWidget *parent)
    : QWidget(parent)
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setSpacing(0);

    auto label = new QLabel(i18n("Web"), this);
    label->setObjectName(QStringLiteral("weblistlabel"));
    topLayout->addWidget(label);

    mWebWidgetLister = new ContactEditor::WebWidgetLister(this);
    mWebWidgetLister->setObjectName(QStringLiteral("webwidgetlister"));
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
