/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "collectionfiltermodel_p.h"

#include <Akonadi/EntityTreeModel>

CollectionFilterModel::CollectionFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , mRights(Akonadi::Collection::ReadOnly)
{
}

void CollectionFilterModel::addContentMimeTypeFilter(const QString &mimeType)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    beginFilterChange();
#endif
    mContentMimeTypes.insert(mimeType);
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    endFilterChange(QSortFilterProxyModel::Direction::Rows);
#else
    invalidateFilter();
#endif
}

void CollectionFilterModel::setRightsFilter(Akonadi::Collection::Rights rights)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    beginFilterChange();
#endif
    mRights = rights;
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
    endFilterChange(QSortFilterProxyModel::Direction::Rows);
#else
    invalidateFilter();
#endif
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
