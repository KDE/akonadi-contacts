/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Stephen Kelly <steveire@gmail.com>
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <Akonadi/EntityTreeModel>

#include <memory>

namespace Akonadi
{
class ContactsTreeModelPrivate;

/**
 * @short A model for contacts and contact groups as available in Akonadi.
 *
 * This class provides a model for displaying the contacts and
 * contact groups which are available from Akonadi.
 *
 * Example:
 *
 * @code
 *
 * // use a separated session for this model
 * Akonadi::Session *session = new Akonadi::Session( "MySession" );
 *
 * Akonadi::ItemFetchScope scope;
 * // fetch all content of the contacts, including images
 * scope.fetchFullPayload( true );
 * // fetch the EntityDisplayAttribute, which contains custom names and icons
 * scope.fetchAttribute<Akonadi::EntityDisplayAttribute>();
 *
 * Akonadi::Monitor *monitor = new Akonadi::Monitor;
 * monitor->setSession( session );
 * // include fetching the collection tree
 * monitor->fetchCollection( true );
 * // set the fetch scope that shall be used
 * monitor->setItemFetchScope( scope );
 * // monitor all collections below the root collection for changes
 * monitor->setCollectionMonitored( Akonadi::Collection::root() );
 * // list only contacts and contact groups
 * monitor->setMimeTypeMonitored( KContacts::Addressee::mimeType(), true );
 * monitor->setMimeTypeMonitored( KContacts::ContactGroup::mimeType(), true );
 *
 * Akonadi::ContactsTreeModel *model = new Akonadi::ContactsTreeModel( monitor );
 *
 * Akonadi::ContactsTreeModel::Columns columns;
 * columns << Akonadi::ContactsTreeModel::FullName;
 * columns << Akonadi::ContactsTreeModel::AllEmails;
 * model->setColumns( columns );
 *
 * Akonadi::EntityTreeView *view = new Akonadi::EntityTreeView;
 * view->setModel( model );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT ContactsTreeModel : public EntityTreeModel
{
    Q_OBJECT

public:
    /**
     * Describes the columns that can be shown by the model.
     */
    enum Column {
        /**
         * Shows the formatted name or, if empty, the assembled name.
         */
        FullName,

        /**
         * Shows the family name.
         */
        FamilyName,

        /**
         * Shows the given name.
         */
        GivenName,

        /**
         * Shows the birthday.
         */
        Birthday,

        /**
         * Shows the formatted home address.
         */
        HomeAddress,

        /**
         * Shows the formatted business address.
         */
        BusinessAddress,

        /**
         * Shows the phone numbers.
         */
        PhoneNumbers,

        /**
         * Shows the preferred email address.
         */
        PreferredEmail,

        /**
         * Shows all email address.
         */
        AllEmails,

        /**
         * Shows organization name.
         */
        Organization,

        /**
         * Shows the role of a contact.
         */
        Role,

        /**
         * Shows homepage url.
         */
        Homepage,

        /**
         * Shows the note.
         */
        Note
    };

    /**
     * Describes a list of columns of the contacts tree model.
     */
    using Columns = QList<Column>;

    /**
     * Describes the role for contacts and contact groups.
     */
    enum Roles {
        DateRole = EntityTreeModel::UserRole + 1, ///< The QDate object for the current index.
        UserRole = DateRole + 42
    };

    /**
     * Creates a new contacts tree model.
     *
     * @param monitor The Monitor whose entities should be represented in the model.
     * @param parent The parent object.
     */
    explicit ContactsTreeModel(Monitor *monitor, QObject *parent = nullptr);

    /**
     * Destroys the contacts tree model.
     */
    ~ContactsTreeModel() override;

    /**
     * Sets the @p columns that the model should show.
     */
    void setColumns(const Columns &columns);

    /**
     * Returns the columns that the model currently shows.
     */
    Q_REQUIRED_RESULT Columns columns() const;

    //@cond PRIVATE
    Q_REQUIRED_RESULT QVariant entityData(const Item &item, int column, int role = Qt::DisplayRole) const override;
    Q_REQUIRED_RESULT QVariant entityData(const Collection &collection, int column, int role = Qt::DisplayRole) const override;
    Q_REQUIRED_RESULT QVariant entityHeaderData(int section, Qt::Orientation orientation, int role, HeaderGroup headerGroup) const override;
    Q_REQUIRED_RESULT int entityColumnCount(HeaderGroup headerGroup) const override;
    //@endcond

private:
    //@cond PRIVATE
    std::unique_ptr<ContactsTreeModelPrivate> const d;
    //@endcond
};
}
