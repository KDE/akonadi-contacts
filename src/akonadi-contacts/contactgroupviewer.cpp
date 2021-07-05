/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupviewer.h"

#include "job/contactgroupexpandjob.h"
#include "standardcontactgroupformatter.h"
#include "textbrowser_p.h"

#include <KColorScheme>
#include <collectionfetchjob.h>
#include <entitydisplayattribute.h>
#include <item.h>
#include <itemfetchjob.h>
#include <itemfetchscope.h>
#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>

#include <KLocalizedString>

#include <QIcon>
#include <QVBoxLayout>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactGroupViewer::Private
{
public:
    Private(ContactGroupViewer *parent)
        : mParent(parent)
    {
        mBrowser = new TextBrowser;

        static QPixmap groupPixmap = QIcon::fromTheme(QStringLiteral("x-mail-distribution-list")).pixmap(QSize(100, 100));
        mBrowser->document()->addResource(QTextDocument::ImageResource, QUrl(QStringLiteral("group_photo")), groupPixmap);

        mStandardContactGroupFormatter = new StandardContactGroupFormatter;
        mContactGroupFormatter = mStandardContactGroupFormatter;
    }

    ~Private()
    {
        delete mStandardContactGroupFormatter;
    }

    void updateView()
    {
        mParent->setWindowTitle(i18nc("@title:window", "Contact Group %1", mCurrentGroupName));

        KContacts::ContactGroup group;
        group.setName(mCurrentGroupName);
        for (const KContacts::Addressee &contact : std::as_const(mCurrentContacts)) {
            group.append(KContacts::ContactGroup::Data(contact.realName(), contact.preferredEmail()));
        }

        mContactGroupFormatter->setContactGroup(group);

        QVector<QVariantMap> additionalFields;

        if (!mCurrentAddressBookName.isEmpty()) {
            QVariantMap addressBookName;
            addressBookName.insert(QStringLiteral("title"), i18n("Address Book"));
            addressBookName.insert(QStringLiteral("value"), mCurrentAddressBookName);

            additionalFields << addressBookName;
        }

        mContactGroupFormatter->setAdditionalFields(additionalFields);

        mBrowser->setHtml(mContactGroupFormatter->toHtml());
    }

    void slotMailClicked(const QUrl &email)
    {
        QString name, address;

        // remove the 'mailto:' and split into name and email address
        KContacts::Addressee::parseEmailAddress(email.path(), name, address);

        Q_EMIT mParent->emailClicked(name, address);
    }

    void _k_expandResult(KJob *job)
    {
        mExpandJob = nullptr;

        if (!job->error()) {
            auto expandJob = qobject_cast<ContactGroupExpandJob *>(job);
            mCurrentContacts = expandJob->contacts();
        }

        // stop any running fetch job
        if (mParentCollectionFetchJob) {
            mParent->disconnect(mCollectionFetchJobConnection);
            delete mParentCollectionFetchJob;
            mParentCollectionFetchJob = nullptr;
        }

        mParentCollectionFetchJob = new CollectionFetchJob(mCurrentItem.parentCollection(), CollectionFetchJob::Base, mParent);
        mCollectionFetchJobConnection = mParent->connect(mParentCollectionFetchJob, &CollectionFetchJob::result, mParent, [this](KJob *job) {
            slotParentCollectionFetched(job);
        });
    }

    void slotParentCollectionFetched(KJob *job)
    {
        mParentCollectionFetchJob = nullptr;
        mCurrentAddressBookName.clear();

        if (!job->error()) {
            auto fetchJob = qobject_cast<CollectionFetchJob *>(job);
            if (!fetchJob->collections().isEmpty()) {
                const Collection collection = fetchJob->collections().at(0);
                mCurrentAddressBookName = collection.displayName();
            }
        }

        updateView();
    }

    QMetaObject::Connection mCollectionFetchJobConnection;
    QMetaObject::Connection mJobConnection;
    ContactGroupViewer *mParent = nullptr;
    TextBrowser *mBrowser = nullptr;
    QString mCurrentGroupName;
    KContacts::Addressee::List mCurrentContacts;
    QString mCurrentAddressBookName;
    Item mCurrentItem;
    ContactGroupExpandJob *mExpandJob = nullptr;
    CollectionFetchJob *mParentCollectionFetchJob = nullptr;
    AbstractContactGroupFormatter *mStandardContactGroupFormatter = nullptr;
    AbstractContactGroupFormatter *mContactGroupFormatter = nullptr;
};

ContactGroupViewer::ContactGroupViewer(QWidget *parent)
    : QWidget(parent)
    , d(new Private(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    connect(d->mBrowser, &TextBrowser::anchorClicked, this, [this](const QUrl &url) {
        d->slotMailClicked(url);
    });

    layout->addWidget(d->mBrowser);

    // always fetch full payload for contact groups
    fetchScope().fetchFullPayload();
    fetchScope().setAncestorRetrieval(ItemFetchScope::Parent);
}

ContactGroupViewer::~ContactGroupViewer()
{
    delete d;
}

Akonadi::Item ContactGroupViewer::contactGroup() const
{
    return ItemMonitor::item();
}

void ContactGroupViewer::setContactGroup(const Akonadi::Item &group)
{
    ItemMonitor::setItem(group);
}

void ContactGroupViewer::setContactGroupFormatter(AbstractContactGroupFormatter *formatter)
{
    if (formatter == nullptr) {
        d->mContactGroupFormatter = d->mStandardContactGroupFormatter;
    } else {
        d->mContactGroupFormatter = formatter;
    }
}

void ContactGroupViewer::itemChanged(const Item &item)
{
    if (!item.hasPayload<KContacts::ContactGroup>()) {
        return;
    }

    const auto group = item.payload<KContacts::ContactGroup>();
    d->mCurrentGroupName = group.name();
    d->mCurrentItem = item;

    if (d->mExpandJob) {
        disconnect(d->mJobConnection);
        d->mExpandJob->kill();
    }

    d->mExpandJob = new ContactGroupExpandJob(group);
    d->mJobConnection = connect(d->mExpandJob, &ContactGroupExpandJob::result, this, [this](KJob *job) {
        d->_k_expandResult(job);
    });
    d->mExpandJob->start();
}

void ContactGroupViewer::itemRemoved()
{
    d->mBrowser->clear();
}

#include "moc_contactgroupviewer.cpp"
