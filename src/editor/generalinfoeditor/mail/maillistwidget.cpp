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

#include "maillistwidget.h"
#include "mailwidgetlister.h"
#include <QLabel>
#include <QVBoxLayout>
#include <KLocalizedString>
#include <KContacts/Addressee>
using namespace Akonadi;

MailListWidget::MailListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->setMargin(0);
    topLayout->setSpacing(0);
    setLayout(topLayout);

    QLabel *label = new QLabel(i18n("Email"), this);
    label->setObjectName(QStringLiteral("emaillistlabel"));
    topLayout->addWidget(label);

    mMailWidgetLister = new Akonadi::MailWidgetLister(this);
    mMailWidgetLister->setObjectName(QStringLiteral("emailwidgetlister"));
    topLayout->addWidget(mMailWidgetLister);
}

MailListWidget::~MailListWidget()
{

}

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
    mMailWidgetLister->setEnabled(!readOnly);
}
