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

#include "mailwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <KLineEdit>
#include <QToolButton>
#include <QComboBox>
#include <editor/widgets/akonadicontactcombobox.h>
#include <editor/widgets/preferredlineeditwidget.h>
#include <QDebug>

using namespace Akonadi;
MailWidget::MailWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    mMailEdit = new PreferredLineEditWidget(this);
    mMailEdit->setTrapReturnKey(true);
    mMailEdit->setPlaceholderText(i18n("Add an Email Account"));
    mMailEdit->setObjectName(QStringLiteral("mailedit"));
    layout->addWidget(mMailEdit);
    connect(mMailEdit, &PreferredLineEditWidget::preferredChanged, this, &MailWidget::slotPreferredChanged);

    mMailType = new Akonadi::AkonadiContactComboBox(this);
    mMailType->setObjectName(QStringLiteral("mailtype"));
    mMailType->addItem(i18n("Select..."), QString());
    mMailType->addItem(i18n("Home"), QStringLiteral("HOME"));
    mMailType->addItem(i18n("Work"), QStringLiteral("WORK"));
    mMailType->addItem(i18n("Other"), QStringLiteral("OTHER"));
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
    const QMap<QString, QStringList> parameters = mEmail.parameters();
    const QStringList value = parameters.value(QStringLiteral("type"));
    if (value.contains(QStringLiteral("PREF"))) {
        setPreferred(true);
    }
}

KContacts::Email MailWidget::email()
{
    mEmail.setEmail(mMailEdit->text());
    QMap<QString, QStringList> parameters = mEmail.parameters();
    QStringList value = parameters.value(QStringLiteral("type"));
    const QString newType = mMailType->currentData().toString();
    if (!newType.isEmpty()) {
        if (!value.contains(newType)) {
            value.append(newType);
        }
        if (!mOldType.isEmpty()) {
            //TODO remove old type.
            value.removeAll(mOldType);
        }
    }
    if (mMailEdit->preferred()) {
        if (!value.contains(QStringLiteral("PREF"))) {
            value.append(QStringLiteral("PREF"));
        }
    } else {
        if (value.contains(QStringLiteral("PREF"))) {
            value.removeAll(QStringLiteral("PREF"));
        }
    }
    parameters.insert(QStringLiteral("type"), value);
    mEmail.setParameters(parameters);
    return mEmail;
}

void MailWidget::setPreferred(bool b)
{
    mMailEdit->setPreferred(b);
}

void MailWidget::slotAddMail()
{
    Q_EMIT addWidget(this);
}

void MailWidget::slotRemoveMail()
{
    Q_EMIT removeWidget(this);
}
