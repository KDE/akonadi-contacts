/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDCONTACTJOB_H
#define ADDCONTACTJOB_H

#include "akonadi-contact_export.h"

#include <KJob>

namespace KContacts
{
class Addressee;
}

namespace Akonadi
{
class Collection;
/**
 * @short A job to add a new contact to Akonadi.
 *
 * The job will check whether a contact with the given email address already
 * exists in Akonadi and adds it if it does not exist yet.
 */
class AKONADI_CONTACT_EXPORT AddContactJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Creates a new add contact job.
     *
     * If the contact is not found, the user will be presented a dialog to
     * choose the address book where the new contact shall be stored.
     *
     * @param contact The contact to add.
     * @param parentWidget The widget that will be used as parent for dialog.
     * @param parent The parent object.
     */
    AddContactJob(const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent = nullptr);

    /**
     * Creates a new add contact job.
     *
     * @param contact The contact to add.
     * @param collection The address book collection where the contact shall be stored in.
     * @param parent The parent object.
     */
    AddContactJob(const KContacts::Addressee &contact, const Akonadi::Collection &collection, QObject *parent = nullptr);

    /**
     * Destroys the add email address job.
     */
    ~AddContactJob() override;

    /**
     * Starts the job.
     */
    void start() override;

    void showMessageBox(bool b);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
