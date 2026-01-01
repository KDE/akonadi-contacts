/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonewidget.h"
#include "editor/widgets/preferredlineeditwidget.h"
#include "phonecomboboxtype.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>

#include <QHBoxLayout>
#include <QToolButton>

using namespace Akonadi;
PhoneWidget::PhoneWidget(QWidget *parent)
    : QWidget(parent)
    , mPhoneNumberEdit(new PreferredLineEditWidget(this))
    , mAddButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
    , mPhoneType(new PhoneComboBoxType(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins({});

    KLineEditEventHandler::catchReturnKey(mPhoneNumberEdit);
    mPhoneNumberEdit->setPlaceholderText(i18nc("@info:placeholder", "Add a Phone Number"));
    mPhoneNumberEdit->setObjectName(QLatin1StringView("phonenumber"));
    layout->addWidget(mPhoneNumberEdit);
    connect(mPhoneNumberEdit, &PreferredLineEditWidget::preferredChanged, this, &PhoneWidget::slotPreferredChanged);

    mPhoneType->setObjectName(QLatin1StringView("phonetype"));
    layout->addWidget(mPhoneType);

    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setToolTip(i18nc("@info:tooltip", "Add a Phone Number"));
    mAddButton->setObjectName(QLatin1StringView("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &PhoneWidget::slotAddPhone);
    layout->addWidget(mAddButton);

    mRemoveButton->setObjectName(QLatin1StringView("removebutton"));
    mRemoveButton->setToolTip(i18nc("@info:tooltip", "Remove Phone Number"));
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mRemoveButton, &QToolButton::clicked, this, &PhoneWidget::slotRemovePhone);
    layout->addWidget(mRemoveButton);
}

PhoneWidget::~PhoneWidget() = default;

void PhoneWidget::updateAddRemoveButton(bool addButtonEnabled, bool removeButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
    mRemoveButton->setEnabled(removeButtonEnabled);
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

#include "moc_phonewidget.cpp"
