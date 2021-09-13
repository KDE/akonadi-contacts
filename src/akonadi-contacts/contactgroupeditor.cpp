/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupeditor.h"
#include "contactgroupeditor_p.h"

#include "contactgroupeditordelegate_p.h"
#include "contactgroupmodel_p.h"
#include "waitingoverlay_p.h"

#include <Akonadi/CollectionDialog>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <Akonadi/Monitor>
#include <Akonadi/Session>
#include <KColorScheme>
#include <KLocalizedString>
#include <KMessageBox>
#include <kcontacts/contactgroup.h>

#include <QMessageBox>
#include <QTimer>

using namespace Akonadi;

ContactGroupEditor::Private::Private(ContactGroupEditor *parent)
    : mParent(parent)
{
}

ContactGroupEditor::Private::~Private()
{
    delete mMonitor;
}

void ContactGroupEditor::Private::adaptHeaderSizes()
{
    mGui.membersView->header()->setDefaultSectionSize(mGui.membersView->header()->width() / 2);
    mGui.membersView->header()->resizeSections(QHeaderView::Interactive);
}

void ContactGroupEditor::Private::itemFetchDone(KJob *job)
{
    if (job->error()) {
        return;
    }

    auto fetchJob = qobject_cast<ItemFetchJob *>(job);
    if (!fetchJob) {
        return;
    }

    if (fetchJob->items().isEmpty()) {
        return;
    }

    mItem = fetchJob->items().at(0);

    mReadOnly = false;
    if (mMode == ContactGroupEditor::EditMode) {
        // if in edit mode we have to fetch the parent collection to find out
        // about the modify rights of the item

        auto collectionFetchJob = new Akonadi::CollectionFetchJob(mItem.parentCollection(), Akonadi::CollectionFetchJob::Base);
        mParent->connect(collectionFetchJob, &CollectionFetchJob::result, mParent, [this](KJob *job) {
            parentCollectionFetchDone(job);
        });
    } else {
        const auto group = mItem.payload<KContacts::ContactGroup>();
        loadContactGroup(group);

        setReadOnly(mReadOnly);

        QTimer::singleShot(0, mParent, [this]() {
            adaptHeaderSizes();
        });
    }
}

void ContactGroupEditor::Private::parentCollectionFetchDone(KJob *job)
{
    if (job->error()) {
        return;
    }

    auto fetchJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
    if (!fetchJob) {
        return;
    }

    const Akonadi::Collection parentCollection = fetchJob->collections().at(0);
    if (parentCollection.isValid()) {
        mReadOnly = !(parentCollection.rights() & Collection::CanChangeItem);
    }

    const auto group = mItem.payload<KContacts::ContactGroup>();
    loadContactGroup(group);

    setReadOnly(mReadOnly);

    QTimer::singleShot(0, mParent, [this]() {
        adaptHeaderSizes();
    });
}

void ContactGroupEditor::Private::storeDone(KJob *job)
{
    if (job->error()) {
        Q_EMIT mParent->error(job->errorString());
        return;
    }

    if (mMode == EditMode) {
        Q_EMIT mParent->contactGroupStored(mItem);
    } else if (mMode == CreateMode) {
        Q_EMIT mParent->contactGroupStored(static_cast<ItemCreateJob *>(job)->item());
    }
}

void ContactGroupEditor::Private::itemChanged(const Item &item, const QSet<QByteArray> &)
{
    Q_UNUSED(item)
    QPointer<QMessageBox> dlg = new QMessageBox(mParent); // krazy:exclude=qclasses

    dlg->setInformativeText(i18n("The contact group has been changed by someone else.\nWhat should be done?"));
    dlg->addButton(i18n("Take over changes"), QMessageBox::AcceptRole);
    dlg->addButton(i18n("Ignore and Overwrite changes"), QMessageBox::RejectRole);

    if (dlg->exec() == QMessageBox::AcceptRole) {
        auto job = new ItemFetchJob(mItem);
        job->fetchScope().fetchFullPayload();
        job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);

        mParent->connect(job, &ItemFetchJob::result, mParent, [this](KJob *job) {
            itemFetchDone(job);
        });
        new WaitingOverlay(job, mParent);
    }
    delete dlg;
}

void ContactGroupEditor::Private::loadContactGroup(const KContacts::ContactGroup &group)
{
    mGui.membersView->setSortingEnabled(false);
    mGui.groupName->setText(group.name());

    mGroupModel->loadContactGroup(group);

    const QAbstractItemModel *model = mGui.membersView->model();
    mGui.membersView->setCurrentIndex(model->index(model->rowCount() - 1, 0));

    if (mMode == EditMode) {
        mGui.membersView->setFocus();
    }

    mGui.membersView->header()->resizeSections(QHeaderView::Stretch);
    mGui.membersView->setSortingEnabled(true);
}

bool ContactGroupEditor::Private::storeContactGroup(KContacts::ContactGroup &group)
{
    if (mGui.groupName->text().isEmpty()) {
        KMessageBox::error(mParent, i18n("The name of the contact group must not be empty."));
        return false;
    }

    group.setName(mGui.groupName->text());

    if (!mGroupModel->storeContactGroup(group)) {
        KMessageBox::error(mParent, mGroupModel->lastErrorMessage());
        return false;
    }

    return true;
}

