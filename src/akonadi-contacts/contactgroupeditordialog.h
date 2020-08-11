/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_CONTACTGROUPEDITORDIALOG_H
#define AKONADI_CONTACTGROUPEDITORDIALOG_H

#include "akonadi-contact_export.h"

#include <QDialog>

namespace Akonadi {
class Item;
class Collection;
class ContactGroupEditor;

/**
 * @short A dialog for creating or editing a contact group in Akonadi.
 *
 * This dialog provides a way to create a new contact group or edit
 * an existing contact group in Akonadi.
 *
 * Example for creating a new contact group:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * ContactGroupEditorDialog *dlg = new ContactGroupEditorDialog( ContactGroupEditorDialog::CreateMode, this );
 * connect( dlg, SIGNAL(contactGroupStored(Akonadi::Item)),
 *          this, SLOT(contactGroupStored(Akonadi::Item)) );
 * dlg->show();
 *
 * @endcode
 *
 * Example for editing an existing contact group:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item contactGroup = ...;
 *
 * ContactGroupEditorDialog *dlg = new ContactGroupEditorDialog( ContactGroupEditorDialog::EditMode, this );
 * connect( dlg, SIGNAL(contactGroupStored(Akonadi::Item)),
 *          this, SLOT(contactGroupStored(Akonadi::Item)) );
 * dlg->setContactGroup( contactGroup );
 * dlg->show();
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupEditorDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Describes the mode of the contact group editor.
     */
    enum Mode {
        CreateMode, ///< Creates a new contact group
        EditMode    ///< Edits an existing contact group
    };

    /**
     * Creates a new contact group editor dialog.
     *
     * @param mode The mode of the dialog.
     * @param parent The parent widget of the dialog.
     */
    explicit ContactGroupEditorDialog(Mode mode, QWidget *parent = nullptr);

    /**
     * Destroys the contact group editor dialog.
     */
    ~ContactGroupEditorDialog();

    /**
     * Sets the contact @p group to edit when in EditMode.
     */
    void setContactGroup(const Akonadi::Item &group);

    /**
     * Sets the @p addressbook that shall be selected as default
     * for storage in create mode.
     */
    void setDefaultAddressBook(const Akonadi::Collection &addressbook);

    /**
     * Returns the ContactGroupEditor that is used by the dialog.
     */
    Q_REQUIRED_RESULT ContactGroupEditor *editor() const;

    void reject() override;
Q_SIGNALS:
    /**
     * This signal is emitted whenever a contact group was updated or stored.
     *
     * @param group The contact group.
     */
    void contactGroupStored(const Akonadi::Item &group);

private:
    void slotAccepted();

    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
