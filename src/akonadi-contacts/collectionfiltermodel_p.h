/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QSortFilterProxyModel>

#include <collection.h>

/**
 * @short A filter model for Akonadi collections.
 *
 * This proxy model filters Akonadi collections by content
 * mime type and rights.
 * It works on a flat list of collections, so a EntityTreeModel
 * has to be adapted by using Akonadi::DescendantsProxyModel.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class CollectionFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    /**
     * Creates a new collection filter model.
     *
     * @param parent The parent object.
     */
    explicit CollectionFilterModel(QObject *parent);

    /**
     * Adds a mime type to the content mime type filter list.
     *
     * If a mime type has been added, only collections that contain
     * this mime type in their content mime types will be listed by
     * this proxy model.
     *
     * @param mimeType mime type content filter
     */
    void addContentMimeTypeFilter(const QString &mimeType);

    /**
     * Sets the collection @p rights filter.
     *
     * Only collections that allows this rights combination
     * will be listed by this proxy model.
     *
     * @param rights collection rights filter
     */
    void setRightsFilter(Akonadi::Collection::Rights rights);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;

private:
    QSet<QString> mContentMimeTypes;
    Akonadi::Collection::Rights mRights;
};

