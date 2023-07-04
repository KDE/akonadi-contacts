/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include <Akonadi/ItemSearchJob>
#include <KContacts/Addressee>

#include <memory>

namespace Akonadi
{
class ContactSearchJobPrivate;

/**
 * @short Job that searches for contacts in the Akonadi storage.
 *
 * This job searches for contacts that match given search criteria and returns
 * the list of contacts.
 *
 * Examples:
 *
 * @code
 *
 * // Search all contacts with email address tokoe@kde.org
 * Akonadi::ContactSearchJob *job = new Akonadi::ContactSearchJob();
 * job->setQuery( Akonadi::ContactSearchJob::Email, "tokoe@kde.org" );
 * connect( job, SIGNAL(result(KJob*)), this, SLOT(searchResult(KJob*)) );
 *
 * ...
 *
 * MyClass::searchResult( KJob *job )
 * {
 *   Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob*>( job );
 *   const KContacts::Addressee::List contacts = searchJob->contacts();
 *   // do something with the contacts
 * }
 *
 * @endcode
 *
 * @code
 *
 * // Search for all existing contacts
 * Akonadi::ContactSearchJob *job = new Akonadi::ContactSearchJob();
 * connect( job, SIGNAL(result(KJob*)), this, SLOT(searchResult(KJob*)) );
 *
 * ...
 *
 * MyClass::searchResult( KJob *job )
 * {
 *   Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob*>( job );
 *   const KContacts::Addressee::List contacts = searchJob->contacts();
 *   // do something with the contacts
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_CORE_EXPORT ContactSearchJob : public ItemSearchJob
{
    Q_OBJECT

public:
    /**
     * Creates a new contact search job.
     *
     * @param parent The parent object.
     */
    explicit ContactSearchJob(QObject *parent = nullptr);

    /**
     * Destroys the contact search job.
     */
    ~ContactSearchJob() override;

    /**
     * Describes the criteria that can be searched for.
     */
    enum Criterion {
        Name, ///< The name of the contact.
        Email, ///< The email address of the contact.
        NickName, ///< The nickname of the contact.
        NameOrEmail, ///< The name or email address of the contact. @since 4.5
        ContactUid ///< The global unique identifier of the contact. @since 4.5
    };

    /**
     * Describes the type of pattern matching that shall be used.
     *
     * @since 4.5
     */
    enum Match {
        ExactMatch, ///< The result must match exactly the pattern (case sensitive).
        StartsWithMatch, ///< The result must start with the pattern (case insensitive).
        ContainsMatch, ///< The result must contain the pattern (case insensitive).
        ContainsWordBoundaryMatch ///< The result must contain a word starting with the pattern (case insensitive).
    };

    /**
     * Sets the @p criterion and @p value for the search with @p match.
     * @param criterion the query criterion to compare with
     * @param value the value to match against
     * @param match how to match the given value
     * @since 4.5
     */
    void setQuery(Criterion criterion, const QString &value, Match match = ExactMatch);

    /**
     * Sets a @p limit on how many results will be returned by this search job.
     *
     * This is useful in situation where for example only the first search result is needed anyway,
     * setting a limit of 1 here will greatly reduce the resource usage during the
     * search.
     * This needs to be called before calling setQuery() to have an effect.
     * By default, the number of results is unlimited.
     * @param limit the upper limit for number of search results
     */
    void setLimit(int limit);

    /**
     * Returns the contacts that matched the search criteria.
     */
    Q_REQUIRED_RESULT KContacts::Addressee::List contacts() const;

private:
    //@cond PRIVATE
    std::unique_ptr<ContactSearchJobPrivate> const d;
    //@endcond
};
}
