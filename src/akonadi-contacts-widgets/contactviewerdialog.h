/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <QDialog>

#include <memory>

namespace Akonadi
{
class Item;
class ContactViewer;
class ContactViewerDialogPrivate;

/*!
 * \brief A dialog for displaying a contact in Akonadi.
 *
 * This dialog provides a way to show a contact from the
 * Akonadi storage.
 *
 * Example:
 *
 * \code
 *
 * using namespace Akonadi;
 *
 * const Item contact = ...
 *
 * ContactViewerDialog *dlg = new ContactViewerDialog( this );
 * dlg->setContact( contact );
 * dlg->show();
 *
 * \endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * \since 4.4
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactViewerDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * Creates a new contact viewer dialog.
     *
     * \a parent The parent widget of the dialog.
     */
    explicit ContactViewerDialog(QWidget *parent = nullptr);

    /*!
     * Destroys the contact viewer dialog.
     */
    ~ContactViewerDialog() override;

    /*!
     * Returns the contact that is currently displayed.
     */
    [[nodiscard]] Akonadi::Item contact() const;

    /*!
     * Returns the ContactViewer that is used by this dialog.
     */
    ContactViewer *viewer() const;

public Q_SLOTS:
    /*!
     * Sets the \a contact that shall be displayed in the dialog.
     */
    void setContact(const Akonadi::Item &contact);

private:
    std::unique_ptr<ContactViewerDialogPrivate> const d;
};
}
