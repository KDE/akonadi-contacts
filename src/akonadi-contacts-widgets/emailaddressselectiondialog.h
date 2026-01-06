/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include "abstractemailaddressselectiondialog.h"
#include "emailaddressselectionwidget.h"

#include <memory>

namespace Akonadi
{
class EmailAddressSelectionDialogPrivate;

/*!
 * \brief A dialog to select email addresses from Akonadi.
 *
 * This dialog allows the user to select an name and email address from
 * the Akonadi storage.
 * The selected addresses are returned as EmailAddressSelectionWidget::Selection objects
 * which encapsulate the name, email address and the Akonadi item that has been selected.
 *
 * Example:
 *
 * \code
 *
 * Akonadi::EmailAddressSelectionDialog dlg( this );
 * if ( dlg.exec() ) {
 *   const Akonadi::EmailAddressSelectionWidget::Selection::List selections = dlg.selectedAddresses();
 *   foreach ( const Akonadi::EmailAddressSelectionWidget::Selection &selection, selections ) {
 *     qCDebug(AKONADICONTACT_LOG) << "Name:" << selection.name() << "Email:" << selection.email();
 *   }
 * }
 *
 * \endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * \since 4.5
 */
class AKONADI_CONTACT_WIDGETS_EXPORT EmailAddressSelectionDialog : public AbstractEmailAddressSelectionDialog
{
    Q_OBJECT

public:
    /*!
     * Creates a new email address selection dialog.
     *
     * \a parent The parent widget.
     */
    explicit EmailAddressSelectionDialog(QWidget *parent = nullptr);

    /*!
     * Creates a new email address selection dialog.
     *
     * \a model A custom, ContactsTreeModel based model to use.
     * \a parent The parent widget.
     */
    explicit EmailAddressSelectionDialog(QAbstractItemModel *model, QWidget *parent = nullptr);

    /*!
     * Destroys the email address selection dialog.
     */
    ~EmailAddressSelectionDialog() override;

    /*!
     * Returns the list of selected email addresses.
     */
    [[nodiscard]] Akonadi::EmailAddressSelection::List selectedAddresses() const override;

    /*!
     * Returns the email address selection view that is used.
     */
    [[nodiscard]] Akonadi::EmailAddressSelectionWidget *view() const override;

private:
    std::unique_ptr<EmailAddressSelectionDialogPrivate> const d;
};
}
