/*
    SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressrequester.h"

#include "emailaddressselectiondialog.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QIcon>

#include <QHBoxLayout>
#include <QPushButton>
#include <QTreeView>

using namespace Akonadi;

class Q_DECL_HIDDEN Akonadi::EmailAddressRequester::Private
{
public:
    Private(EmailAddressRequester *qq)
        : q(qq)
    {
    }

    void slotAddressBook();

    EmailAddressRequester *const q;
    KLineEdit *mLineEdit = nullptr;
};

void EmailAddressRequester::Private::slotAddressBook()
{
    QPointer<Akonadi::EmailAddressSelectionDialog> dlg = new Akonadi::EmailAddressSelectionDialog(q);
    dlg->view()->view()->setSelectionMode(QAbstractItemView::MultiSelection);
    if (!dlg->exec()) {
        delete dlg;
        return;
    }

    QStringList addressList;
    const auto selectedAddresses = dlg->selectedAddresses();
    addressList.reserve(selectedAddresses.size());
    for (const Akonadi::EmailAddressSelection &selection : selectedAddresses) {
        addressList << selection.quotedEmail();
    }

    QString text = mLineEdit->text().trimmed();

    if (!text.isEmpty()) {
        if (!text.endsWith(QLatin1Char(','))) {
            text += QLatin1String(", ");
        } else {
            text += QLatin1Char(' ');
        }
    }

    mLineEdit->setText(text + addressList.join(QLatin1Char(',')));
    delete dlg;
}

EmailAddressRequester::EmailAddressRequester(QWidget *parent)
    : QWidget(parent)
    , d(new Private(this))
{
    auto *layout = new QHBoxLayout(this);
    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    d->mLineEdit = new KLineEdit(this);
    d->mLineEdit->setClearButtonEnabled(true);
    d->mLineEdit->setTrapReturnKey(true);
    layout->addWidget(d->mLineEdit, 1);

    auto *button = new QPushButton(this);
    button->setIcon(QIcon::fromTheme(QStringLiteral("help-contents")));
    button->setFixedHeight(d->mLineEdit->sizeHint().height());
    button->setToolTip(i18n("Open Address Book"));
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, [this]() {
        d->slotAddressBook();
    });
    connect(d->mLineEdit, &KLineEdit::textChanged, this, &EmailAddressRequester::textChanged);
}

EmailAddressRequester::~EmailAddressRequester()
{
    delete d;
}

void EmailAddressRequester::clear()
{
    d->mLineEdit->clear();
}

void EmailAddressRequester::setText(const QString &text)
{
    d->mLineEdit->setText(text);
}

QString EmailAddressRequester::text() const
{
    return d->mLineEdit->text();
}

KLineEdit *EmailAddressRequester::lineEdit() const
{
    return d->mLineEdit;
}

#include "moc_emailaddressrequester.cpp"
