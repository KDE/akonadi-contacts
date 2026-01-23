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
class Addressee;
}
namespace Akonadi
{
class Collection;
class Item;
class AbstractContactEditorWidget;
class AkonadiContactEditorPrivate;

/*!
 * \class Akonadi::AkonadiContactEditor
 * \brief An widget to edit contacts in Akonadi.
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/ContactEditor
 *
 * This widget provides a way to create a new contact or edit
 * an existing contact in Akonadi.
 *
 * Example for creating a new contact:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * ContactEditor *editor = new ContactEditor( Akonadi::ContactEditor::CreateMode, this );
 *
 * ...
 *
 * if ( !editor->saveContactInAddressBook() ) {
 *   qCDebug(AKONADICONTACT_LOG) << "Unable to save new contact to storage";
 *   return;
 * }
 *
 * \endcode
 *
 * Example for editing an existing contact:
 *
 * \code
 *
 * const Akonadi::Item contact = ...;
 *
 * ContactEditor *editor = new ContactEditor( Akonadi::ContactEditor::EditMode, this );
 * editor->loadContact( contact );
 *
 * ...
 *
 * editor->saveContactInAddressBook();
 *
 * \endcode
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.4
 */
class AKONADI_CONTACT_WIDGETS_EXPORT AkonadiContactEditor : public QWidget
{
    Q_OBJECT

public:
    /*!
     * Describes the mode of the editor.
     */
    enum Mode {
        CreateMode, ///< Creates a new contact
        EditMode ///< Edits an existing contact
    };

    enum DisplayMode {
        FullMode, ///< Show all pages
        VCardMode ///< Show just pages with elements stored in vcard.
    };

    /*!
     * Creates a new contact editor with the standard editor widget.
     *
     * \a mode The mode of the editor.
     * \a parent The parent widget of the editor.
     */
    explicit AkonadiContactEditor(Mode mode, QWidget *parent = nullptr);

    /*!
     * Creates a new contact editor with a custom editor widget.
     *
     * \a mode The mode of the editor.
     * \a editorWidget The contact editor widget that shall be used for editing.
     * \a parent The parent widget of the editor.
     */
    AkonadiContactEditor(Mode mode, Akonadi::AbstractContactEditorWidget *editorWidget, QWidget *parent = nullptr);

    /*!
     * Creates a new contact editor dialog with a custom editor widget.
     *
     * \a mode The mode of the dialog.
     * \a displayMode mode for displaying the editor
     * \a parent The parent widget of the dialog.
     * \since 4.10
     */
    AkonadiContactEditor(Mode mode, DisplayMode displayMode, QWidget *parent = nullptr);

    /*!
     * Destroys the contact editor.
     */
    ~AkonadiContactEditor() override;

    /*!
     * Sets a \a contact that is used as template in create mode.
     * The fields of the editor will be prefilled with the content of the contact.
     * \a contact the contact to use as template content
     */
    void setContactTemplate(const KContacts::Addressee &contact);

    /*!
     * Sets the \a addressbook which shall be used to store new
     * contacts.
     */
    void setDefaultAddressBook(const Akonadi::Collection &addressbook);

    /*!
     * \since 4.10
     * \brief ContactEditor::contact
     * Returns
     */
    [[nodiscard]] KContacts::Addressee contact();
    [[nodiscard]] bool hasNoSavedData() const;
public Q_SLOTS:
    /*!
     * Loads the \a contact into the editor.
     */
    void loadContact(const Akonadi::Item &contact);

    /*!
     * Save the contact from the editor back to the storage. And return error.
     * Need to connect to finished() signal, to keep time to Q_EMIT signal.
     * \since 4.11
     */
    void saveContactInAddressBook();

Q_SIGNALS:
    /*!
     * This signal is emitted when the \a contact has been saved back
     * to the storage.
     */
    void contactStored(const Akonadi::Item &contact);

    /*!
     * This signal is emitted when an error occurred during the save.
     * \a errorMsg The error message.
     * \since 4.11
     */
    void error(const QString &errorMsg);

    /*!
     * \brief finished
     * \since 4.11
     */
    void finished();

private:
    std::unique_ptr<AkonadiContactEditorPrivate> const d;
};
}
