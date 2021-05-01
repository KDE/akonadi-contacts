/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addcontactjob.h"
#include "akonadi/contact/selectaddressbookdialog.h"
#include <Collection>

#include <Akonadi/Contact/ContactSearchJob>
#include <KLocalizedString>
#include <KMessageBox>
#include <item.h>
#include <itemcreatejob.h>
#include <kcontacts/addressee.h>

#include <QPointer>

using namespace Akonadi;

class Q_DECL_HIDDEN AddContactJob::Private
{
public:
    Private(AddContactJob *qq, const KContacts::Addressee &contact, QWidget *parentWidget)
        : q(qq)
        , mContact(contact)
        , mParentWidget(parentWidget)
    {
    }

    Private(AddContactJob *qq, const KContacts::Addressee &contact, const Akonadi::Collection &collection)
        : q(qq)
        , mContact(contact)
        , mCollection(collection)
    {
    }

    void slotSearchDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }

        const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);

        const KContacts::Addressee::List contacts = searchJob->contacts();

        if (!contacts.isEmpty()) { // contact is already part of the address book...
            if (mShowMessageBox) {
                const QString text = i18nc("@info",
                                           "The vCard's primary email address is already in "
                                           "your address book; however, you may save the vCard into "
                                           "a file and import it into the address book manually.");
                KMessageBox::information(mParentWidget, text);
            }
            q->setError(UserDefinedError);
            q->emitResult();
            return;
        }

        if (!mCollection.isValid()) {
            // ask user in which address book the new contact shall be stored
            QPointer<Akonadi::SelectAddressBookDialog> dlg = new Akonadi::SelectAddressBookDialog(mParentWidget);

            bool gotIt = true;
            if (!dlg->exec()) {
                q->setError(UserDefinedError);
                q->emitResult();
                gotIt = false;
            } else {
                mCollection = dlg->selectedCollection();
            }
            delete dlg;
            if (!gotIt) {
                return;
            }
        }

        if (mCollection.isValid()) {
            // create the new item
            Akonadi::Item item;
            item.setMimeType(KContacts::Addressee::mimeType());
            item.setPayload<KContacts::Addressee>(mContact);

            // save the new item in akonadi storage
            auto job = new Akonadi::ItemCreateJob(item, mCollection);
            q->connect(job, &Akonadi::ItemCreateJob::result, q, [this](KJob *job) {
                slotAddContactDone(job);
            });
        } else {
            q->setError(UserDefinedError);
            q->emitResult();
        }
    }

    void slotAddContactDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }

        if (mShowMessageBox) {
            const QString text = i18nc("@info",
                                       "The vCard was added to your address book; "
                                       "you can add more information to this "
                                       "entry by opening the address book.");
            KMessageBox::information(mParentWidget, text, QString(), QStringLiteral("addedtokabc"));
        }
        q->emitResult();
    }

    AddContactJob *const q;
    const KContacts::Addressee mContact;
    QWidget *mParentWidget = nullptr;
    Akonadi::Collection mCollection;
    bool mShowMessageBox = true;
};

AddContactJob::AddContactJob(const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , d(new Private(this, contact, parentWidget))
{
}

AddContactJob::AddContactJob(const KContacts::Addressee &contact, const Akonadi::Collection &collection, QObject *parent)
    : KJob(parent)
    , d(new Private(this, contact, collection))
{
}

AddContactJob::~AddContactJob()
{
    delete d;
}

void AddContactJob::showMessageBox(bool b)
{
    d->mShowMessageBox = b;
}

void AddContactJob::start()
{
    // first check whether a contact with the same email exists already
    auto searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, d->mContact.preferredEmail().toLower(), Akonadi::ContactSearchJob::ExactMatch);

    connect(searchJob, &Akonadi::ContactSearchJob::result, this, [this](KJob *job) {
        d->slotSearchDone(job);
    });
}

#include "moc_addcontactjob.cpp"
