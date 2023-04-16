/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "openemailaddressjob.h"

#include "job/addemailaddressjob.h"

#include <Akonadi/CollectionDialog>
#include <Akonadi/ContactEditorDialog>
#include <Akonadi/ContactSearchJob>
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <KContacts/Addressee>
#include <QPointer>

using namespace AkonadiContactWidgets;

class AkonadiContactWidgets::OpenEmailAddressJobPrivate
{
public:
    OpenEmailAddressJobPrivate(OpenEmailAddressJob *qq, const QString &emailString, QWidget *parentWidget)
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
            QPointer<AkonadiContactWidgets::ContactEditorDialog> dlg =
                new AkonadiContactWidgets::ContactEditorDialog(AkonadiContactWidgets::ContactEditorDialog::EditMode, mParentWidget);
            dlg->setContact(contacts.first());
            dlg->exec();
            delete dlg;

            q->emitResult();
            return;
        }

        auto createJob = new AkonadiContactWidgets::AddEmailAddressJob(mCompleteAddress, mParentWidget, q);
        q->connect(createJob, &AkonadiContactWidgets::AddEmailAddressJob::result, q, [this](KJob *job) {
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

        const AkonadiContactWidgets::AddEmailAddressJob *createJob = qobject_cast<AkonadiContactWidgets::AddEmailAddressJob *>(job);

        // open the editor with the matching item
        QPointer<AkonadiContactWidgets::ContactEditorDialog> dlg =
            new AkonadiContactWidgets::ContactEditorDialog(AkonadiContactWidgets::ContactEditorDialog::EditMode, mParentWidget);
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
    , d(new OpenEmailAddressJobPrivate(this, email, parentWidget))
{
}

OpenEmailAddressJob::~OpenEmailAddressJob() = default;

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
