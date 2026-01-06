/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <QWidget>

#include <memory>

namespace KContacts
{
class ContactGroup;
}

namespace Akonadi
{
class Collection;
class Item;
class ContactGroupEditorPrivate;

/*!
 * \brief An widget to edit contact groups in Akonadi.
 *
 * This widget provides a way to create a new contact group or edit
 * an existing contact group in Akonadi.
 *
 * Example for creating a new contact group:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * ContactGroupEditor *editor = new ContactGroupEditor( Akonadi::ContactGroupEditor::CreateMode, this );
 *
 * ...
 *
 * if ( !editor->saveContactGroup() ) {
 *   qCDebug(AKONADICONTACT_LOG) << "Unable to save new contact group to storage";
 *   return;
 * }
 *
 * \endcode
 *
 * Example for editing an existing contact group:
 *
 * \code
 *
 * const Akonadi::Item contactGroup = ...;
 *
 * ContactGroupEditor *editor = new ContactGroupEditor( Akonadi::ContactGroupEditor::EditMode, this );
 * editor->loadContactGroup( contactGroup );
 *
 * ...
 *
 * if ( !editor->saveContactGroup() ) {
 *   qCDebug(AKONADICONTACT_LOG) << "Unable to save changed contact group to storage";
 *   return;
 * }
 *
 * \endcode
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.4
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactGroupEditor : public QWidget
{
    Q_OBJECT

public:
    /*!
     * Describes the mode of the contact group editor.
     */
    enum Mode {
        CreateMode, ///< Creates a new contact group
        EditMode ///< Edits an existing contact group
    };

    /*!
     * Creates a new contact group editor.
     *
     * \a mode The mode of the editor.
     * \a parent The parent widget of the editor.
     */
    explicit ContactGroupEditor(Mode mode, QWidget *parent = nullptr);

    /*!
     * Destroys the contact group editor.
     */
    ~ContactGroupEditor() override;

    /*!
     * Sets a contact \a group that is used as template in create mode.
     * The fields of the editor will be prefilled with the content of the group.
     * \a group the group to use as template content
     */
    void setContactGroupTemplate(const KContacts::ContactGroup &group);

    /*!
     * Sets the \a addressbook which shall be used to store new
     * contact groups.
     */
    void setDefaultAddressBook(const Akonadi::Collection &addressbook);

    void groupNameIsValid(bool isValid);

public Q_SLOTS:
    /*!
     * Loads the contact \a group into the editor.
     */
    void loadContactGroup(const Akonadi::Item &group);

    /*!
     * Saves the contact group from the editor back to the storage.
     *
     * Returns \\ true if the contact group has been saved successfully, false otherwise.
     */
    bool saveContactGroup();

Q_SIGNALS:
    /*!
     * This signal is emitted when the contact \a group has been saved back
     * to the storage.
     */
    void contactGroupStored(const Akonadi::Item &group);

    /*!
     * This signal is emitted when an error occurred during the save.
     * \a errorMsg The error message.
     */
    void error(const QString &errorMsg);

private:
    friend class ContactGroupEditorDialog;

    std::unique_ptr<ContactGroupEditorPrivate> const d;

    Q_DISABLE_COPY(ContactGroupEditor)
};
}
