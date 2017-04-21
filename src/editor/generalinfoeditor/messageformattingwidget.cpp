/*
    This file is part of Akonadi Contact.

    Copyright (C) 2017 Laurent Montel <montel@kde.org>

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

#include "messageformattingwidget.h"
#include <KLocalizedString>

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

MessageFormattingWidget::MessageFormattingWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setMargin(0);
    QLabel *label = new QLabel(i18n("Show messages received from this contact as:"), this);
    label->setObjectName(QStringLiteral("label"));
    topLayout->addWidget(label);

    mMailPreferFormatting = new QComboBox(this);
    mMailPreferFormatting->setObjectName(QStringLiteral("mMailPreferFormatting"));
    topLayout->addWidget(mMailPreferFormatting);
    label->setBuddy(mMailPreferFormatting);
    const QStringList listFormat {i18n("Default"), i18n("Plain Text"), i18n("HTML")};
    mMailPreferFormatting->addItems(listFormat);

    mAllowRemoteContent = new QCheckBox(i18n("Allow remote content in received HTML messages"), this);
    mAllowRemoteContent->setObjectName(QStringLiteral("mAllowRemoteContent"));
    topLayout->addWidget(mAllowRemoteContent);
}

MessageFormattingWidget::~MessageFormattingWidget()
{

}

void MessageFormattingWidget::loadContact(const KContacts::Addressee &contact)
{

}

void MessageFormattingWidget::storeContact(KContacts::Addressee &contact) const
{

}

void MessageFormattingWidget::setReadOnly(bool readOnly)
{
    mMailPreferFormatting->setEnabled(!readOnly);
    mAllowRemoteContent->setEnabled(!readOnly);
}
