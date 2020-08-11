/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactsfilterproxymodel.h"

#include "contactstreemodel.h"

#include <entitytreemodel.h>
#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>

using namespace Akonadi;

static bool contactMatchesFilter(const KContacts::Addressee &contact, const QString &filterString, ContactsFilterProxyModel::MatchFilterContactFlag flag);
static bool contactGroupMatchesFilter(const KContacts::ContactGroup &group, const QString &filterString);


class Q_DECL_HIDDEN ContactsFilterProxyModel::Private
{
public:
    Private()
        : flags({})
        , matchFilterFlag(ContactsFilterProxyModel::MatchFilterContactFlag::All)
        , mExcludeVirtualCollections(false)
    {
    }

    QString mFilter;
    ContactsFilterProxyModel::FilterFlags flags;
    ContactsFilterProxyModel::MatchFilterContactFlag matchFilterFlag;
    bool mExcludeVirtualCollections;
};

ContactsFilterProxyModel::ContactsFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d(new Private)
{
    // contact names should be sorted correctly
    setSortLocaleAware(true);
    setDynamicSortFilter(true);
}

ContactsFilterProxyModel::~ContactsFilterProxyModel()
{
    delete d;
}

void ContactsFilterProxyModel::setFilterString(const QString &filter)
{
    d->mFilter = filter;
    invalidateFilter();
}

bool ContactsFilterProxyModel::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    const QModelIndex index = sourceModel()->index(row, 0, parent);
    if (d->mExcludeVirtualCollections) {
        const Akonadi::Collection collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
        if (collection.isValid() && collection.isVirtual()) {
            return false;
        }
    }

    if ((d->mFilter.isEmpty()) && (!(d->flags & ContactsFilterProxyModel::HasEmail))) {
        return true;
    }

    const Akonadi::Item item = index.data(Akonadi::EntityTreeModel::ItemRole).value<Akonadi::Item>();

    if (item.hasPayload<KContacts::Addressee>()) {
        const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
        if (d->flags & ContactsFilterProxyModel::HasEmail) {
            if (contact.emails().isEmpty()) {
                return false;
            }
        }
        if (!d->mFilter.isEmpty()) {
            return contactMatchesFilter(contact, d->mFilter, d->matchFilterFlag);
        }
    } else {
        if (!d->mFilter.isEmpty()) {
            if (item.hasPayload<KContacts::ContactGroup>()) {
                const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
                return contactGroupMatchesFilter(group, d->mFilter);
            }
        }
    }

    return true;
}

bool ContactsFilterProxyModel::lessThan(const QModelIndex &leftIndex, const QModelIndex &rightIndex) const
{
    const QDate leftDate = leftIndex.data(ContactsTreeModel::DateRole).toDate();
    const QDate rightDate = rightIndex.data(ContactsTreeModel::DateRole).toDate();
    if (leftDate.isValid() && rightDate.isValid()) {
        if (leftDate.month() < rightDate.month()) {
            return true;
        } else if (leftDate.month() == rightDate.month()) {
            if (leftDate.day() < rightDate.day()) {
                return true;
            }
        } else {
            return false;
        }
    }

    return QSortFilterProxyModel::lessThan(leftIndex, rightIndex);
}

void ContactsFilterProxyModel::setMatchFilterContactFlag(ContactsFilterProxyModel::MatchFilterContactFlag flag)
{
    d->matchFilterFlag = flag;
}

void ContactsFilterProxyModel::setFilterFlags(ContactsFilterProxyModel::FilterFlags flags)
{
    d->flags = flags;
}

void ContactsFilterProxyModel::setExcludeVirtualCollections(bool exclude)
{
    if (exclude != d->mExcludeVirtualCollections) {
        d->mExcludeVirtualCollections = exclude;
        invalidateFilter();
    }
}

Qt::ItemFlags ContactsFilterProxyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        // Don't crash
        return Qt::NoItemFlags;
    }
    const Akonadi::Collection collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (collection.isValid()) {
        return QSortFilterProxyModel::flags(index) & ~(Qt::ItemIsSelectable);
    }
    return QSortFilterProxyModel::flags(index);
}

static bool addressMatchesFilter(const KContacts::Address &address, const QString &filterString)
{
    if (address.street().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.locality().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.region().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.postalCode().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.country().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.label().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (address.postOfficeBox().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    return false;
}

static bool contactMatchesFilter(const KContacts::Addressee &contact, const QString &filterString, ContactsFilterProxyModel::MatchFilterContactFlag flag)
{
    if (contact.assembledName().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (contact.formattedName().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (contact.nickName().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }


    int count = 0;
    if (flag == ContactsFilterProxyModel::MatchFilterContactFlag::All) {
        if (contact.birthday().toString().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
        const KContacts::Address::List addresses = contact.addresses();
        count = addresses.count();
        for (int i = 0; i < count; ++i) {
            if (addressMatchesFilter(addresses.at(i), filterString)) {
                return true;
            }
        }

        const KContacts::PhoneNumber::List phoneNumbers = contact.phoneNumbers();
        count = phoneNumbers.count();
        for (int i = 0; i < count; ++i) {
            if (phoneNumbers.at(i).number().contains(filterString, Qt::CaseInsensitive)) {
                return true;
            }
        }
    }

    const QStringList emails = contact.emails();
    count = emails.count();
    for (int i = 0; i < count; ++i) {
        if (emails.at(i).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
    }


    if (flag == ContactsFilterProxyModel::MatchFilterContactFlag::All) {
        const QStringList categories = contact.categories();
        count = categories.count();
        for (int i = 0; i < count; ++i) {
            if (categories.at(i).contains(filterString, Qt::CaseInsensitive)) {
                return true;
            }
        }
        if (contact.mailer().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.title().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.role().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.organization().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.department().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.note().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.url().url().url().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        const QStringList customs = contact.customs();
        count = customs.count();
        for (int i = 0; i < count; ++i) {
            if (customs.at(i).contains(filterString, Qt::CaseInsensitive)) {
                return true;
            }
        }
    }

    return false;
}

bool contactGroupMatchesFilter(const KContacts::ContactGroup &group, const QString &filterString)
{
    if (group.name().contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    const int count = group.dataCount();
    for (int i = 0; i < count; ++i) {
        if (group.data(i).name().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
        if (group.data(i).email().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
    }

    return false;
}
