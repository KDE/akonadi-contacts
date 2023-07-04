/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mailwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>
#include <editor/generalinfoeditor/mail/mailtypecombobox.h>
#include <editor/widgets/preferredlineeditwidget.h>

using namespace Akonadi;
MailWidget::MailWidget(QWidget *parent)
    : QWidget(parent)
    , mMailEdit(new PreferredLineEditWidget(this))
    , mMailType(new Akonadi::MailTypeCombobox(this))
    , mAddButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins({});

    mMailEdit->setTrapReturnKey(true);
    mMailEdit->setPlaceholderText(i18n("Add an Email Account"));
    mMailEdit->setObjectName(QStringLiteral("mailedit"));
    layout->addWidget(mMailEdit);
    connect(mMailEdit, &PreferredLineEditWidget::preferredChanged, this, &MailWidget::slotPreferredChanged);

    mMailType->setObjectName(QStringLiteral("mailtype"));
    layout->addWidget(mMailType);

    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    mAddButton->setToolTip(i18n("Add an Email"));
    connect(mAddButton, &QToolButton::clicked, this, &MailWidget::slotAddMail);
    layout->addWidget(mAddButton);

    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    mRemoveButton->setToolTip(i18n("Remove Email"));
    connect(mRemoveButton, &QToolButton::clicked, this, &MailWidget::slotRemoveMail);
    layout->addWidget(mRemoveButton);
}

MailWidget::~MailWidget() = default;

void MailWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}

void MailWidget::clearWidget()
{
    mMailEdit->clear();
    mEmail = KContacts::Email();
    mMailType->setCurrentIndex(0);
}

void MailWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

void MailWidget::setMail(const KContacts::Email &email)
{
    mEmail = email;
    mMailEdit->setText(email.mail());
    mMailType->setCurrentIndex(mMailType->findData((int)email.type()));
    setPreferred(email.isPreferred());
}

KContacts::Email MailWidget::email()
{
    mEmail.setEmail(mMailEdit->text());
    mEmail.setType(KContacts::Email::Type(mMailType->currentData().toInt()));
    mEmail.setPreferred(mMailEdit->preferred());
    return mEmail;
}

void MailWidget::setPreferred(bool b)
{
    mMailEdit->setPreferred(b);
}

void MailWidget::setReadOnly(bool readOnly)
{
    mMailEdit->setReadOnly(readOnly);
    mMailType->setEnabled(!readOnly);
    mAddButton->setEnabled(!readOnly);
    mRemoveButton->setEnabled(!readOnly);
}

void MailWidget::slotAddMail()
{
    Q_EMIT addWidget(this);
}

void MailWidget::slotRemoveMail()
{
    Q_EMIT removeWidget(this);
}

#include "moc_mailwidget.cpp"
