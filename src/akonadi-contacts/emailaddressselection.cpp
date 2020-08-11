/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselection.h"
#include "emailaddressselection_p.h"

#include <kcontacts/contactgroup.h>
#include <kmime/kmime_header_parsing.h>

using namespace Akonadi;

EmailAddressSelection::Private::Private()
    : QSharedData()
{
}

EmailAddressSelection::Private::Private(const Private &other)
    : QSharedData(other)
{
    mName = other.mName;
    mEmailAddress = other.mEmailAddress;
    mItem = other.mItem;
}

EmailAddressSelection::EmailAddressSelection()
    : d(new Private)
{
}

EmailAddressSelection::EmailAddressSelection(const EmailAddressSelection &other)
    : d(other.d)
{
}

EmailAddressSelection &EmailAddressSelection::operator=(const EmailAddressSelection &other)
{
    if (this != &other) {
        d = other.d;
    }

    return *this;
}

EmailAddressSelection::~EmailAddressSelection()
{
}

bool EmailAddressSelection::isValid() const
{
    return d->mItem.isValid();
}

QString EmailAddressSelection::name() const
{
    return d->mName;
}

QString EmailAddressSelection::email() const
{
    return d->mEmailAddress;
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
