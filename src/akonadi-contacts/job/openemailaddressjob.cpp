/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "openemailaddressjob.h"

#include "job/addemailaddressjob.h"

#include <Akonadi/CollectionDialog>
#include <Akonadi/Contact/ContactEditorDialog>
#include <Akonadi/Contact/ContactSearchJob>
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <QPointer>
#include <kcontacts/addressee.h>

using namespace Akonadi;

class Q_DECL_HIDDEN OpenEmailAddressJob::Private
{
public:
    Private(OpenEmailAddressJob *qq, const QString &emailString, QWidget *parentWidget)
        : q(qq)
        , mCompleteAddress(emailString)
        , mParentWidget(parentWidget)
    {
        KContacts::Addressee::parseEmailAddress(emailString, mName, mEmail);
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

        const Akonadi::Item::List contacts = searchJob->items();
        if (!contacts.isEmpty()) {
            // open the editor with the matching item
            QPointer<Akonadi::ContactEditorDialog> dlg = new Akonadi::ContactEditorDialog(Akonadi::ContactEditorDialog::EditMode, mParentWidget);
            dlg->setContact(contacts.first());
            dlg->exec();
            delete dlg;

            q->emitResult();
            return;
        }

        auto createJob = new AddEmailAddressJob(mCompleteAddress, mParentWidget, q);
        q->connect(createJob, &AddEmailAddressJob::result, q, [this](KJob *job) {
            slotAddContactDone(job);
        });
        createJob->start();
    }

    void slotAddContactDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }

        const AddEmailAddressJob *createJob = qobject_cast<AddEmailAddressJob *>(job);

        // open the editor with the matching item
        QPointer<Akonadi::ContactEditorDialog> dlg = new Akonadi::ContactEditorDialog(Akonadi::ContactEditorDialog::EditMode, mParentWidget);
        dlg->setContact(createJob->contact());
        dlg->exec();
        delete dlg;

        q->emitResult();
    }

    OpenEmailAddressJob *const q;
    const QString mCompleteAddress;
    QString mEmail;
    QString mName;
    QWidget *const mParentWidget;
};

OpenEmailAddressJob::OpenEmailAddressJob(const QString &email, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , d(new Private(this, email, parentWidget))
{
}

OpenEmailAddressJob::~OpenEmailAddressJob()
{
    delete d;
}

void OpenEmailAddressJob::start()
{
    // first check whether a contact with the same email exists already
    auto searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, d->mEmail.toLower(), Akonadi::ContactSearchJob::ExactMatch);
    connect(searchJob, &Akonadi::ContactSearchJob::result, this, [this](KJob *job) {
        d->slotSearchDone(job);
    });
}

#include "moc_openemailaddressjob.cpp"
