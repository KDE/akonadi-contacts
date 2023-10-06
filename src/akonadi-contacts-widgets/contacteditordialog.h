/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <QDialog>

#include <memory>

namespace Akonadi
{
class Collection;
class Item;
class AkonadiContactEditor;
class AbstractContactEditorWidget;
class ContactEditorDialogPrivate;

/**
 * @short A dialog for creating or editing a contact in Akonadi.
 *
 * This dialog provides a way to create a new contact or edit
 * an existing contact in Akonadi.
 *
 * Example for creating a new contact:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * ContactEditorDialog *dlg = new ContactEditorDialog( ContactEditorDialog::CreateMode, this );
 * connect( dlg, SIGNAL(contactStored(Akonadi::Item)),
 *          this, SLOT(contactStored(Akonadi::Item)) );
 * dlg->show();
 *
 *
 * @endcode
 *
 * Example for editing an existing contact:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item contact = ...;
 *
 * ContactEditorDialog *dlg = new ContactEditorDialog( ContactEditorDialog::EditMode, this );
 * connect( dlg, SIGNAL(contactStored(Akonadi::Item)),
 *          this, SLOT(contactStored(Akonadi::Item)) );
 * dlg->setContact( contact );
 * dlg->show();
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactEditorDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Describes the mode of the editor dialog.
     */
    enum Mode {
        CreateMode, ///< Creates a new contact
        EditMode ///< Edits an existing contact
    };

    enum DisplayMode {
        FullMode, // Show all pages
        VCardMode // Show just pages with elements stored in vcard.
    };

    /**
     * Creates a new contact editor dialog with the standard editor widget.
     *
     * @param mode The mode of the dialog.
     * @param parent The parent widget of the dialog.
     */
    explicit ContactEditorDialog(Mode mode, QWidget *parent = nullptr);

    /**
     * Creates a new contact editor dialog with a custom editor widget.
     *
     * @param mode The mode of the dialog.
     * @param editorWidget The contact editor widget that shall be used for editing.
     * @param parent The parent widget of the dialog.
     */
    ContactEditorDialog(Mode mode, Akonadi::AbstractContactEditorWidget *editorWidget, QWidget *parent = nullptr);

    /**
     * Creates a new contact editor dialog with a custom editor widget.
     *
     * @param mode The mode of the dialog.
     * @param displayMode The mode of displaying: full or vcard
     * @param parent The parent widget of the dialog.
     * @since 4.10
     */
    ContactEditorDialog(Mode mode, DisplayMode displayMode, QWidget *parent = nullptr);

    /**
     * Destroys the contact editor dialog.
     */
    ~ContactEditorDialog() override;

    /**
     * Sets the @p contact to edit when in EditMode.
     * @param contact the contact to edit
     * @note The contact item just must have a uid set, all
     * other data are fetched by the dialog automatically.
     */
    void setContact(const Akonadi::Item &contact);

    /**
     * Sets the @p addressbook that shall be selected as default in create mode.
     */
    void setDefaultAddressBook(const Akonadi::Collection &addressbook);

    /**
     * Returns the ContactEditor that is used by this dialog.
     */
    [[nodiscard]] Akonadi::AkonadiContactEditor *editor() const;

    void reject() override;

Q_SIGNALS:
    /**
     * This signal is emitted whenever a contact was updated or stored.
     *
     * @param contact The data reference of the contact.
     */
    void contactStored(const Akonadi::Item &contact);

    /**
     * This signal is emitted whenever a contact is not updated or stored.
     *
     * @param errMsg The error during updating or storing contact.
     */
    void error(const QString &errMsg);

public Q_SLOTS:
    void accept() override;

private:
    //@cond PRIVATE
    std::unique_ptr<ContactEditorDialogPrivate> const d;
    //@endcond
};
}
