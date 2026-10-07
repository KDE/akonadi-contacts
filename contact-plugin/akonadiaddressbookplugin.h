/*
    SPDX-FileCopyrightText: 2026 Carl Schwan <carlschwan@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <KContacts/AddressBookPlugin>

class AkonadiAddressBookPlugin : public KContacts::AddressBookPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kcontacts.AddressBookPlugin")
public:
    explicit AkonadiAddressBookPlugin(QObject *parent = nullptr, const QVariantList &args = {});
    QList<QSharedPointer<KContacts::AddressBook>> addressBooks() const override;

private:
    void updateCollection(const Akonadi::Collection &collection);
    QList<QSharedPointer<KContacts::AddressBook>> m_addressBooks;
};
