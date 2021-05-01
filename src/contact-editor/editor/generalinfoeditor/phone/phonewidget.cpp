/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonewidget.h"
#include "editor/widgets/preferredlineeditwidget.h"
#include "phonecomboboxtype.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QToolButton>

using namespace ContactEditor;
PhoneWidget::PhoneWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    mPhoneNumberEdit = new PreferredLineEditWidget(this);
    mPhoneNumberEdit->setTrapReturnKey(true);
    mPhoneNumberEdit->setPlaceholderText(i18n("Add a Phone Number"));
    mPhoneNumberEdit->setObjectName(QStringLiteral("phonenumber"));
    layout->addWidget(mPhoneNumberEdit);
    connect(mPhoneNumberEdit, &PreferredLineEditWidget::preferredChanged, this, &PhoneWidget::slotPreferredChanged);

    mPhoneType = new PhoneComboBoxType(this);
    mPhoneType->setObjectName(QStringLiteral("phonetype"));
    layout->addWidget(mPhoneType);

    mAddButton = new QToolButton(this);
    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setToolTip(i18n("Add a Phone Number"));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &PhoneWidget::slotAddPhone);
    layout->addWidget(mAddButton);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    mRemoveButton->setToolTip(i18n("Remove Phone Number"));
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mRemoveButton, &QToolButton::clicked, this, &PhoneWidget::slotRemovePhone);
    layout->addWidget(mRemoveButton);
}

PhoneWidget::~PhoneWidget()
{
}

void PhoneWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

KContacts::PhoneNumber PhoneWidget::storePhone()
{
    KContacts::PhoneNumber number;
    number.setNumber(mPhoneNumberEdit->text());
    KContacts::PhoneNumber::Type currentType = mPhoneType->type();
    if (mPhoneNumberEdit->preferred()) {
        currentType |= KContacts::PhoneNumber::Pref;
    }
    number.setType(currentType);
    return number;
}

void PhoneWidget::loadPhone(const KContacts::PhoneNumber &number)
{
    mPhoneNumberEdit->setText(number.number());
    KContacts::PhoneNumber::Type currentType = number.type();
    mPhoneType->setType(number.type() & ~KContacts::PhoneNumber::Pref);
    mPhoneNumberEdit->setPreferred(currentType & KContacts::PhoneNumber::Pref);
}

void PhoneWidget::slotAddPhone()
{
    Q_EMIT addWidget(this);
}

void PhoneWidget::slotRemovePhone()
{
    Q_EMIT removeWidget(this);
}

void PhoneWidget::clearWidget()
{
    mPhoneNumberEdit->clear();
    mPhoneType->resetToDefault();
}

void PhoneWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}

void PhoneWidget::setPreferred(bool b)
{
    mPhoneNumberEdit->setPreferred(b);
}

void PhoneWidget::setReadOnly(bool readOnly)
{
    mPhoneNumberEdit->setReadOnly(readOnly);
    mAddButton->setEnabled(!readOnly);
    mRemoveButton->setEnabled(!readOnly);
    mPhoneType->setEnabled(!readOnly);
}
