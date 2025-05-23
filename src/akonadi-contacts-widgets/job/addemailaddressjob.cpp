/*
  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>
  SPDX-FileCopyrightText: 2010 Nicolas Lécureuil <nicolas.lecureuil@free.fr>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addemailaddressjob.h"
#include "widgets/selectaddressbookdialog.h"
#include <Akonadi/AgentConfigurationDialog>
#include <Akonadi/AgentFilterProxyModel>
#include <Akonadi/AgentInstance>
#include <Akonadi/AgentInstanceCreateJob>
#include <Akonadi/AgentManager>
#include <Akonadi/AgentType>
#include <Akonadi/AgentTypeDialog>
#include <Akonadi/Collection>
#include <Akonadi/CollectionDialog>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ContactEditorDialog>
#include <Akonadi/ContactSearchJob>
#include <Akonadi/ItemCreateJob>
#include <KContacts/ContactGroup>

#include <KLocalizedString>
#include <KMessageBox>

#include <QPointer>

using namespace Akonadi;

class Akonadi::AddEmailAddressJobPrivate
{
public:
    AddEmailAddressJobPrivate(AddEmailAddressJob *qq, const QString &emailString, QWidget *parentWidget)
        : q(qq)
        , mCompleteAddress(emailString)
        , mParentWidget(parentWidget)
        , mInteractive(true)
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
        if (!contacts.isEmpty()) {
            if (mInteractive) {
                const QString text = xi18nc("@info",
                                            "A contact with the email address <email>%1</email> "
                                            "is already in your address book.",
                                            mCompleteAddress);

                KMessageBox::information(mParentWidget, text, QString(), QStringLiteral("alreadyInAddressBook"));
            }
            q->setError(KJob::UserDefinedError);
            q->emitResult();
            return;
        }
        createContact();
    }

    void createContact()
    {
        const QStringList mimeTypes(KContacts::Addressee::mimeType());

        auto const addressBookJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive);

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

        const Akonadi::CollectionFetchJob *addressBookJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);

        Akonadi::Collection::List canCreateItemCollections;

        const Akonadi::Collection::List lstColls = addressBookJob->collections();
        for (const Akonadi::Collection &collection : lstColls) {
            if (Akonadi::Collection::CanCreateItem & collection.rights()) {
                canCreateItemCollections.append(collection);
            }
        }

        Akonadi::Collection addressBook;

        const int nbItemCollection(canCreateItemCollections.size());
        if (nbItemCollection == 0) {
            if (KMessageBox::questionTwoActions(
                    mParentWidget,
                    i18nc("@info", "You must create an address book before adding a contact. Do you want to create an address book?"),
                    i18nc("@title:window", "No Address Book Available"),
                    KGuiItem(i18nc("@action:button", "Create Address Book"), QStringLiteral("address-book-new")),
                    KStandardGuiItem::cancel())
                == KMessageBox::ButtonCode::PrimaryAction) {
                QPointer<Akonadi::AgentTypeDialog> dlg = new Akonadi::AgentTypeDialog(mParentWidget);
                dlg->setWindowTitle(i18nc("@title:window", "Add Address Book"));
                dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::Addressee::mimeType());
                dlg->agentFilterProxyModel()->addMimeTypeFilter(KContacts::ContactGroup::mimeType());
                dlg->agentFilterProxyModel()->addCapabilityFilter(QStringLiteral("Resource"));

                if (dlg->exec()) {
                    const Akonadi::AgentType agentType = dlg->agentType();

                    if (agentType.isValid()) {
                        auto job = new Akonadi::AgentInstanceCreateJob(agentType, q);
                        q->connect(job, &Akonadi::AgentInstanceCreateJob::result, q, [this, job](KJob *) {
                            if (job->error()) {
                                slotResourceCreationDone(job);
                                return;
                            }
                            auto configureDialog = new Akonadi::AgentConfigurationDialog(job->instance(), mParentWidget);
                            configureDialog->setAttribute(Qt::WA_DeleteOnClose);
                            q->connect(configureDialog, &QDialog::rejected, q, [this, instance = job->instance()] {
                                Akonadi::AgentManager::self()->removeInstance(instance);
                                q->emitResult();
                            });
                            q->connect(configureDialog, &QDialog::accepted, q, [this] {
                                createContact();
                            });
                            configureDialog->show();
                        });
                        job->start();
                        delete dlg;
                        return;
                    } else { // if agent is not valid => return error and finish job
                        q->setError(KJob::UserDefinedError);
                        q->emitResult();
                        delete dlg;
                        return;
                    }
                } else { // Canceled create agent => return error and finish job
                    q->setError(KJob::UserDefinedError);
                    q->emitResult();
                    delete dlg;
                    return;
                }
            } else {
                q->setError(KJob::UserDefinedError);
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
                q->setError(KJob::UserDefinedError);
                q->emitResult();
                gotIt = false;
            }
            delete dlg;
            if (!gotIt) {
                return;
            }
        }

        if (!addressBook.isValid()) {
            q->setError(KJob::UserDefinedError);
            q->emitResult();
            return;
        }
        KContacts::Addressee contact;
        contact.setNameFromString(mName);
        KContacts::Email email(mEmail);
        email.setPreferred(true);
        contact.addEmail(email);
        // create the new item
        Akonadi::Item item;
        item.setMimeType(KContacts::Addressee::mimeType());
        item.setPayload<KContacts::Addressee>(contact);

        // save the new item in akonadi storage
        auto createJob = new Akonadi::ItemCreateJob(item, addressBook, q);
        q->connect(createJob, &Akonadi::ItemCreateJob::result, q, [this](KJob *job) {
            slotAddContactDone(job);
        });
    }

    void slotAddContactDone(KJob *job)
    {
        if (job->error()) {
            q->setError(job->error());
            q->setErrorText(job->errorText());
            q->emitResult();
            return;
        }

        const Akonadi::ItemCreateJob *createJob = qobject_cast<Akonadi::ItemCreateJob *>(job);
        mItem = createJob->item();

        if (mInteractive) {
            const QString text = xi18nc("@info",
                                        "<para>A contact for \"%1\" was successfully added "
                                        "to your address book.</para>"
                                        "<para>Do you want to edit this new contact now?</para>",
                                        mCompleteAddress);

            if (KMessageBox::questionTwoActions(mParentWidget,
                                                text,
                                                QString(),
                                                KGuiItem(i18nc("@action:button", "Edit"), QStringLiteral("document-edit")),
                                                KGuiItem(i18nc("@action:button", "Finish"), QStringLiteral("dialog-ok-apply")),
                                                QStringLiteral("addedtokabc"))
                == KMessageBox::ButtonCode::PrimaryAction) {
                QPointer<Akonadi::ContactEditorDialog> dlg = new Akonadi::ContactEditorDialog(Akonadi::ContactEditorDialog::EditMode, mParentWidget);
                dlg->setContact(mItem);
                QObject::connect(dlg.data(), &Akonadi::ContactEditorDialog::contactStored, q, [this](const Akonadi::Item &item) {
                    contactStored(item);
                });
                QObject::connect(dlg.data(), &Akonadi::ContactEditorDialog::error, q, [this](const QString &str) {
                    slotContactEditorError(str);
                });
                dlg->exec();
                delete dlg;
            }
        }
        q->emitResult();
    }

    void slotContactEditorError(const QString &error)
    {
        if (mInteractive) {
            KMessageBox::error(mParentWidget, i18n("Contact cannot be stored: %1", error), i18nc("@title:window", "Failed to store contact"));
        }
    }

    void contactStored(const Akonadi::Item &)
    {
        if (mInteractive) {
            Q_EMIT q->successMessage(i18n("Contact created successfully"));
        }
    }

    AddEmailAddressJob *const q;
    const QString mCompleteAddress;
    QString mEmail;
    QString mName;
    QWidget *const mParentWidget;
    Akonadi::Item mItem;
    bool mInteractive = false;
};

AddEmailAddressJob::AddEmailAddressJob(const QString &email, QWidget *parentWidget, QObject *parent)
    : KJob(parent)
    , d(new AddEmailAddressJobPrivate(this, email, parentWidget))
{
}

AddEmailAddressJob::~AddEmailAddressJob() = default;

void AddEmailAddressJob::start()
{
    // first check whether a contact with the same email exists already
    auto searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setLimit(1);
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, d->mEmail.toLower(), Akonadi::ContactSearchJob::ExactMatch);
    connect(searchJob, &Akonadi::ContactSearchJob::result, this, [this](KJob *job) {
        d->slotSearchDone(job);
    });
}

Akonadi::Item AddEmailAddressJob::contact() const
{
    return d->mItem;
}

void AddEmailAddressJob::setInteractive(bool b)
{
    d->mInteractive = b;
}

#include "moc_addemailaddressjob.cpp"
