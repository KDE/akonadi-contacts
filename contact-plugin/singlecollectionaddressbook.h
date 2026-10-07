/*
    SPDX-FileCopyrightText: 2026 Carl Schwan <carlschwan@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KContacts/AddressBook>
#include <KJob>

class SingleCollectionAddressBook : public KContacts::AddressBook
{
    Q_OBJECT
public:
    explicit SingleCollectionAddressBook(const Akonadi::Collection &collection, QObject *parent = nullptr);
    Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &collection);
    KContacts::Addressee::List addressees() const override;
    bool addAddressee(const KContacts::Addressee &addressee) override;
    bool removeAddressee(const KContacts::Addressee &addressee) override;
    bool updateAddressee(const KContacts::Addressee &addressee) override;

private:
    void upsertItem(const Akonadi::Item &item);
    void removeItem(const Akonadi::Item &item);
    void watchJob(KJob *job);
    Akonadi::Item findItem(const KContacts::Addressee &addressee) const;
    Akonadi::Collection m_collection;
    Akonadi::Item::List m_items;
};