void ContactGroupEditor::Private::setupMonitor()
{
    delete mMonitor;
    mMonitor = new Monitor;
    mMonitor->setObjectName(QStringLiteral("ContactGroupEditorMonitor"));
    mMonitor->ignoreSession(Session::defaultSession());

    connect(mMonitor, &Monitor::itemChanged, mParent, [this](const Akonadi::Item &item, const QSet<QByteArray> &arrays) {
        itemChanged(item, arrays);
    });
}

void ContactGroupEditor::Private::setReadOnly(bool readOnly)
{
    mGui.groupName->setReadOnly(readOnly);
    mGui.membersView->setEnabled(!readOnly);
}

ContactGroupEditor::ContactGroupEditor(Mode mode, QWidget *parent)
    : QWidget(parent)
    , d(new Private(this))
{
    d->mMode = mode;
    d->mGui.setupUi(this);

    d->mGui.membersView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    d->mGroupModel = new ContactGroupModel(this);
    auto proxyModel = new GroupFilterModel(this);
    proxyModel->setSourceModel(d->mGroupModel);
    connect(d->mGui.searchField, &QLineEdit::textChanged, this, [proxyModel](const QString &text) {
        proxyModel->setFilterRegularExpression(text);
    });
    d->mGui.membersView->setModel(proxyModel);
    d->mGui.membersView->setItemDelegate(new ContactGroupEditorDelegate(d->mGui.membersView, this));

    if (mode == CreateMode) {
        KContacts::ContactGroup dummyGroup;
        d->mGroupModel->loadContactGroup(dummyGroup);

        QTimer::singleShot(0, this, [this]() {
            d->adaptHeaderSizes();
        });
        QTimer::singleShot(0, d->mGui.groupName, qOverload<>(&ContactGroupEditor::setFocus));
    }

    d->mGui.membersView->header()->setStretchLastSection(true);
}

ContactGroupEditor::~ContactGroupEditor()
{
    delete d;
}

void ContactGroupEditor::loadContactGroup(const Akonadi::Item &item)
{
    if (d->mMode == CreateMode) {
        Q_ASSERT_X(false, "ContactGroupEditor::loadContactGroup", "You are calling loadContactGroup in CreateMode!");
    }

    auto job = new ItemFetchJob(item);
    job->fetchScope().fetchFullPayload();
    job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);

    connect(job, &ItemModifyJob::result, this, [this](KJob *job) {
        d->itemFetchDone(job);
    });

    d->setupMonitor();
    d->mMonitor->setItemMonitored(item);

    new WaitingOverlay(job, this);
}

bool ContactGroupEditor::saveContactGroup()
{
    if (d->mMode == EditMode) {
        if (!d->mItem.isValid()) {
            return false;
        }

        if (d->mReadOnly) {
            return true;
        }

        auto group = d->mItem.payload<KContacts::ContactGroup>();

        if (!d->storeContactGroup(group)) {
            return false;
        }

        d->mItem.setPayload<KContacts::ContactGroup>(group);

        auto job = new ItemModifyJob(d->mItem);
        connect(job, &ItemModifyJob::result, this, [this](KJob *job) {
            d->storeDone(job);
        });
    } else if (d->mMode == CreateMode) {
        if (!d->mDefaultCollection.isValid()) {
            const QStringList mimeTypeFilter(KContacts::ContactGroup::mimeType());

            QPointer<CollectionDialog> dlg = new CollectionDialog(this);
            dlg->setMimeTypeFilter(mimeTypeFilter);
            dlg->setAccessRightsFilter(Collection::CanCreateItem);
            dlg->setWindowTitle(i18nc("@title:window", "Select Address Book"));
            dlg->setDescription(i18n("Select the address book the new contact group shall be saved in:"));

            if (dlg->exec() == QDialog::Accepted) {
                setDefaultAddressBook(dlg->selectedCollection());
                delete dlg;
            } else {
                delete dlg;
                return false;
            }
        }

        KContacts::ContactGroup group;
        if (!d->storeContactGroup(group)) {
            return false;
        }

        Item item;
        item.setPayload<KContacts::ContactGroup>(group);
        item.setMimeType(KContacts::ContactGroup::mimeType());

        auto job = new ItemCreateJob(item, d->mDefaultCollection);
        connect(job, &ItemCreateJob::result, this, [this](KJob *job) {
            d->storeDone(job);
        });
    }

    return true;
}

void ContactGroupEditor::setContactGroupTemplate(const KContacts::ContactGroup &group)
{
    d->mGroupModel->loadContactGroup(group);
    d->mGui.membersView->header()->setDefaultSectionSize(d->mGui.membersView->header()->width() / 2);
    d->mGui.membersView->header()->resizeSections(QHeaderView::Interactive);
}

void ContactGroupEditor::setDefaultAddressBook(const Akonadi::Collection &collection)
{
    d->mDefaultCollection = collection;
}

void ContactGroupEditor::groupNameIsValid(bool isValid)
{
#ifndef QT_NO_STYLE_STYLESHEET
    QString styleSheet;
    if (!isValid) {
        const KColorScheme::BackgroundRole bgColorScheme(KColorScheme::NegativeBackground);
        KStatefulBrush bgBrush(KColorScheme::View, bgColorScheme);
        styleSheet = QStringLiteral("QLineEdit{ background-color:%1 }").arg(bgBrush.brush(palette()).color().name());
    }
    d->mGui.groupName->setStyleSheet(styleSheet);
#endif
}

#include "moc_contactgroupeditor.cpp"
