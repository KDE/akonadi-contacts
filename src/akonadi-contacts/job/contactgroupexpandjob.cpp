/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupexpandjob.h"
#include "akonadi_contact_debug.h"
#include "job/contactgroupsearchjob.h"
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemSearchJob>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactGroupExpandJob::Private
{
public:
    Private(const KContacts::ContactGroup &group, ContactGroupExpandJob *parent)
        : mParent(parent)
        , mGroup(group)
    {
    }

    Private(const QString &name, ContactGroupExpandJob *parent)
        : mParent(parent)
        , mName(name)
    {
    }

    void resolveGroup()
    {
        for (int i = 0, total = mGroup.dataCount(); i < total; ++i) {
            const KContacts::ContactGroup::Data data = mGroup.data(i);

            KContacts::Addressee contact;
            contact.setNameFromString(data.name());
            contact.insertEmail(data.email(), true);

            mContacts.append(contact);
        }

        for (int i = 0, total = mGroup.contactReferenceCount(); i < total; ++i) {
            const KContacts::ContactGroup::ContactReference reference = mGroup.contactReference(i);

            Item item;
            if (!reference.gid().isEmpty()) {
                item.setGid(reference.gid());
            } else {
                item.setId(reference.uid().toLongLong());
            }
            auto job = new ItemFetchJob(item, mParent);
            job->fetchScope().fetchFullPayload();
            job->setProperty("preferredEmail", reference.preferredEmail());

            mParent->connect(job, &ItemFetchJob::result, mParent, [this](KJob *job) {
                fetchResult(job);
            });

            mFetchCount++;
        }

        if (mFetchCount == 0) { // nothing to fetch, so we can return immediately
            mParent->emitResult();
        }
    }

    void searchResult(KJob *job)
    {
        if (job->error()) {
            mParent->setError(job->error());
            mParent->setErrorText(job->errorText());
            mParent->emitResult();
            return;
        }

        auto searchJob = qobject_cast<ContactGroupSearchJob *>(job);

        if (searchJob->contactGroups().isEmpty()) {
            mParent->emitResult();
            return;
        }

        mGroup = searchJob->contactGroups().at(0);
        resolveGroup();
    }

    void fetchResult(KJob *job)
    {
        const ItemFetchJob *fetchJob = qobject_cast<ItemFetchJob *>(job);

        const Item::List items = fetchJob->items();
        if (!items.isEmpty()) {
            const QString email = fetchJob->property("preferredEmail").toString();

            const Item item = items.first();
            if (item.hasPayload<KContacts::Addressee>()) {
                auto contact = item.payload<KContacts::Addressee>();
                if (!email.isEmpty()) {
                    contact.insertEmail(email, true);
                }

                mContacts.append(contact);
            } else {
                qCWarning(AKONADICONTACT_LOG) << "Contact for Akonadi item" << item.id() << "does not exist anymore!";
            }
        }

        mFetchCount--;

        if (mFetchCount == 0) {
            mParent->emitResult();
        }
    }

    ContactGroupExpandJob *const mParent;
    KContacts::ContactGroup mGroup;
    QString mName;
    KContacts::Addressee::List mContacts;

    int mFetchCount = 0;
};

ContactGroupExpandJob::ContactGroupExpandJob(const KContacts::ContactGroup &group, QObject *parent)
    : KJob(parent)
    , d(new Private(group, this))
{
}

ContactGroupExpandJob::ContactGroupExpandJob(const QString &name, QObject *parent)
    : KJob(parent)
    , d(new Private(name, this))
{
}

ContactGroupExpandJob::~ContactGroupExpandJob() = default;

void ContactGroupExpandJob::start()
{
    if (!d->mName.isEmpty() && !d->mName.contains(QLatin1Char('@'))) {
        // we have to search the contact group first
        auto searchJob = new ContactGroupSearchJob(this);
        searchJob->setQuery(ContactGroupSearchJob::Name, d->mName);
        searchJob->setLimit(1);
        connect(searchJob, &ContactGroupSearchJob::result, this, [this](KJob *job) {
            d->searchResult(job);
        });
    } else {
        QMetaObject::invokeMethod(
            this,
            [this]() {
                d->resolveGroup();
            },
            Qt::QueuedConnection);
    }
}

KContacts::Addressee::List ContactGroupExpandJob::contacts() const
{
    return d->mContacts;
}

#include "moc_contactgroupexpandjob.cpp"
