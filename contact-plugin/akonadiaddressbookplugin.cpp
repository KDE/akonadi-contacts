/*
    SPDX-FileCopyrightText: 2026 Carl Schwan <carlschwan@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "akonadiaddressbookplugin.h"
#include "akonadiaddressbookplugin_debug.h"
#include "singlecollectionaddressbook.h"

#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/Monitor>
#include <Akonadi/ServerManager>
#include <algorithm>
#include <utility>

AkonadiAddressBookPlugin::AkonadiAddressBookPlugin(QObject *parent, const QVariantList &args)
    : KContacts::AddressBookPlugin(parent, args)
{
    if (qEnvironmentVariableIsSet("AKONADI_CONTACT_KCONTACTS_PLUGIN_NO_AUTO_LAUNCH") && !Akonadi::ServerManager::isRunning()) {
        qCWarning(AKONADIADDRESSBOOKPLUGIN_LOG) << "Akonadi is not running, but auto-launch is disabled!";
        return;
    }
    auto monitor = new Akonadi::Monitor(this);
    monitor->setCollectionMonitored(Akonadi::Collection::root());
    monitor->setTypeMonitored(Akonadi::Monitor::Collections);
    monitor->collectionFetchScope().setContentMimeTypes({KContacts::Addressee::mimeType()});
    connect(monitor, &Akonadi::Monitor::collectionAdded, this, &AkonadiAddressBookPlugin::updateCollection);
    connect(monitor, qOverload<const Akonadi::Collection &>(&Akonadi::Monitor::collectionChanged), this, &AkonadiAddressBookPlugin::updateCollection);
    connect(monitor, &Akonadi::Monitor::collectionRemoved, this, [this](const Akonadi::Collection &collection) {
        const auto oldSize = m_addressBooks.size();
        m_addressBooks.erase(std::remove_if(m_addressBooks.begin(),
                                            m_addressBooks.end(),
                                            [&collection](const auto &book) {
                                                return book.template staticCast<SingleCollectionAddressBook>()->collection().id() == collection.id();
                                            }),
                             m_addressBooks.end());
        if (oldSize != m_addressBooks.size()) {
            Q_EMIT addressBooksChanged();
        }
    });

    auto job = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
    job->setFetchScope(monitor->collectionFetchScope());
    connect(job, &KJob::result, this, [this, job]() {
        if (job->error()) {
            qCWarning(AKONADIADDRESSBOOKPLUGIN_LOG) << job->errorString();
            return;
        }
        for (const auto &collection : job->collections()) {
            updateCollection(collection);
        }
    });
}

void AkonadiAddressBookPlugin::updateCollection(const Akonadi::Collection &collection)
{
    const bool supported = !collection.isVirtual() && collection.contentMimeTypes().contains(KContacts::Addressee::mimeType());
    for (auto it = m_addressBooks.begin(); it != m_addressBooks.end(); ++it) {
        const auto book = it->staticCast<SingleCollectionAddressBook>();
        if (book->collection().id() == collection.id()) {
            if (supported) {
                book->setCollection(collection);
            } else {
                m_addressBooks.erase(it);
            }
            Q_EMIT addressBooksChanged();
            return;
        }
    }
    if (supported) {
        m_addressBooks.push_back(QSharedPointer<SingleCollectionAddressBook>::create(collection));
        Q_EMIT addressBooksChanged();
    }
}

QList<QSharedPointer<KContacts::AddressBook>> AkonadiAddressBookPlugin::addressBooks() const
{
    return m_addressBooks;
}

#include "moc_akonadiaddressbookplugin.cpp"
