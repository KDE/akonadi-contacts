/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_CONTACTGROUPEXPANDJOB_H
#define AKONADI_CONTACTGROUPEXPANDJOB_H

#include "akonadi-contact_export.h"

#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>
#include <KJob>

namespace Akonadi {
/**
 * @short Job that expands a ContactGroup to a list of contacts.
 *
 * This job takes a KContacts::ContactGroup object or a name of a contact group and
 * expands it to a list of KContacts::Addressee objects by creating temporary KContacts::Addressee objects
 * for the KContacts::ContactGroup::Data objects of the group and fetching the
 * complete contacts from the Akonadi storage for the
 * KContacts::ContactGroup::ContactReferences of the group.
 *
 * @code
 *
 * const KContacts::ContactGroup group = ...;
 *
 * Akonadi::ContactGroupExpandJob *job = new Akonadi::ContactGroupExpandJob( group );
 * connect( job, SIGNAL(result(KJob*)), this, SLOT(expandResult(KJob*)) );
 * job->start();
 *
 * ...
 *
 * MyClass::expandResult( KJob *job )
 * {
 *   Akonadi::ContactGroupExpandJob *expandJob = qobject_cast<Akonadi::ContactGroupExpandJob*>( job );
 *   const KContacts::Addressee::List contacts = expandJob->contacts();
 *   // do something with the contacts
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupExpandJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group expand job.
     *
     * @param group The contact group to expand.
     * @param parent The parent object.
     */
    explicit ContactGroupExpandJob(const KContacts::ContactGroup &group, QObject *parent = nullptr);

    /**
     * Creates a new contact group expand job.
     *
     * @param name The name of the contact group to expand.
     * @param parent The parent object.
     *
     * @since 4.5
     */
    explicit ContactGroupExpandJob(const QString &name, QObject *parent = nullptr);

    /**
     * Destroys the contact group expand job.
     */
    ~ContactGroupExpandJob() override;

    /**
     * Returns the list of contacts.
     */
    Q_REQUIRED_RESULT KContacts::Addressee::List contacts() const;

    /**
     * Starts the expand job.
     */
    void start() override;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;

    //Already use with QMetaObject::invokeMethod
    Q_PRIVATE_SLOT(d, void resolveGroup())
    //@endcond
};
}

#endif
