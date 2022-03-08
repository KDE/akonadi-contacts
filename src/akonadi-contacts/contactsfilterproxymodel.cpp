/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactsfilterproxymodel.h"

#include "contactstreemodel.h"

#include <Akonadi/EntityTreeModel>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

using namespace Akonadi;

static bool contactMatchesFilter(const KContacts::Addressee &contact, const QString &filterString, ContactsFilterProxyModel::MatchFilterContactFlag flag);
static bool contactGroupMatchesFilter(const KContacts::ContactGroup &group, const QString &filterString);

static QString normalize(QStringView str)
{
    QString out;
    out.reserve(str.size());
    for (const auto c : str) {
        // case folding
        const auto n = c.toCaseFolded();

        // if the character has a canonical decomposition use that and skip the
        // combining diacritic markers following it
        // see https://en.wikipedia.org/wiki/Unicode_equivalence
        // see https://en.wikipedia.org/wiki/Combining_character
        if (n.decompositionTag() == QChar::Canonical) {
            out.push_back(n.decomposition().at(0));
        }
        // handle compatibility compositions such as ligatures
        // see https://en.wikipedia.org/wiki/Unicode_compatibility_characters
        else if (n.decompositionTag() == QChar::Compat && n.isLetter() && n.script() == QChar::Script_Latin) {
            out.append(n.decomposition());
        } else {
            out.push_back(n);
        }
    }
    return out;
}

class Akonadi::ContactsFilterProxyModelPrivate
{
public:
    ContactsFilterProxyModelPrivate()
        : flags({})
    {
    }

    QString mFilter;
    ContactsFilterProxyModel::FilterFlags flags;
    ContactsFilterProxyModel::MatchFilterContactFlag matchFilterFlag = ContactsFilterProxyModel::MatchFilterContactFlag::All;
    bool mExcludeVirtualCollections = false;
};

ContactsFilterProxyModel::ContactsFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d(new ContactsFilterProxyModelPrivate)
{
    // contact names should be sorted correctly
    setSortLocaleAware(true);
    setDynamicSortFilter(true);
}

ContactsFilterProxyModel::~ContactsFilterProxyModel() = default;

void ContactsFilterProxyModel::setFilterString(const QString &filter)
{
    d->mFilter = filter;
    invalidateFilter();
}

bool ContactsFilterProxyModel::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    const QModelIndex index = sourceModel()->index(row, 0, parent);
    if (d->mExcludeVirtualCollections) {
        const auto collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
        if (collection.isValid() && collection.isVirtual()) {
            return false;
        }
    }

    if ((d->mFilter.isEmpty()) && (!(d->flags & ContactsFilterProxyModel::HasEmail))) {
        return true;
    }
    const QString filterStr = normalize(d->mFilter);
    const auto item = index.data(Akonadi::EntityTreeModel::ItemRole).value<Akonadi::Item>();

    if (item.hasPayload<KContacts::Addressee>()) {
        const auto contact = item.payload<KContacts::Addressee>();
        if (d->flags & ContactsFilterProxyModel::HasEmail) {
            if (contact.emails().isEmpty()) {
                return false;
            }
        }
        if (!d->mFilter.isEmpty()) {
            return contactMatchesFilter(contact, filterStr, d->matchFilterFlag);
        }
    } else {
        if (!d->mFilter.isEmpty()) {
            if (item.hasPayload<KContacts::ContactGroup>()) {
                const auto group = item.payload<KContacts::ContactGroup>();
                return contactGroupMatchesFilter(group, filterStr);
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
    const auto collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
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
    if (normalize(contact.assembledName()).contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (normalize(contact.formattedName()).contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    if (normalize(contact.nickName()).contains(filterString, Qt::CaseInsensitive)) {
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
        if (normalize(emails.at(i)).contains(filterString, Qt::CaseInsensitive)) {
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

        if (normalize(contact.title()).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (contact.role().contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (normalize(contact.organization()).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (normalize(contact.department()).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }

        if (normalize(contact.note()).contains(filterString, Qt::CaseInsensitive)) {
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
    if (normalize(group.name()).contains(filterString, Qt::CaseInsensitive)) {
        return true;
    }

    const int count = group.dataCount();
    for (int i = 0; i < count; ++i) {
        if (normalize(group.data(i).name()).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
        if (normalize(group.data(i).email()).contains(filterString, Qt::CaseInsensitive)) {
            return true;
        }
    }

    return false;
}
