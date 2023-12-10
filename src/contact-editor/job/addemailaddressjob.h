/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_export.h"
#include <Akonadi/Item>
#include <KJob>

#include <memory>

namespace ContactEditor
{
class Item;
class AddEmailAddressJobPrivate;

/**
 * @short A job to add a new contact with a given email address to Akonadi.
 *
 * The job will check whether a contact with the given email address already
 * exists in Akonadi and inform the user about it, if it does not exist yet,
 * a new contact is added.
 */
class CONTACTEDITOR_EXPORT AddEmailAddressJob : public KJob
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
    friend class AddEmailAddressJobPrivate;
    std::unique_ptr<AddEmailAddressJobPrivate> const d;
    //@endcond
};
}