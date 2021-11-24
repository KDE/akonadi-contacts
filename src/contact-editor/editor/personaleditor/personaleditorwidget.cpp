/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "personaleditorwidget.h"
#include "../utils/utils.h"

#include <KLineEdit>
#include <KLocalizedString>
#include <QGridLayout>
#include <QLabel>

#include "dateeditwidget.h"

#include <KContacts/Addressee>

using namespace ContactEditor;

PersonalEditorWidget::PersonalEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QGridLayout(this);
    auto label = new QLabel(i18nc("@label The birthdate of a contact", "Birthdate:"));
    mainLayout->addWidget(label, 0, 0);

    mBirthdateWidget = new DateEditWidget(DateEditWidget::Birthday);
    label->setBuddy(mBirthdateWidget);
    mainLayout->addWidget(mBirthdateWidget, 1, 0);

    label = new QLabel(i18nc("@label The wedding anniversary of a contact", "Anniversary:"));
    mainLayout->addWidget(label, 0, 1);

    mAnniversaryWidget = new DateEditWidget(DateEditWidget::Anniversary);
    label->setBuddy(mAnniversaryWidget);
    mainLayout->addWidget(mAnniversaryWidget, 1, 1);

    label = new QLabel(i18nc("@label The partner's name of a contact", "Partner's name:"));
    mainLayout->addWidget(label, 0, 2);

    mPartnerWidget = new KLineEdit;
    mPartnerWidget->setPlaceholderText(i18n("Add name"));
    mPartnerWidget->setTrapReturnKey(true);
    label->setBuddy(mPartnerWidget);
    mainLayout->addWidget(mPartnerWidget, 1, 2);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(2, 1);

    mainLayout->setRowStretch(2, 1);
}

PersonalEditorWidget::~PersonalEditorWidget() = default;

void PersonalEditorWidget::loadContact(const KContacts::Addressee &contact)
{
    mBirthdateWidget->setDate(contact.birthday().date());
    mAnniversaryWidget->setDate(contact.anniversary());

    // family group
    mPartnerWidget->setText(contact.spousesName());
}

void PersonalEditorWidget::storeContact(KContacts::Addressee &contact)
{
    contact.setBirthday(mBirthdateWidget->date());
    contact.setAnniversary(mAnniversaryWidget->date());

    // family group
    contact.setSpousesName(mPartnerWidget->text().trimmed());
}

void PersonalEditorWidget::setReadOnly(bool readOnly)
{
    // widgets from dates group
    mBirthdateWidget->setReadOnly(readOnly);
    mAnniversaryWidget->setReadOnly(readOnly);

    // widgets from family group
    mPartnerWidget->setReadOnly(readOnly);
}
