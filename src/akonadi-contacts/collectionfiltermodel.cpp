/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "collectionfiltermodel_p.h"

#include <entitytreemodel.h>

CollectionFilterModel::CollectionFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , mRights(Akonadi::Collection::ReadOnly)
{
}

void CollectionFilterModel::addContentMimeTypeFilter(const QString &mimeType)
{
    mContentMimeTypes.insert(mimeType);
    invalidateFilter();
}

void CollectionFilterModel::setRightsFilter(Akonadi::Collection::Rights rights)
{
    mRights = rights;
    invalidateFilter();
}

bool CollectionFilterModel::filterAcceptsRow(int row, const QModelIndex &parent) const
{
    bool accepted = true;

    const QModelIndex index = sourceModel()->index(row, 0, parent);
    const auto collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (!collection.isValid()) {
        return false;
    }

    if (!mContentMimeTypes.isEmpty()) {
        const auto collectionMimeTypesSet = collection.contentMimeTypes();
        const QSet<QString> contentMimeTypes = QSet<QString>(collectionMimeTypesSet.begin(), collectionMimeTypesSet.end());
        accepted = accepted && contentMimeTypes.intersects(mContentMimeTypes);
    }

    if (mRights != Akonadi::Collection::ReadOnly) {
        accepted = accepted && (collection.rights() & mRights);
    }

    return accepted;
}

#include "moc_collectionfiltermodel_p.cpp"
