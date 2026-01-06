/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 - 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <Akonadi/StandardActionManager>

#include <QObject>

#include <memory>

class QAction;
class KActionCollection;
class QItemSelectionModel;
class QWidget;
namespace Akonadi
{
class Item;
class StandardContactActionManagerPrivate;

/*!
 * \brief Manages contact specific actions for collection and item views.
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.6
 */
class AKONADI_CONTACT_WIDGETS_EXPORT StandardContactActionManager : public QObject
{
    Q_OBJECT

public:
    /*!
     * Describes the supported actions.
     */
    enum Type {
        CreateContact = Akonadi::StandardActionManager::LastType + 1, ///< Creates a new contact
        CreateContactGroup, ///< Creates a new contact group
        EditItem, ///< Edits the selected contact resp. contact group
        LastType ///< Marks last action
    };

    /*!
     * Creates a new standard contact action manager.
     *
     * \a actionCollection The action collection to operate on.
     * \a parent The parent widget.
     */
    explicit StandardContactActionManager(KActionCollection *actionCollection, QWidget *parent = nullptr);

    /*!
     * Destroys the standard contact action manager.
     */
    ~StandardContactActionManager() override;

    /*!
     * Sets the collection selection model based on which the collection
     * related actions should operate. If none is set, all collection actions
     * will be disabled.
     * \a selectionModel the selection model for collections
     */
    void setCollectionSelectionModel(QItemSelectionModel *selectionModel);

    /*!
     * Sets the item selection model based on which the item related actions
     * should operate. If none is set, all item actions will be disabled.
     * \a selectionModel the selection model for items
     */
    void setItemSelectionModel(QItemSelectionModel *selectionModel);

    /*!
     * Creates the action of the given type and adds it to the action collection
     * specified in the constructor if it does not exist yet. The action is
     * connected to its default implementation provided by this class.
     * \a type the type of action to create
     */
    QAction *createAction(Type type);

    /*!
     * Creates the action of the given type and adds it to the action collection
     * specified in the constructor if it does not exist yet. The action is
     * connected to its default implementation provided by this class.
     * \a type the type of action to create
     */
    QAction *createAction(Akonadi::StandardActionManager::Type type);

    /*!
     * Convenience method to create all standard actions.
     * \sa createAction()
     */
    void createAllActions();

    /*!
     * Returns the action of the given type, 0 if it has not been created (yet).
     */
    QAction *action(Type type) const;

    /*!
     * Returns the action of the given type, 0 if it has not been created (yet).
     * \a type the type of action to return
     */
    QAction *action(Akonadi::StandardActionManager::Type type) const;

    /*!
     * Sets the label of the action \a type to \a text, which is used during
     * updating the action state and substituted according to the number of
     * selected objects. This is mainly useful to customize the label of actions
     * that can operate on multiple objects.
     *
     * Example:
     * \code
     * acctMgr->setActionText( Akonadi::StandardActionManager::CopyItems,
     *                         ki18np( "Copy Item", "Copy %1 Items" ) );
     * \endcode
     */
    void setActionText(Akonadi::StandardActionManager::Type type, const KLocalizedString &text);

    /*!
     * Sets whether the default implementation for the given action \a type
     * shall be executed when the action is triggered.
     *
     * \a intercept If \\ false, the default implementation will be executed,
     *                  if \\ true no action is taken.
     */
    void interceptAction(Type type, bool intercept = true);

    /*!
     * Sets whether the default implementation for the given action \a type
     * shall be executed when the action is triggered.
     *
     * \a intercept If \\ false, the default implementation will be executed,
     *                  if \\ true no action is taken.
     */
    void interceptAction(Akonadi::StandardActionManager::Type type, bool intercept = true);

    /*!
     * Returns the list of collections that are currently selected.
     * The list is empty if no collection is currently selected.
     */
    [[nodiscard]] Akonadi::Collection::List selectedCollections() const;

    /*!
     * Returns the list of items that are currently selected.
     * The list is empty if no item is currently selected.
     */
    [[nodiscard]] Akonadi::Item::List selectedItems() const;

    /*!
     * \a names the list of names to set as collection properties page names
     * \since 4.8.2
     */
    void setCollectionPropertiesPageNames(const QStringList &names);

Q_SIGNALS:
    /*!
     * This signal is emitted whenever the action state has been updated.
     * In case you have special needs for changing the state of some actions,
     * connect to this signal and adjust the action state.
     */
    void actionStateUpdated();

private:
    std::unique_ptr<StandardContactActionManagerPrivate> const d;
};
}
