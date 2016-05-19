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

#include "namewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <KLineEdit>
#include <QToolButton>
#include "nameeditdialog.h"

using namespace Akonadi;

NameWidget::NameWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setMargin(0);
    QLabel *label = new QLabel(i18n("Name"));
    label->setObjectName(QStringLiteral("namelabel"));
    topLayout->addWidget(label);

    QHBoxLayout *lineLayout = new QHBoxLayout;
    lineLayout->setMargin(0);
    topLayout->addLayout(lineLayout);

    mNameEdit = new KLineEdit;
    mNameEdit->setTrapReturnKey(true);
    lineLayout->addWidget(mNameEdit);
    setFocusProxy(mNameEdit);
    setFocusPolicy(Qt::StrongFocus);

    mButtonEdit = new QToolButton;
    mButtonEdit->setText(i18n("..."));
    mButtonEdit->setToolTip(i18n("Edit Contact Name"));
    lineLayout->addWidget(mButtonEdit);

    connect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
    connect(mButtonEdit, &QToolButton::clicked, this, &NameWidget::slotOpenNameEditDialog);
}

NameWidget::~NameWidget()
{

}

void NameWidget::setReadOnly(bool readOnly)
{
    mNameEdit->setReadOnly(readOnly);
    mButtonEdit->setEnabled(!readOnly);
}

void NameWidget::loadContact(const KContacts::Addressee &contact)
{
    qDebug() << "contact " << contact.assembledName();
    mContact = contact;

    disconnect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
    mNameEdit->setText(contact.assembledName());
    connect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
}

void NameWidget::storeContact(KContacts::Addressee &contact) const
{
    contact.setPrefix(mContact.prefix());
    contact.setGivenName(mContact.givenName());
    contact.setAdditionalName(mContact.additionalName());
    contact.setFamilyName(mContact.familyName());
    contact.setSuffix(mContact.suffix());
}

void NameWidget::slotTextChanged(const QString &text)
{
    mContact.setNameFromString(text);

    Q_EMIT nameChanged(mContact);
}

void NameWidget::slotOpenNameEditDialog()
{
    QPointer<NameEditDialog> dlg = new NameEditDialog(this);

    dlg->setPrefix(mContact.prefix());
    dlg->setGivenName(mContact.givenName());
    dlg->setAdditionalName(mContact.additionalName());
    dlg->setFamilyName(mContact.familyName());
    dlg->setSuffix(mContact.suffix());

    if (dlg->exec() == QDialog::Accepted) {
        mContact.setPrefix(dlg->prefix());
        mContact.setGivenName(dlg->givenName());
        mContact.setAdditionalName(dlg->additionalName());
        mContact.setFamilyName(dlg->familyName());
        mContact.setSuffix(dlg->suffix());

        disconnect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
        mNameEdit->setText(mContact.assembledName());
        connect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);

        Q_EMIT nameChanged(mContact);
    }

    delete dlg;
}

