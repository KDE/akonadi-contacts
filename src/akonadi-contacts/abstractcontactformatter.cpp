/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "abstractcontactformatter.h"

#include <Akonadi/Item>
#include <KContacts/Addressee>

using namespace Akonadi;

class Akonadi::AbstractContactFormatterPrivate
{
public:
    KContacts::Addressee mContact;
    Akonadi::Item mItem;
    QVector<QVariantMap> mCustomFieldDescriptions;
};

AbstractContactFormatter::AbstractContactFormatter()
    : d(new AbstractContactFormatterPrivate)
{
}

AbstractContactFormatter::~AbstractContactFormatter() = default;

void AbstractContactFormatter::setContact(const KContacts::Addressee &contact)
{
    d->mContact = contact;
}

KContacts::Addressee AbstractContactFormatter::contact() const
{
    return d->mContact;
}

void AbstractContactFormatter::setItem(const Akonadi::Item &item)
{
    d->mItem = item;
}

Akonadi::Item AbstractContactFormatter::item() const
{
    return d->mItem;
}

void AbstractContactFormatter::setCustomFieldDescriptions(const QVector<QVariantMap> &descriptions)
{
    d->mCustomFieldDescriptions = descriptions;
}

QVector<QVariantMap> AbstractContactFormatter::customFieldDescriptions() const
{
    return d->mCustomFieldDescriptions;
}
