/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addemaildisplayjob.h"
#include "akonadi/contact/selectaddressbookdialog.h"

#include <CollectionDialog>
#include <Akonadi/Contact/ContactSearchJob>
#include <Item>
#include <ItemCreateJob>
#include <ItemModifyJob>
#include <CollectionFetchJob>
#include <CollectionFetchScope>
#include <Collection>
#include <Akonadi/Contact/ContactEditorDialog>
#include <AgentTypeDialog>
#include <AgentType>
#include <AgentFilterProxyModel>
#include <AgentInstanceCreateJob>

#include <KContacts/ContactGroup>
#include <KLocalizedString>
#include <KMessageBox>

#include <QPointer>

using namespace Akonadi;

class Q_DECL_HIDDEN AddEmailDisplayJob::Private
{
public:
    Private(AddEmailDisplayJob *qq, const QString &emailString, QWidget *parentWidget)
        : q(qq)
        , mCompleteAddress(emailString)
        , mParentWidget(parentWidget)
    {
        KContacts::Addressee::parseEmailAddress(emailString, mName, mEmail);
    }

    void slotResourceCreationDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }
        createContact();
    }

    void searchContact()
    {
        // first check whether a contact with the same email exists already
        auto *searchJob = new Akonadi::ContactSearchJob(q);
        searchJob->setLimit(1);
        searchJob->setQuery(Akonadi::ContactSearchJob::Email, mEmail.toLower(),
                            Akonadi::ContactSearchJob::ExactMatch);
        q->connect(searchJob, &Akonadi::ContactSearchJob::result, q, [this](KJob *job) {
            slotSearchDone(job);
        });
    }

    void modifyContact()
    {
        Akonadi::Item item = contact;
        if (item.hasPayload<KContacts::Addressee>()) {
            KContacts::Addressee address = item.payload<KContacts::Addressee>();
            address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailPreferedFormatting"), mShowAsHTML ? QStringLiteral("HTML") : QStringLiteral("TEXT"));
            address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailAllowToRemoteContent"), mRemoteContent ? QStringLiteral("TRUE") : QStringLiteral("FALSE"));
            item.setPayload<KContacts::Addressee>(address);
            auto *itemModifyJob = new Akonadi::ItemModifyJob(item);
            q->connect(itemModifyJob, &Akonadi::ItemModifyJob::result, q, [this](KJob *itemModifyJob) {
                auto *modifiedJob = static_cast<Akonadi::ItemModifyJob *>(itemModifyJob);
                if (!modifiedJob->error()) {
                    Q_EMIT q->contactUpdated(modifiedJob->item(), messageId, mShowAsHTML, mRemoteContent);
                }
                slotAddModifyContactDone(itemModifyJob);
            });
        } else {
            searchContact();
        }
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

        const Akonadi::Item::List items = searchJob->items();
        if (items.isEmpty()) {
            createContact();
        } else {
            Akonadi::Item item = items.at(0);
            KContacts::Addressee contact = searchJob->contacts().at(0);
            contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailPreferedFormatting"), mShowAsHTML ? QStringLiteral("HTML") : QStringLiteral("TEXT"));
            contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailAllowToRemoteContent"), mRemoteContent ? QStringLiteral("TRUE") : QStringLiteral("FALSE"));
            item.setPayload<KContacts::Addressee>(contact);
            auto *itemModifyJob = new Akonadi::ItemModifyJob(item);
            q->connect(itemModifyJob, &Akonadi::ItemModifyJob::result, q, [this](KJob *itemModifyJob) {
                auto *modifiedJob = static_cast<Akonadi::ItemModifyJob *>(itemModifyJob);
                if (!modifiedJob->error()) {
                    Q_EMIT q->contactUpdated(modifiedJob->item(), messageId, mShowAsHTML, mRemoteContent);
                }
                slotAddModifyContactDone(itemModifyJob);
            });
        }
    }

    void createContact()
    {
        const QStringList mimeTypes(KContacts::Addressee::mimeType());

        Akonadi::CollectionFetchJob *const addressBookJob
            = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(),
                                              Akonadi::CollectionFetchJob::Recursive);

        addressBookJob->fetchScope().setContentMimeTypes(mimeTypes);
        q->connect(addressBookJob, &Akonadi::CollectionFetchJob::result, q, [this](KJob *job) {
            slotCollectionsFetched(job);
        });
    }

    void slotCollectionsFetched(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }

        const Akonadi::CollectionFetchJob *addressBookJob
            = qobject_cast<Akonadi::CollectionFetchJob *>(job);

        Akonadi::Collection::List canCreateItemCollections;
        const Akonadi::Collection::List colsList = addressBookJob->collections();
        for (const Akonadi::Collection &collection : colsList) {
            if (Akonadi::Collection::CanCreateItem &collection.rights()) {
                canCreateItemCollections.append(collection);
            }
        }

        Akonadi::Collection addressBook;

        const int nbItemCollection(canCreateItemCollections.size());
        if (nbItemCollection == 0) {
            if (KMessageBox::questionYesNo(
                    mParentWidget,
                    i18nc("@info",
                          "You must create an address book before adding a contact. Do you want to create an address book?"),
                    i18nc("@title:window", "No Address Book Available")) == KMessageBox::Yes) {
                QPointer<Akonadi::AgentTypeDialog> dlg = new Akonadi::AgentTypeDialog(mParentWidget);
                dlg->setWindowTitle(i18nc("@title:window", "Add Address Book"));
                dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
                dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::ContactGroup::mimeType());
                dlg->agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

                if (dlg->exec()) {
                    const Akonadi::AgentType agentType = dlg->agentType();

                    if (agentType.isValid()) {
                        auto *job = new Akonadi::AgentInstanceCreateJob(agentType, q);
                        q->connect(job, &Akonadi::AgentInstanceCreateJob::result, q, [this](KJob *job) {
                            slotResourceCreationDone(job);
                        });
                        job->configure(mParentWidget);
                        job->start();
                        delete dlg;
                        return;
                    } else { //if agent is not valid => return error and finish job
                        q->setError(UserDefinedError);
                        q->emitResult();
                        delete dlg;
                        return;
                    }
                } else { //Canceled create agent => return error and finish job
                    q->setError(UserDefinedError);
                    q->emitResult();
                    delete dlg;
                    return;
                }
            } else {
                q->setError(UserDefinedError);
                q->emitResult();
                return;
            }
        } else if (nbItemCollection == 1) {
            addressBook = canCreateItemCollections[0];
        } else {
            // ask user in which address book the new contact shall be stored
            QPointer<Akonadi::SelectAddressBookDialog> dlg = new Akonadi::SelectAddressBookDialog(mParentWidget);

            bool gotIt = true;
            if (dlg->exec()) {
                addressBook = dlg->selectedCollection();
            } else {
                q->setError(UserDefinedError);
                q->emitResult();
                gotIt = false;
            }
            delete dlg;
            if (!gotIt) {
                return;
            }
        }

        if (!addressBook.isValid()) {
            q->setError(UserDefinedError);
            q->emitResult();
            return;
        }
        KContacts::Addressee contact;
        contact.setNameFromString(mName);
        contact.insertEmail(mEmail, true);
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailPreferedFormatting"), mShowAsHTML ? QStringLiteral("HTML") : QStringLiteral("TEXT"));
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("MailAllowToRemoteContent"), mRemoteContent ? QStringLiteral("TRUE") : QStringLiteral("FALSE"));

        // create the new item
        Akonadi::Item item;
        item.setMimeType(KContacts::Addressee::mimeType());
        item.setPayload<KContacts::Addressee>(contact);

        // save the new item in akonadi storage
        auto *createJob = new Akonadi::ItemCreateJob(item, addressBook, q);
        q->connect(createJob, &Akonadi::ItemCreateJob::result, q, [this](KJob *createJob) {
            auto *modifiedJob = static_cast<Akonadi::ItemCreateJob *>(createJob);
            if (!modifiedJob->error()) {
                Q_EMIT q->contactUpdated(modifiedJob->item(), messageId, mShowAsHTML, mRemoteContent);
            }
            slotAddModifyContactDone(createJob);
        });
    }

    void slotAddModifyContactDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
        }
        q->emitResult();
    }

    AddEmailDisplayJob *const q;
    Akonadi::Item contact;
    Akonadi::Item::Id messageId;
    QString mCompleteAddress;
    QString mEmail;
    QString mName;
    QWidget *const mParentWidget;
    bool mShowAsHTML = false;
    bool mRemoteContent = false;
};

AddEmailDisplayJob::AddEmailDisplayJob(const QString &email, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , d(new Private(this, email, parentWidget))
{
}

AddEmailDisplayJob::~AddEmailDisplayJob()
{
    delete d;
}

void AddEmailDisplayJob::setShowAsHTML(bool html)
{
    d->mShowAsHTML = html;
}

void AddEmailDisplayJob::setRemoteContent(bool b)
{
    d->mRemoteContent = b;
}

void AddEmailDisplayJob::setContact(const Akonadi::Item &contact)
{
    d->contact = contact;
}

void AddEmailDisplayJob::setMessageId(Akonadi::Item::Id id)
{
    d->messageId = id;
}

void AddEmailDisplayJob::start()
{
    if (d->contact.isValid()) {
        d->modifyContact();
    } else {
        d->searchContact();
    }
}

#include "moc_addemaildisplayjob.cpp"
