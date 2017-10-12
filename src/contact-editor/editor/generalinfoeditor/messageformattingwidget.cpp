/*
    This file is part of Contact Editor.

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
#include "editor/utils/utils.h"
#include <KLocalizedString>

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace ContactEditor;

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
    const QStringList listFormat {
        i18n("Default"), i18n("Plain Text"), i18n("HTML")
    };
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
    const QString mailAllowToRemoteContent = ContactEditor::Utils::loadCustom(contact, QStringLiteral("MailAllowToRemoteContent"));
    mAllowRemoteContent->setChecked(mailAllowToRemoteContent == QLatin1String("TRUE"));

    const QString mailPreferedFormatting = ContactEditor::Utils::loadCustom(contact, QStringLiteral("MailPreferedFormatting"));
    if (mailPreferedFormatting.isEmpty()) {
        mMailPreferFormatting->setCurrentIndex(0);
    } else if (mailPreferedFormatting == QLatin1String("TEXT")) {
        mMailPreferFormatting->setCurrentIndex(1);
    } else if (mailPreferedFormatting == QLatin1String("HTML")) {
        mMailPreferFormatting->setCurrentIndex(2);
    } else {
        mMailPreferFormatting->setCurrentIndex(0);
    }
}

void MessageFormattingWidget::storeContact(KContacts::Addressee &contact) const
{
    QString mailPreferedFormatting;
    const int index = mMailPreferFormatting->currentIndex();
    if (index == 0) {
        //Nothing => remove custom variable
    } else if (index == 1) {
        mailPreferedFormatting = QStringLiteral("TEXT");
    } else if (index == 2) {
        mailPreferedFormatting = QStringLiteral("HTML");
    }
    ContactEditor::Utils::storeCustom(contact, QLatin1String("MailPreferedFormatting"), mailPreferedFormatting);

    QString mailAllowToRemoteContent;
    if (mAllowRemoteContent->isChecked()) {
        mailAllowToRemoteContent = QLatin1String("TRUE");
    }
    ContactEditor::Utils::storeCustom(contact, QLatin1String("MailAllowToRemoteContent"), mailAllowToRemoteContent);
}

void MessageFormattingWidget::setReadOnly(bool readOnly)
{
    mMailPreferFormatting->setEnabled(!readOnly);
    mAllowRemoteContent->setEnabled(!readOnly);
}
