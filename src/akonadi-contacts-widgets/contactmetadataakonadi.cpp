/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactmetadataakonadi_p.h"

#include "attributes/contactmetadataattribute_p.h"

#include <Akonadi/Item>

using namespace AkonadiContactWidgets;

ContactMetaDataAkonadi::ContactMetaDataAkonadi() = default;

ContactMetaDataAkonadi::~ContactMetaDataAkonadi() = default;

void ContactMetaDataAkonadi::load(const Akonadi::Item &contact)
{
    if (!contact.hasAttribute("contactmetadata")) {
        return;
    }
    const auto attribute = contact.attribute<Akonadi::ContactMetaDataAttribute>();
    const QVariantMap metaData = attribute->metaData();
    loadMetaData(metaData);
}

void ContactMetaDataAkonadi::store(Akonadi::Item &contact)
{
    auto attribute = contact.attribute<Akonadi::ContactMetaDataAttribute>(Akonadi::Item::AddIfMissing);

    attribute->setMetaData(storeMetaData());
}
