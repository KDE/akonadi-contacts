/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messageformattingwidget.h"
#include "editor/utils/utils.h"
#include <KLocalizedString>

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace Akonadi;

MessageFormattingWidget::MessageFormattingWidget(QWidget *parent)
    : QWidget(parent)
    , mMailPreferFormatting(new QComboBox(this))
    , mAllowRemoteContent(new QCheckBox(i18n("Allow remote content in received HTML messages"), this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    auto label = new QLabel(i18nc("@label:textbox", "Show messages received from this contact as:"), this);
    label->setObjectName(QLatin1StringView("label"));
    topLayout->addWidget(label);

    mMailPreferFormatting->setObjectName(QLatin1StringView("mMailPreferFormatting"));
    topLayout->addWidget(mMailPreferFormatting);
    label->setBuddy(mMailPreferFormatting);
    const QStringList listFormat{i18n("Default"), i18n("Plain Text"), i18n("HTML")};
    mMailPreferFormatting->addItems(listFormat);

    mAllowRemoteContent->setObjectName(QLatin1StringView("mAllowRemoteContent"));
    topLayout->addWidget(mAllowRemoteContent);
}

MessageFormattingWidget::~MessageFormattingWidget() = default;

void MessageFormattingWidget::loadContact(const KContacts::Addressee &contact)
{
    const QString mailAllowToRemoteContent = Akonadi::Utils::loadCustom(contact, QStringLiteral("MailAllowToRemoteContent"));
    mAllowRemoteContent->setChecked(mailAllowToRemoteContent == QLatin1StringView("TRUE"));

    const QString mailPreferedFormatting = Akonadi::Utils::loadCustom(contact, QStringLiteral("MailPreferedFormatting"));
    if (mailPreferedFormatting.isEmpty()) {
        mMailPreferFormatting->setCurrentIndex(0);
    } else if (mailPreferedFormatting == QLatin1StringView("TEXT")) {
        mMailPreferFormatting->setCurrentIndex(1);
    } else if (mailPreferedFormatting == QLatin1StringView("HTML")) {
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
        // Nothing => remove custom variable
    } else if (index == 1) {
        mailPreferedFormatting = QStringLiteral("TEXT");
    } else if (index == 2) {
        mailPreferedFormatting = QStringLiteral("HTML");
    }
    Akonadi::Utils::storeCustom(contact, QStringLiteral("MailPreferedFormatting"), mailPreferedFormatting);

    QString mailAllowToRemoteContent;
    if (mAllowRemoteContent->isChecked()) {
        mailAllowToRemoteContent = QStringLiteral("TRUE");
    }
    Akonadi::Utils::storeCustom(contact, QStringLiteral("MailAllowToRemoteContent"), mailAllowToRemoteContent);
}

void MessageFormattingWidget::setReadOnly(bool readOnly)
{
    mMailPreferFormatting->setEnabled(!readOnly);
    mAllowRemoteContent->setEnabled(!readOnly);
}

#include "moc_messageformattingwidget.cpp"
