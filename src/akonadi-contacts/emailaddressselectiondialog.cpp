/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectiondialog.h"
#include "recipientspicker/recipientspickerwidget.h"

#include <KConfigGroup>

#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

using namespace Akonadi;

class Akonadi::EmailAddressSelectionDialogPrivate
{
public:
    EmailAddressSelectionDialogPrivate(EmailAddressSelectionDialog *qq, QAbstractItemModel *model)
        : q(qq)
    {
        auto mainLayout = new QVBoxLayout(q);
        if (model) {
            mView = new RecipientsPickerWidget(true, model, q);
        } else {
            mView = new RecipientsPickerWidget(true, nullptr, q);
        }
        mainLayout->addWidget(mView);
        q->connect(mView->emailAddressSelectionWidget()->view(), &QTreeView::doubleClicked, q, &QDialog::accept);
        auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, q);
        QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
        okButton->setDefault(true);
        okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, q, &QDialog::accept);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, q, &QDialog::reject);

        mainLayout->addWidget(buttonBox);
        readConfig();
    }

    void readConfig()
    {
        KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("EmailAddressSelectionDialog"));
        const QSize size = group.readEntry("Size", QSize());
        if (size.isValid()) {
            q->resize(size);
        } else {
            q->resize(q->sizeHint().width(), q->sizeHint().height());
        }
    }

    void writeConfig()
    {
        KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("EmailAddressSelectionDialog"));
        group.writeEntry("Size", q->size());
    }

    EmailAddressSelectionDialog *const q;
    RecipientsPickerWidget *mView = nullptr;
};

EmailAddressSelectionDialog::EmailAddressSelectionDialog(QWidget *parent)
    : AbstractEmailAddressSelectionDialog(parent)
    , d(new EmailAddressSelectionDialogPrivate(this, nullptr))
{
}

EmailAddressSelectionDialog::EmailAddressSelectionDialog(QAbstractItemModel *model, QWidget *parent)
    : AbstractEmailAddressSelectionDialog(parent)
    , d(new EmailAddressSelectionDialogPrivate(this, model))
{
}

EmailAddressSelectionDialog::~EmailAddressSelectionDialog()
{
    d->writeConfig();
}

EmailAddressSelection::List EmailAddressSelectionDialog::selectedAddresses() const
{
    return d->mView->emailAddressSelectionWidget()->selectedAddresses();
}

EmailAddressSelectionWidget *EmailAddressSelectionDialog::view() const
{
    return d->mView->emailAddressSelectionWidget();
}
