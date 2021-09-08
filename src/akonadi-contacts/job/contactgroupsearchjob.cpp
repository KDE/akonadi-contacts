/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupsearchjob.h"

#include <QStringList>
#include <akonadi/itemfetchscope.h>
#include <searchquery.h>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactGroupSearchJob::Private
{
public:
    int mLimit = -1;
};

ContactGroupSearchJob::ContactGroupSearchJob(QObject *parent)
    : ItemSearchJob(parent)
    , d(new Private)
{
    fetchScope().fetchFullPayload();
    d->mLimit = -1;

    setMimeTypes(QStringList() << KContacts::ContactGroup::mimeType());

    // by default search for all contact groups
    Akonadi::SearchQuery query;
    query.addTerm(ContactSearchTerm(ContactSearchTerm::All, QVariant(), SearchTerm::CondEqual));
    ItemSearchJob::setQuery(query);
}

ContactGroupSearchJob::~ContactGroupSearchJob()
{
    delete d;
}

void ContactGroupSearchJob::setQuery(Criterion criterion, const QString &value)
{
    // Exact match was the default in 4.4, so we have to keep it and ContactSearchJob has something
    // else as default
    setQuery(criterion, value, ExactMatch);
}

static Akonadi::SearchTerm::Condition matchType(ContactGroupSearchJob::Match match)
{
    switch (match) {
    case ContactGroupSearchJob::ExactMatch:
        return Akonadi::SearchTerm::CondEqual;
    case ContactGroupSearchJob::StartsWithMatch:
    case ContactGroupSearchJob::ContainsMatch:
        return Akonadi::SearchTerm::CondContains;
    }
    return Akonadi::SearchTerm::CondEqual;
}

void ContactGroupSearchJob::setQuery(Criterion criterion, const QString &value, Match match)
{
    Akonadi::SearchQuery query;
    if (criterion == Name) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Name, value, matchType(match)));
    }

    query.setLimit(d->mLimit);

    ItemSearchJob::setQuery(query);
}

void ContactGroupSearchJob::setLimit(int limit)
{
    d->mLimit = limit;
}

KContacts::ContactGroup::List ContactGroupSearchJob::contactGroups() const
{
    KContacts::ContactGroup::List contactGroups;
    const Akonadi::Item::List lstItems = items();
    for (const Item &item : lstItems) {
        if (item.hasPayload<KContacts::ContactGroup>()) {
            contactGroups.append(item.payload<KContacts::ContactGroup>());
        }
    }

    return contactGroups;
}
