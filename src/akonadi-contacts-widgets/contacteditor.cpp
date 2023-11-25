/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contacteditor.h"

#include "abstractcontacteditorwidget_p.h"
#include "attributes/contactmetadataattribute_p.h"
#include "contactmetadataakonadi_p.h"
#include "editor/contacteditorwidget.h"

#include <Akonadi/CollectionDialog>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <Akonadi/Monitor>
#include <Akonadi/Session>
#include <KContacts/Addressee>
#include <KLocalizedString>

#include <QMessageBox>
#include <QPointer>
#include <QVBoxLayout>

using namespace Akonadi;

class Akonadi::AkonadiContactEditorPrivate
{
public:
    AkonadiContactEditorPrivate(AkonadiContactEditor::Mode mode,
                                AkonadiContactEditor::DisplayMode displayMode,
                                Akonadi::AbstractContactEditorWidget *editorWidget,
                                AkonadiContactEditor *parent)
        : mParent(parent)
        , mMode(mode)
    {
        if (editorWidget) {
            mEditorWidget = editorWidget;
        } else {
            mEditorWidget =
                new ContactEditorWidget(displayMode == AkonadiContactEditor::FullMode ? ContactEditorWidget::FullMode : ContactEditorWidget::VCardMode,
                                        mParent);
        }

        auto layout = new QVBoxLayout(mParent);
        layout->setContentsMargins({});
        layout->setSpacing(0);
        layout->addWidget(mEditorWidget);
    }

    ~AkonadiContactEditorPrivate()
    {
        delete mMonitor;
    }

    void itemFetchDone(KJob *job);
    void parentCollectionFetchDone(KJob *job);
    void storeDone(KJob *job);
    void itemChanged(const Akonadi::Item &item, const QSet<QByteArray> &);

    void loadContact(const KContacts::Addressee &addr, const Akonadi::ContactMetaDataAkonadi &metaData);
    void storeContact(KContacts::Addressee &addr, Akonadi::ContactMetaDataAkonadi &metaData);
    void setupMonitor();

    AkonadiContactEditor *const mParent;
    const AkonadiContactEditor::Mode mMode;
    Akonadi::Item mItem;
    Akonadi::ContactMetaDataAkonadi mContactMetaData;
    Akonadi::Monitor *mMonitor = nullptr;
    Akonadi::Collection mDefaultCollection;
    Akonadi::AbstractContactEditorWidget *mEditorWidget = nullptr;
    bool mReadOnly = false;
};

void Akonadi::AkonadiContactEditorPrivate::itemFetchDone(KJob *job)
{
    if (job->error() != KJob::NoError) {
        Q_EMIT mParent->error(job->errorString());
        Q_EMIT mParent->finished();
        return;
    }

    auto fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    if (!fetchJob) {
        return;
    }

    if (fetchJob->items().isEmpty()) {
        return;
    }

    mItem = fetchJob->items().at(0);

    mReadOnly = false;
    if (mMode == AkonadiContactEditor::EditMode) {
        // if in edit mode we have to fetch the parent collection to find out
        // about the modify rights of the item

        auto collectionFetchJob = new Akonadi::CollectionFetchJob(mItem.parentCollection(), Akonadi::CollectionFetchJob::Base);
        mParent->connect(collectionFetchJob, &Akonadi::CollectionFetchJob::result, mParent, [this](KJob *job) {
            parentCollectionFetchDone(job);
        });
    } else {
        const auto addr = mItem.payload<KContacts::Addressee>();
        mContactMetaData.load(mItem);
        loadContact(addr, mContactMetaData);
        mEditorWidget->setReadOnly(mReadOnly);
    }
}

void Akonadi::AkonadiContactEditorPrivate::parentCollectionFetchDone(KJob *job)
{
    if (job->error()) {
        Q_EMIT mParent->error(job->errorString());
        Q_EMIT mParent->finished();
        return;
    }

    auto fetchJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
    if (!fetchJob) {
        return;
    }

    const Akonadi::Collection parentCollection = fetchJob->collections().at(0);
    if (parentCollection.isValid()) {
        mReadOnly = !(parentCollection.rights() & Akonadi::Collection::CanChangeItem);
    }

    const auto addr = mItem.payload<KContacts::Addressee>();
    mContactMetaData.load(mItem);
    loadContact(addr, mContactMetaData);
    mEditorWidget->setReadOnly(mReadOnly);
}

void Akonadi::AkonadiContactEditorPrivate::storeDone(KJob *job)
{
    if (job->error() != KJob::NoError) {
        Q_EMIT mParent->error(job->errorString());
        Q_EMIT mParent->finished();
        return;
    }

    if (mMode == AkonadiContactEditor::EditMode) {
        Q_EMIT mParent->contactStored(mItem);
    } else if (mMode == AkonadiContactEditor::CreateMode) {
        Q_EMIT mParent->contactStored(static_cast<Akonadi::ItemCreateJob *>(job)->item());
    }
    Q_EMIT mParent->finished();
}

void Akonadi::AkonadiContactEditorPrivate::itemChanged(const Akonadi::Item &item, const QSet<QByteArray> &)
{
    Q_UNUSED(item)
    QPointer<QMessageBox> dlg = new QMessageBox(mParent); // krazy:exclude=qclasses

    dlg->setInformativeText(i18n("The contact has been changed by someone else.\nWhat should be done?"));
    dlg->addButton(i18n("Take over changes"), QMessageBox::AcceptRole);
    dlg->addButton(i18n("Ignore and Overwrite changes"), QMessageBox::RejectRole);

    if (dlg->exec() == QMessageBox::AcceptRole) {
        auto job = new Akonadi::ItemFetchJob(mItem);
        job->fetchScope().fetchFullPayload();
        job->fetchScope().fetchAttribute<Akonadi::ContactMetaDataAttribute>();
        job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);

        mParent->connect(job, &Akonadi::ItemFetchJob::result, mParent, [this](KJob *job) {
            itemFetchDone(job);
        });
    } else {
        // Still update the item so that the internal revision match
        mItem = item;
    }

    delete dlg;
}

