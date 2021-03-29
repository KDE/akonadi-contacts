/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <KJob>

namespace Akonadi
{
/**
 * @short A job to open the contact editor for a contact with a given email address.
 *
 * The job will check whether a contact with the given email address already
 * exists in Akonadi. If not, it will add a new contact with the email address
 * to Akonadi and then opens the contact editor.
 */
class AKONADI_CONTACT_EXPORT OpenEmailAddressJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Creates a new open email address job.
     *
     * @param email The email address to open.
     * @param parentWidget The widget that will be used as parent for dialog.
     * @param parent The parent object.
     */
    explicit OpenEmailAddressJob(const QString &email, QWidget *parentWidget, QObject *parent = nullptr);

    /**
     * Destroys the open email address job.
     */
    ~OpenEmailAddressJob() override;

    /**
     * Starts the job.
     */
    void start() override;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

