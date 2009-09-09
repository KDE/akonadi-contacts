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

#ifndef AKONADI_CONTACTGROUPEDITORDIALOG_H
#define AKONADI_CONTACTGROUPEDITORDIALOG_H

#include "akonadi-contact_export.h"

#include <kdialog.h>

class QAbstractItemModel;

namespace Akonadi {

class Item;
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
 * Akonadi::ContactGroupEditorDialog dlg( Akonadi::ContactGroupEditorDialog::CreateMode, this );
 *
 * if ( dlg.exec() ) {
 *   qDebug() << "New contact group has been added to the address book";
 * } else {
 *   qDebug() << "User has canceled operation";
 * }
 *
 * @endcode
 *
 * Example for editing an existing contact group:
 *
 * @code
 *
 * const Akonadi::Item contactGroup = ...;
 *
 * Akonadi::ContactGroupEditorDialog dlg( Akonadi::ContactGroupEditorDialog::EditMode, this );
 * dlg.setContactGroup( contactGroup );
 *
 * if ( dlg.exec() ) {
 *   qDebug() << "Contact group has been edited";
 * } else {
 *   qDebug() << "User has canceled operation";
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupEditorDialog : public KDialog
{
  Q_OBJECT

  public:
    /**
     * Describes the mode of the contact group editor.
     */
    enum Mode
    {
      CreateMode, ///< Creates a new contact group
      EditMode    ///< Edits an existing contact group
    };

    /**
     * Creates a new contact group editor dialog.
     *
     * @param mode The mode of the dialog.
     * @param parent The parent widget of the dialog.
     */
    explicit ContactGroupEditorDialog( Mode mode, QWidget *parent = 0 );

    /**
     * Destroys the contact group editor dialog.
     */
    ~ContactGroupEditorDialog();

    /**
     * Sets the contact @p group to edit when in EditMode.
     */
    void setContactGroup( const Akonadi::Item &group );

  Q_SIGNALS:
    /**
     * This signal is emitted whenever a contact group was updated or stored.
     *
     * @param group The contact group.
     */
    void contactGroupStored( const Akonadi::Item &group );

  protected Q_SLOTS:
    virtual void slotButtonClicked( int button );

  private:
    //@cond PRIVATE
    class Private;
    Private* const d;
    //@endcond
};

}

#endif
