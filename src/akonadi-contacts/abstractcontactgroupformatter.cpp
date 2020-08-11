/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "abstractcontactgroupformatter.h"

#include <item.h>
#include <kcontacts/contactgroup.h>

using namespace Akonadi;

class Q_DECL_HIDDEN AbstractContactGroupFormatter::Private
{
public:
    KContacts::ContactGroup mContactGroup;
    Akonadi::Item mItem;
    QVector<QVariantMap> mAdditionalFields;
};

AbstractContactGroupFormatter::AbstractContactGroupFormatter()
    : d(new Private)
{
}

AbstractContactGroupFormatter::~AbstractContactGroupFormatter()
{
    delete d;
}

void AbstractContactGroupFormatter::setContactGroup(const KContacts::ContactGroup &group)
{
    d->mContactGroup = group;
}

KContacts::ContactGroup AbstractContactGroupFormatter::contactGroup() const
{
    return d->mContactGroup;
}

void AbstractContactGroupFormatter::setItem(const Akonadi::Item &item)
{
    d->mItem = item;
}

Akonadi::Item AbstractContactGroupFormatter::item() const
{
    return d->mItem;
}

void AbstractContactGroupFormatter::setAdditionalFields(const QVector<QVariantMap> &fields)
{
    d->mAdditionalFields = fields;
}

QVector<QVariantMap> AbstractContactGroupFormatter::additionalFields() const
{
    return d->mAdditionalFields;
}
