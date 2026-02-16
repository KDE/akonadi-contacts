/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include <KJob>

#include <memory>

namespace KContacts
{
class Addressee;
}

namespace Akonadi
{
class Collection;
}
namespace Akonadi
{
class AddContactJobPrivate;

/*!
 * \class Akonadi::AddContactJob
 * \brief A job to add a new contact to Akonadi.
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/AddContactJob
 *
 * The job will check whether a contact with the given email address already
 * exists in Akonadi and adds it if it does not exist yet.
 */
class AKONADI_CONTACT_WIDGETS_EXPORT AddContactJob : public KJob
{
    Q_OBJECT

public:
    /*!
     * Creates a new add contact job.
     *
     * If the contact is not found, the user will be presented a dialog to
     * choose the address book where the new contact shall be stored.
     *
     * \a contact The contact to add.
     * \a parentWidget The widget that will be used as parent for dialog.
     * \a parent The parent object.
     */
    AddContactJob(const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent = nullptr);

    /*!
     * Creates a new add contact job.
     *
     * \a contact The contact to add.
     * \a collection The address book collection where the contact shall be stored in.
     * \a parent The parent object.
     */
    AddContactJob(const KContacts::Addressee &contact, const Akonadi::Collection &collection, QObject *parent = nullptr);

    /*!
     * Destroys the add email address job.
     */
    ~AddContactJob() override;

    /*!
     * Starts the job.
     */
    void start() override;

    /*!
     * Sets whether a message box should be shown for the result.
     *
     * \a b Whether to show a message box.
     */
    void showMessageBox(bool b);

private:
    friend class AddContactJobPrivate;
    std::unique_ptr<AddContactJobPrivate> const d;
};
}
