/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactsearchjob.h"
#include <Akonadi/SearchQuery>

#include <Akonadi/ItemFetchScope>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactSearchJob::Private
{
public:
    int mLimit = -1;
};

ContactSearchJob::ContactSearchJob(QObject *parent)
    : ItemSearchJob(parent)
    , d(new Private())
{
    fetchScope().fetchFullPayload();
    d->mLimit = -1;

    setMimeTypes(QStringList() << KContacts::Addressee::mimeType());

    // by default search for all contacts
    Akonadi::SearchQuery query;
    query.addTerm(ContactSearchTerm(ContactSearchTerm::All, QVariant(), SearchTerm::CondEqual));
    ItemSearchJob::setQuery(query);
}

ContactSearchJob::~ContactSearchJob()
{
    delete d;
}

static Akonadi::SearchTerm::Condition matchType(ContactSearchJob::Match match)
{
    switch (match) {
    case ContactSearchJob::ExactMatch:
        return Akonadi::SearchTerm::CondEqual;
    case ContactSearchJob::StartsWithMatch:
    case ContactSearchJob::ContainsWordBoundaryMatch:
    case ContactSearchJob::ContainsMatch:
        return Akonadi::SearchTerm::CondContains;
    }
    return Akonadi::SearchTerm::CondEqual;
}

void ContactSearchJob::setQuery(Criterion criterion, const QString &value, Match match)
{
    Akonadi::SearchQuery query(SearchTerm::RelOr);

    if (criterion == Name) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Name, value, matchType(match)));
    } else if (criterion == Email) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Email, value, matchType(match)));
    } else if (criterion == NickName) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Nickname, value, matchType(match)));
    } else if (criterion == NameOrEmail) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Name, value, matchType(match)));
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Email, value, matchType(match)));
    } else if (criterion == ContactUid) {
        query.addTerm(ContactSearchTerm(ContactSearchTerm::Uid, value, matchType(match)));
    }

    query.setLimit(d->mLimit);

    ItemSearchJob::setQuery(query);
}

void ContactSearchJob::setLimit(int limit)
{
    d->mLimit = limit;
}

KContacts::Addressee::List ContactSearchJob::contacts() const
{
    KContacts::Addressee::List contacts;

    const Akonadi::Item::List lstItems = items();
    for (const Item &item : lstItems) {
        if (item.hasPayload<KContacts::Addressee>()) {
            contacts.append(item.payload<KContacts::Addressee>());
        }
    }

    return contacts;
}
