/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2020 Laurent Montel <montel.org>

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

#include "mailwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>
#include <editor/generalinfoeditor/mail/mailtypecombobox.h>
#include <editor/widgets/preferredlineeditwidget.h>

using namespace ContactEditor;
MailWidget::MailWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    mMailEdit = new PreferredLineEditWidget(this);
    mMailEdit->setTrapReturnKey(true);
    mMailEdit->setPlaceholderText(i18n("Add an Email Account"));
    mMailEdit->setObjectName(QStringLiteral("mailedit"));
    layout->addWidget(mMailEdit);
    connect(mMailEdit, &PreferredLineEditWidget::preferredChanged, this, &MailWidget::slotPreferredChanged);

    mMailType = new ContactEditor::MailTypeCombobox(this);
    mMailType->setObjectName(QStringLiteral("mailtype"));
    layout->addWidget(mMailType);

    mAddButton = new QToolButton(this);
    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    mAddButton->setToolTip(i18n("Add an Email"));
    connect(mAddButton, &QToolButton::clicked, this, &MailWidget::slotAddMail);
    layout->addWidget(mAddButton);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    mRemoveButton->setToolTip(i18n("Remove Email"));
    connect(mRemoveButton, &QToolButton::clicked, this, &MailWidget::slotRemoveMail);
    layout->addWidget(mRemoveButton);
}

MailWidget::~MailWidget()
{
}

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
