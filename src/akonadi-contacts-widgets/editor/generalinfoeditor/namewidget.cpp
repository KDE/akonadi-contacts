/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "namewidget.h"
#include "nameeditdialog.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

using namespace Akonadi;

NameWidget::NameWidget(QWidget *parent)
    : QWidget(parent)
    , mNameEdit(new KLineEdit(this))
    , mButtonEdit(new QToolButton(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    auto label = new QLabel(i18n("Name"));
    label->setObjectName(QStringLiteral("namelabel"));
    topLayout->addWidget(label);

    auto lineLayout = new QHBoxLayout;
    lineLayout->setContentsMargins({});
    topLayout->addLayout(lineLayout);

    mNameEdit->setTrapReturnKey(true);
    lineLayout->addWidget(mNameEdit);
    setFocusProxy(mNameEdit);
    setFocusPolicy(Qt::StrongFocus);

    mButtonEdit->setText(i18n("..."));
    mButtonEdit->setToolTip(i18n("Edit Contact Name"));
    lineLayout->addWidget(mButtonEdit);

    connect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
    connect(mButtonEdit, &QToolButton::clicked, this, &NameWidget::slotOpenNameEditDialog);
}

NameWidget::~NameWidget() = default;

void NameWidget::setReadOnly(bool readOnly)
{
    mNameEdit->setReadOnly(readOnly);
    mButtonEdit->setEnabled(!readOnly);
}

void NameWidget::setDisplayType(DisplayNameEditWidget::DisplayType type)
{
    mDisplayType = type;
}

DisplayNameEditWidget::DisplayType NameWidget::displayType() const
{
    return mDisplayType;
}

void NameWidget::loadContact(const KContacts::Addressee &contact)
{
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
    contact.setFormattedName(mContact.formattedName());
}

void NameWidget::slotTextChanged(const QString &text)
{
    mContact.setNameFromString(text);

    Q_EMIT nameChanged(mContact);
}

void NameWidget::slotOpenNameEditDialog()
{
    QPointer<NameEditDialog> dlg = new NameEditDialog(this);
    dlg->loadContact(mContact);
    dlg->setDisplayType(mDisplayType);

    if (dlg->exec() == QDialog::Accepted) {
        dlg->storeContact(mContact);
        mDisplayType = dlg->displayType();
        disconnect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);
        mNameEdit->setText(mContact.assembledName());
        connect(mNameEdit, &QLineEdit::textChanged, this, &NameWidget::slotTextChanged);

        Q_EMIT nameChanged(mContact);
    }

    delete dlg;
}

#include "moc_namewidget.cpp"
