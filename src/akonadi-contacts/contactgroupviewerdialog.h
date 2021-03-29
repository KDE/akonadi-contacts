/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <QDialog>

namespace Akonadi
{
class Item;

class ContactGroupViewer;

/**
 * @short A dialog for displaying a contact group in Akonadi.
 *
 * This dialog provides a way to show a contact group from the
 * Akonadi storage.
 *
 * Example:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item group = ...
 *
 * ContactGroupViewerDialog *dlg = new ContactGroupViewerDialog( this );
 * dlg->setContactGroup( group );
 * dlg->show();
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupViewerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group viewer dialog.
     *
     * @param parent The parent widget of the dialog.
     */
    explicit ContactGroupViewerDialog(QWidget *parent = nullptr);

    /**
     * Destroys the contact group viewer dialog.
     */
    ~ContactGroupViewerDialog() override;

    /**
     * Returns the contact group that is currently displayed.
     */
    Q_REQUIRED_RESULT Akonadi::Item contactGroup() const;

    /**
     * Returns the ContactGroupViewer that is used by this dialog.
     */
    ContactGroupViewer *viewer() const;

public Q_SLOTS:
    /**
     * Sets the contact @p group that shall be displayed in the dialog.
     */
    void setContactGroup(const Akonadi::Item &group);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

