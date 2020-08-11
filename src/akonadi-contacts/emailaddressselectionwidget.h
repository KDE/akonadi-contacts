/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_EMAILADDRESSSELECTIONWIDGET_H
#define AKONADI_EMAILADDRESSSELECTIONWIDGET_H

#include "akonadi-contact_export.h"

#include "emailaddressselection.h"

#include <item.h>

#include <QAbstractItemView>
#include <QWidget>

class QLineEdit;
class QAbstractItemModel;
class QTreeView;

namespace Akonadi {
/**
 * @short A widget to select email addresses from Akonadi.
 *
 * This widget allows the user to select an name and email address from
 * the Akonadi storage.
 * The selected addresses are returned as EmailAddressSelectionWidget::Selection objects
 * which encapsulate the name, email address and the Akonadi item that has been selected.
 *
 * Example:
 *
 * @code
 *
 * Akonadi::EmailAddressSelectionWidget *widget = new Akonadi::EmailAddressSelectionWidget( this );
 * widget->view()->setSelectionMode( QAbstractItemView::MultiSelection );
 * ...
 *
 * foreach ( const Akonadi::EmailAddressSelection &selection, widget->selectedAddresses() ) {
 *   qCDebug(AKONADICONTACT_LOG) << "Name:" << selection.name() << "Email:" << selection.email();
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT EmailAddressSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Creates a new email address selection widget.
     *
     * @param parent The parent widget.
     */
    explicit EmailAddressSelectionWidget(QWidget *parent = nullptr);

    /**
     * Creates a new email address selection widget.
     *
     * @param model A custom, ContactsTreeModel based model to use.
     * @param parent The parent widget.
     */
    explicit EmailAddressSelectionWidget(QAbstractItemModel *model, QWidget *parent = nullptr);

    /**
     * @brief Creates a new email address selection widget.
     * @param showOnlyContactWithEmail Allow to specify if you want to see only contact with email (by default yes in other constructor)
     * @param model A custom ContactsTreeModel based model to use.
     * @param parent The parent widget.
     */
    explicit EmailAddressSelectionWidget(bool showOnlyContactWithEmail, QAbstractItemModel *model = nullptr, QWidget *parent = nullptr);

    /**
     * Destroys the email address selection widget.
     */
    ~EmailAddressSelectionWidget();

    /**
     * Returns the list of selected email addresses.
     */
    Q_REQUIRED_RESULT EmailAddressSelection::List selectedAddresses() const;

    /**
     * Returns the line edit that is used for the search line.
     */
    QLineEdit *searchLineEdit() const;

    /**
     * Returns the tree view that is used to list the items.
     */
    QTreeView *view() const;

Q_SIGNALS:
    /**
     * @since 4.10.1
     */
    void doubleClicked();
private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
