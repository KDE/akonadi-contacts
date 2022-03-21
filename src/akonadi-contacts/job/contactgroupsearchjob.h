/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <Akonadi/Item>
#include <Akonadi/ItemSearchJob>
#include <KContacts/ContactGroup>

#include <memory>

namespace Akonadi
{
class ContactGroupSearchJobPrivate;

/**
 * @short Job that searches for contact groups in the Akonadi storage.
 *
 * This job searches for contact groups that match given search criteria and returns
 * the list of contact groups.
 *
 * @code
 *
 * Akonadi::ContactGroupSearchJob *job = new Akonadi::ContactGroupSearchJob();
 * job->setQuery( Akonadi::ContactGroupSearchJob::Name, "Family Members" );
 * connect( job, SIGNAL(result(KJob*)), this, SLOT(searchResult(KJob*)) );
 *
 * ...
 *
 * MyClass::searchResult( KJob *job )
 * {
 *   Akonadi::ContactGroupSearchJob *searchJob = qobject_cast<Akonadi::ContactGroupSearchJob*>( job );
 *   const KContacts::ContactGroup::List contactGroups = searchJob->contactGroups();
 *   // do something with the contact groups
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupSearchJob : public ItemSearchJob
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group search job.
     *
     * @param parent The parent object.
     */
    explicit ContactGroupSearchJob(QObject *parent = nullptr);

    /**
     * Destroys the contact group search job.
     */
    ~ContactGroupSearchJob() override;

    /**
     * Describes the criteria that can be searched for.
     */
    enum Criterion {
        Name ///< The name of the contact group.
    };

    /**
     * Describes the type of pattern matching that shall be used.
     *
     * @since 4.5
     */
    enum Match {
        ExactMatch, ///< The result must match exactly the pattern (case sensitive).
        StartsWithMatch, ///< The result must start with the pattern (case insensitive).
        ContainsMatch ///< The result must contain the pattern (case insensitive).
    };

    /**
     * Sets the @p criterion and @p value for the search.
     */
    void setQuery(Criterion criterion, const QString &value);

    /**
     * Sets the @p criterion and @p value for the search with @p match.
     * @param criterion the query criterion to compare with
     * @param value the value to match against
     * @param match how to match the given value
     * @since 4.5
     */
    void setQuery(Criterion criterion, const QString &value, Match match);

    /**
     * Sets a @p limit on how many results will be returned by this search job.
     * This is useful in situation where for example only the first search result is needed anyway,
     * setting a limit of 1 here will greatly reduce the resource usage during the
     * search.
     * @param limit the limit to set
     * @note this needs to be called before calling setQuery() to have an effect.
     * By default, the number of results is unlimited.
     *
     * @since 4.4.3
     */
    void setLimit(int limit);

    /**
     * Returns the contact groups that matched the search criteria.
     */
    Q_REQUIRED_RESULT KContacts::ContactGroup::List contactGroups() const;

private:
    //@cond PRIVATE
    std::unique_ptr<ContactGroupSearchJobPrivate> const d;
    //@endcond
};
}
