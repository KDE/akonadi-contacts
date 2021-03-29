/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <QSortFilterProxyModel>

namespace Akonadi
{
/**
 * @short A proxy model for \a ContactsTreeModel models.
 *
 * This class provides a filter proxy model for a ContactsTreeModel.
 * The list of shown contacts or contact groups can be limited by
 * settings a filter pattern. Only contacts or contact groups that contain
 * this pattern as part of their data will be listed.
 *
 * Example:
 *
 * @code
 *
 * Akonadi::ContactsTreeModel *model = new Akonadi::ContactsTreeModel( ... );
 *
 * Akonadi::ContactsFilterProxyModel *filter = new Akonadi::ContactsFilterProxyModel;
 * filter->setSourceModel( model );
 *
 * Akonadi::EntityTreeView *view = new Akonadi::EntityTreeView;
 * view->setModel( filter );
 *
 * QLineEdit *filterEdit = new QLineEdit;
 * connect( filterEdit, SIGNAL(textChanged(QString)),
 *          filter, SLOT(setFilterString(QString)) );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT ContactsFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum MatchFilterContactFlag { All = 0, OnlyNameAndEmailsAddresses = 1 };
    enum FilterFlag {
        HasEmail = 0x01 /// Filters out contacts without any email address set.
    };
    Q_DECLARE_FLAGS(FilterFlags, FilterFlag)

    /**
     * Creates a new contacts filter proxy model.
     *
     * @param parent The parent object.
     */
    explicit ContactsFilterProxyModel(QObject *parent = nullptr);

    /**
     * Destroys the contacts filter proxy model.
     */
    ~ContactsFilterProxyModel() override;

    /**
     * Sets the filter @p flags. By default
     * ContactsFilterProxyModel::FilterString is set.
     * @param flags the filter flags to set
     * @since 4.8
     */
    void setFilterFlags(ContactsFilterProxyModel::FilterFlags flags);

    /**
     * @brief setMatchFilterContactFlag
     * @param flag
     * @since 5.8.0
     *
     */
    void setMatchFilterContactFlag(ContactsFilterProxyModel::MatchFilterContactFlag flag);

    Q_REQUIRED_RESULT Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * Sets whether we want virtual collections to be filtered or not.
     * By default, virtual collections are accepted.
     *
     * @param exclude If true, virtual collections aren't accepted.
     *
     * @since 4.8
     */
    void setExcludeVirtualCollections(bool exclude);

public Q_SLOTS:
    /**
     * Sets the @p filter that is used to filter for matching contacts
     * and contact groups.
     */
    void setFilterString(const QString &filter);

protected:
    //@cond PRIVATE
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    //@endcond

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ContactsFilterProxyModel::FilterFlags)
}

