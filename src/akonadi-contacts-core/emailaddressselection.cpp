/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselection.h"
#include "emailaddressselection_p.h"

#include <KContacts/ContactGroup>
#include <KMime/Types>

using namespace Akonadi;

EmailAddressSelectionPrivate::EmailAddressSelectionPrivate() = default;

EmailAddressSelectionPrivate::EmailAddressSelectionPrivate(const EmailAddressSelectionPrivate &other) = default;

EmailAddressSelection::EmailAddressSelection()
    : d(new EmailAddressSelectionPrivate)
{
}

EmailAddressSelection::EmailAddressSelection(const EmailAddressSelection &other) = default;

EmailAddressSelection &EmailAddressSelection::operator=(const EmailAddressSelection &other) = default;

EmailAddressSelection::~EmailAddressSelection() = default;

bool EmailAddressSelection::isValid() const
{
    return d->mItem.isValid();
}

QString EmailAddressSelection::name() const
{
    return d->mName;
}

void EmailAddressSelection::setName(const QString &name)
{
    d->mName = name;
}

QString EmailAddressSelection::email() const
{
    return d->mEmailAddress;
}

void EmailAddressSelection::setEmail(const QString &email)
{
    d->mEmailAddress = email;
}

QString EmailAddressSelection::quotedEmail() const
{
    if (d->mItem.hasPayload<KContacts::ContactGroup>()) {
        if (d->mEmailAddress == d->mName) {
            return d->mName;
        }
    }

    KMime::Types::Mailbox mailbox;
    mailbox.setAddress(d->mEmailAddress.toUtf8());
    mailbox.setName(d->mName);

    return mailbox.prettyAddress(KMime::Types::Mailbox::QuoteWhenNecessary);
}

Akonadi::Item EmailAddressSelection::item() const
{
    return d->mItem;
}

void EmailAddressSelection::setItem(const Item &item)
{
    d->mItem = item;
}
