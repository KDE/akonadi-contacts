/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDEMAILADDRESSJOB_H
#define ADDEMAILADDRESSJOB_H

#include "akonadi-contact_export.h"

#include <KJob>

namespace Akonadi
{
class Item;
/**
 * @short A job to add a new contact with a given email address to Akonadi.
 *
 * The job will check whether a contact with the given email address already
 * exists in Akonadi and inform the user about it, if it does not exist yet,
 * a new contact is added.
 */
class AKONADI_CONTACT_EXPORT AddEmailAddressJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Creates a new add email address job.
     *
     * @param email The email address.
     * @param parentWidget The widget that will be used as parent for dialog.
     * @param parent The parent object.
     */
    explicit AddEmailAddressJob(const QString &email, QWidget *parentWidget, QObject *parent = nullptr);

    /**
     * Destroys the add email address job.
     */
    ~AddEmailAddressJob() override;

    /**
     * Starts the job.
     */
    void start() override;

    /**
     * Returns the item that represents the new contact.
     */
    Q_REQUIRED_RESULT Akonadi::Item contact() const;

    void setInteractive(bool b);
Q_SIGNALS:
    void successMessage(const QString &message);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