void Akonadi::AkonadiContactEditorPrivate::loadContact(const KContacts::Addressee &addr, const ContactMetaDataAkonadi &metaData)
{
    mEditorWidget->loadContact(addr, metaData);
}

void Akonadi::AkonadiContactEditorPrivate::storeContact(KContacts::Addressee &addr, ContactMetaDataAkonadi &metaData)
{
    mEditorWidget->storeContact(addr, metaData);
}

void Akonadi::AkonadiContactEditorPrivate::setupMonitor()
{
    delete mMonitor;
    mMonitor = new Akonadi::Monitor;
    mMonitor->setObjectName(QLatin1StringView("ContactEditorMonitor"));
    mMonitor->ignoreSession(Akonadi::Session::defaultSession());

    QObject::connect(mMonitor, &Akonadi::Monitor::itemChanged, mParent, [this](const Akonadi::Item &item, const QSet<QByteArray> &set) {
        itemChanged(item, set);
    });
}

Akonadi::AkonadiContactEditor::AkonadiContactEditor(Mode mode, QWidget *parent)
    : QWidget(parent)
    , d(new AkonadiContactEditorPrivate(mode, FullMode, nullptr, this))
{
}

Akonadi::AkonadiContactEditor::AkonadiContactEditor(Mode mode, Akonadi::AbstractContactEditorWidget *editorWidget, QWidget *parent)
    : QWidget(parent)
    , d(new AkonadiContactEditorPrivate(mode, FullMode, editorWidget, this))
{
}

Akonadi::AkonadiContactEditor::AkonadiContactEditor(Mode mode, DisplayMode displayMode, QWidget *parent)
    : QWidget(parent)
    , d(new AkonadiContactEditorPrivate(mode, displayMode, nullptr, this))
{
}

Akonadi::AkonadiContactEditor::~AkonadiContactEditor() = default;

void Akonadi::AkonadiContactEditor::loadContact(const Akonadi::Item &item)
{
    if (d->mMode == CreateMode) {
        Q_ASSERT_X(false, "Akonadi::loadContact", "You are calling loadContact in CreateMode!");
    }

    auto job = new Akonadi::ItemFetchJob(item);
    job->fetchScope().fetchFullPayload();
    job->fetchScope().fetchAttribute<Akonadi::ContactMetaDataAttribute>();
    job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);

    connect(job, &Akonadi::ItemFetchJob::result, this, [this](KJob *job) {
        d->itemFetchDone(job);
    });

    d->setupMonitor();
    d->mMonitor->setItemMonitored(item);
}

KContacts::Addressee Akonadi::AkonadiContactEditor::contact()
{
    KContacts::Addressee addr;
    d->storeContact(addr, d->mContactMetaData);
    return addr;
}

void Akonadi::AkonadiContactEditor::saveContactInAddressBook()
{
    if (d->mMode == EditMode) {
        if (!d->mItem.isValid() || d->mReadOnly) {
            Q_EMIT finished();
            return;
        }

        auto addr = d->mItem.payload<KContacts::Addressee>();

        d->storeContact(addr, d->mContactMetaData);

        d->mContactMetaData.store(d->mItem);

        d->mItem.setPayload<KContacts::Addressee>(addr);

        auto job = new Akonadi::ItemModifyJob(d->mItem);
        connect(job, &Akonadi::ItemModifyJob::result, this, [this](KJob *job) {
            d->storeDone(job);
        });
    } else if (d->mMode == CreateMode) {
        if (!d->mDefaultCollection.isValid()) {
            const QStringList mimeTypeFilter(KContacts::Addressee::mimeType());

            QPointer<Akonadi::CollectionDialog> dlg = new Akonadi::CollectionDialog(this);
            dlg->setMimeTypeFilter(mimeTypeFilter);
            dlg->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
            dlg->setWindowTitle(i18nc("@title:window", "Select Address Book"));
            dlg->setDescription(i18n("Select the address book the new contact shall be saved in:"));
            if (dlg->exec() == QDialog::Accepted) {
                setDefaultAddressBook(dlg->selectedCollection());
                delete dlg;
            } else {
                delete dlg;
                return;
            }
        }

        KContacts::Addressee addr;
        d->storeContact(addr, d->mContactMetaData);

        Akonadi::Item item;
        item.setPayload<KContacts::Addressee>(addr);
        item.setMimeType(KContacts::Addressee::mimeType());

        d->mContactMetaData.store(item);

        auto job = new Akonadi::ItemCreateJob(item, d->mDefaultCollection);
        connect(job, &Akonadi::ItemCreateJob::result, this, [this](KJob *job) {
            d->storeDone(job);
        });
    }
}

void Akonadi::AkonadiContactEditor::setContactTemplate(const KContacts::Addressee &contact)
{
    d->loadContact(contact, d->mContactMetaData);
}

void Akonadi::AkonadiContactEditor::setDefaultAddressBook(const Akonadi::Collection &collection)
{
    d->mDefaultCollection = collection;
}

bool Akonadi::AkonadiContactEditor::hasNoSavedData() const
{
    return d->mEditorWidget->hasNoSavedData();
}

#include "moc_contacteditor.cpp"
