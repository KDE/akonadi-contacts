/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef AKONADI_CONTACTVIEWERDIALOG_H
#define AKONADI_CONTACTVIEWERDIALOG_H

#include "akonadi-contact_export.h"

#include <kdialog.h>

class QUrl;

namespace KABC {
class Address;
class PhoneNumber;
}

namespace Akonadi {

class Item;

/**
 * @short A dialog for displaying a contact in Akonadi.
 *
 * This dialog provides a way to show a contact from the
 * Akonadi storage.
 *
 * Example:
 *
 * @code
 *
 * const Akonadi::Item contact = ...
 *
 * Akonadi::ContactViewerDialog dlg( this );
 * dlg.setContact( contact );
 * dlg.exec();
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactViewerDialog : public KDialog
{
  Q_OBJECT

  public:
    /**
     * Creates a new contact viewer dialog.
     *
     * @param parent The parent widget of the dialog.
     */
    explicit ContactViewerDialog( QWidget *parent = 0 );

    /**
     * Destroys the contact viewer dialog.
     */
    ~ContactViewerDialog();

    /**
     * Returns the contact that is currently displayed.
     */
    Akonadi::Item contact() const;

  public Q_SLOTS:
    /**
     * Sets the @p contact that shall be displayed in the dialog.
     */
    void setContact( const Akonadi::Item &contact );

  Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has clicked on
     * a url (e.g. homepage or blog url) in the viewer dialog.
     *
     * @param url The url that has been clicked.
     */
    void urlClicked( const QUrl &url );

    /**
     * This signal is emitted whenever the user has clicked on
     * an email address in the viewer dialog.
     *
     * @param name The name of the contact.
     * @param email The plain email address of the contact.
     */
    void emailClicked( const QString &name, const QString &email );

    /**
     * This signal is emitted whenever the user has clicked on a
     * phone number (that includes fax numbers as well) in the viewer dialog.
     *
     * @param number The corresponding phone number.
     */
    void phoneNumberClicked( const KABC::PhoneNumber &number );

    /**
     * This signal is emitted whenever the user has clicked on an
     * address in the viewer dialog.
     *
     * @param address The corresponding address.
     */
    void addressClicked( const KABC::Address &address );

  private:
    //@cond PRIVATE
    class Private;
    Private* const d;
    //@endcond
};

}

#endif
