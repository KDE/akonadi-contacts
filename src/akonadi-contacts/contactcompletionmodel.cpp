/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactcompletionmodel_p.h"

#include <Akonadi/Monitor>
#include <Akonadi/Session>
#include <akonadi/itemfetchscope.h>
#include <entitymimetypefiltermodel.h>

#include <kcontacts/addressee.h>

using namespace Akonadi;

QAbstractItemModel *ContactCompletionModel::mSelf = nullptr;

QAbstractItemModel *ContactCompletionModel::self()
{
    if (mSelf) {
        return mSelf;
    }

    auto monitor = new Monitor;
    monitor->setObjectName(QStringLiteral("ContactCompletionModelMonitor"));
    monitor->fetchCollection(true);
    monitor->itemFetchScope().fetchFullPayload();
    monitor->setCollectionMonitored(Akonadi::Collection::root());
    monitor->setMimeTypeMonitored(KContacts::Addressee::mimeType());

    auto model = new ContactCompletionModel(monitor);

    auto filter = new Akonadi::EntityMimeTypeFilterModel(model);
    filter->setSourceModel(model);
    filter->addMimeTypeExclusionFilter(Akonadi::Collection::mimeType());
    filter->addMimeTypeExclusionFilter(Akonadi::Collection::virtualMimeType());
    filter->setHeaderGroup(Akonadi::EntityTreeModel::ItemListHeaders);

    mSelf = filter;

    return mSelf;
}

ContactCompletionModel::ContactCompletionModel(Monitor *monitor, QObject *parent)
    : EntityTreeModel(monitor, parent)
{
    setCollectionFetchStrategy(InvisibleCollectionFetch);
}

ContactCompletionModel::~ContactCompletionModel()
{
}

QVariant ContactCompletionModel::entityData(const Item &item, int column, int role) const
{
    if (!item.hasPayload<KContacts::Addressee>()) {
        // Pass modeltest
        if (role == Qt::DisplayRole) {
            return item.remoteId();
        }

        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const auto contact = item.payload<KContacts::Addressee>();

        switch (column) {
        case NameColumn:
            if (!contact.formattedName().isEmpty()) {
                return contact.formattedName();
            } else {
                return contact.assembledName();
            }
            break;
        case NameAndEmailColumn: {
            QString name = QStringLiteral("%1 %2").arg(contact.givenName(), contact.familyName()).simplified();
            if (name.isEmpty()) {
                name = contact.organization().simplified();
            }
            if (name.isEmpty()) {
                return QString();
            }

            const QString email = contact.preferredEmail().simplified();
            if (email.isEmpty()) {
                return QString();
            }

            return QStringLiteral("%1 <%2>").arg(name, email);
            break;
        }
        case EmailColumn:
            return contact.preferredEmail();
            break;
        }
    }

    return EntityTreeModel::entityData(item, column, role);
}

QVariant ContactCompletionModel::entityData(const Collection &collection, int column, int role) const
{
    return EntityTreeModel::entityData(collection, column, role);
}

int ContactCompletionModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 3;
    } else {
        return 0;
    }
}

int ContactCompletionModel::entityColumnCount(HeaderGroup) const
{
    return 3;
}

#include "moc_contactcompletionmodel_p.cpp"
