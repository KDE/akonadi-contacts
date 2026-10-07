/*
    SPDX-FileCopyrightText: 2026 Carl Schwan <carlschwan@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "singlecollectionaddressbook.h"

#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemDeleteJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <Akonadi/Monitor>
#include <algorithm>
#include <utility>

SingleCollectionAddressBook::SingleCollectionAddressBook(const Akonadi::Collection &collection, QObject *parent)
    : KContacts::AddressBook(parent)
{
    setCollection(collection);
    setIsLoading(true);
    auto monitor = new Akonadi::Monitor(this);
    monitor->setCollectionMonitored(collection);
    monitor->itemFetchScope().fetchFullPayload();
    connect(monitor, &Akonadi::Monitor::itemAdded, this, [this](const Akonadi::Item &item) {
        upsertItem(item);
    });
    connect(monitor, &Akonadi::Monitor::itemChanged, this, [this](const Akonadi::Item &item) {
        upsertItem(item);
    });
    connect(monitor, &Akonadi::Monitor::itemRemoved, this, &SingleCollectionAddressBook::removeItem);
    connect(monitor,
            &Akonadi::Monitor::itemMoved,
            this,
            [this](const Akonadi::Item &item, const Akonadi::Collection &source, const Akonadi::Collection &destination) {
                if (source.id() == m_collection.id()) {
                    removeItem(item);
                }
                if (destination.id() == m_collection.id()) {
                    upsertItem(item);
                }
            });
    auto job = new Akonadi::ItemFetchJob(collection, this);
    job->fetchScope().fetchFullPayload();
    connect(job, &KJob::result, this, [this, job]() {
        if (job->error()) {
            Q_EMIT errorOccurred(job->errorString());
        } else {
            for (const auto &item : job->items()) {
                upsertItem(item);
            }
        }
        setIsLoading(false);
    });
}

Akonadi::Collection SingleCollectionAddressBook::collection() const
{
    return m_collection;
}

void SingleCollectionAddressBook::setCollection(const Akonadi::Collection &collection)
{
    Q_ASSERT(!m_collection.isValid() || m_collection.id() == collection.id());
    m_collection = collection;
    const auto attr = collection.attribute<Akonadi::EntityDisplayAttribute>();
    setName(attr && !attr->displayName().isEmpty() ? attr->displayName() : collection.name());
    setIcon(attr ? attr->icon() : QIcon::fromTheme(QStringLiteral("view-pim-contacts")));
    setAccessMode(collection.rights() & (Akonadi::Collection::CanCreateItem | Akonadi::Collection::CanChangeItem | Akonadi::Collection::CanDeleteItem)
                      ? KContacts::ReadWrite
                      : KContacts::ReadOnly);
}

KContacts::Addressee::List SingleCollectionAddressBook::addressees() const
{
    KContacts::Addressee::List result;
    result.reserve(m_items.size());
    for (const auto &item : m_items) {
        result.push_back(item.payload<KContacts::Addressee>());
    }
    return result;
}

void SingleCollectionAddressBook::upsertItem(const Akonadi::Item &item)
{
    if (!item.hasPayload<KContacts::Addressee>()) {
        removeItem(item);
        return;
    }
    const auto it = std::find_if(m_items.begin(), m_items.end(), [&item](const auto &entry) {
        return entry.id() == item.id();
    });
    if (it != m_items.end()) {
        const int row = std::distance(m_items.begin(), it);
        *it = item;
        Q_EMIT addresseesChanged(row, row);
    } else {
        const int row = m_items.size();
        Q_EMIT addresseesAboutToBeInserted(row, row);
        m_items.push_back(item);
        Q_EMIT addresseesInserted();
    }
    Q_EMIT addresseesChanged();
}

void SingleCollectionAddressBook::removeItem(const Akonadi::Item &item)
{
    const auto it = std::find_if(m_items.begin(), m_items.end(), [&item](const auto &entry) {
        return entry.id() == item.id();
    });
    if (it == m_items.end()) {
        return;
    }
    const int row = std::distance(m_items.begin(), it);
    Q_EMIT addresseesAboutToBeRemoved(row, row);
    m_items.erase(it);
    Q_EMIT addresseesRemoved();
    Q_EMIT addresseesChanged();
}

Akonadi::Item SingleCollectionAddressBook::findItem(const KContacts::Addressee &addressee) const
{
    if (addressee.uid().isEmpty()) {
        return {};
    }
    const auto it = std::find_if(m_items.begin(), m_items.end(), [&addressee](const auto &item) {
        return item.template payload<KContacts::Addressee>().uid() == addressee.uid();
    });
    return it == m_items.end() ? Akonadi::Item() : *it;
}

void SingleCollectionAddressBook::watchJob(KJob *job)
{
    connect(job, &KJob::result, this, [this](KJob *finishedJob) {
        if (finishedJob->error()) {
            Q_EMIT errorOccurred(finishedJob->errorString());
        }
    });
}

bool SingleCollectionAddressBook::addAddressee(const KContacts::Addressee &addressee)
{
    if (!(m_collection.rights() & Akonadi::Collection::CanCreateItem)) {
        return false;
    }
    Akonadi::Item item;
    item.setMimeType(KContacts::Addressee::mimeType());
    item.setPayload(addressee);
    watchJob(new Akonadi::ItemCreateJob(item, m_collection, this));
    return true;
}

bool SingleCollectionAddressBook::removeAddressee(const KContacts::Addressee &addressee)
{
    const auto item = findItem(addressee);
    if (!item.isValid() || !(m_collection.rights() & Akonadi::Collection::CanDeleteItem)) {
        return false;
    }
    watchJob(new Akonadi::ItemDeleteJob(item, this));
    return true;
}

bool SingleCollectionAddressBook::updateAddressee(const KContacts::Addressee &addressee)
{
    auto item = findItem(addressee);
    if (!item.isValid() || !(m_collection.rights() & Akonadi::Collection::CanChangeItem)) {
        return false;
    }
    item.setPayload(addressee);
    watchJob(new Akonadi::ItemModifyJob(item, this));
    return true;
}

#include "moc_singlecollectionaddressbook.cpp"
