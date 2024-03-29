/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 - 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardcontactactionmanager.h"

#include "contacteditordialog.h"
#include "contactgroupeditordialog.h"

#include <Akonadi/EntityTreeModel>
#include <Akonadi/MimeTypeChecker>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <QAction>

#include <QItemSelectionModel>
#include <QPointer>

using namespace Akonadi;
using namespace Akonadi;
class Akonadi::StandardContactActionManagerPrivate
{
public:
    StandardContactActionManagerPrivate(KActionCollection *actionCollection, QWidget *parentWidget, StandardContactActionManager *parent)
        : mActionCollection(actionCollection)
        , mParentWidget(parentWidget)
        , mParent(parent)
    {
        mGenericManager = new StandardActionManager(actionCollection, parentWidget);
        mParent->connect(mGenericManager, &StandardActionManager::actionStateUpdated, mParent, &StandardContactActionManager::actionStateUpdated);

        mGenericManager->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType() << KContacts::ContactGroup::mimeType());

        mGenericManager->setCapabilityFilter(QStringList() << QStringLiteral("Resource"));
    }

    ~StandardContactActionManagerPrivate()
    {
        delete mGenericManager;
    }

    void updateGenericAllActions()
    {
        updateGenericAction(StandardActionManager::CreateCollection);
        updateGenericAction(StandardActionManager::CopyCollections);
        updateGenericAction(StandardActionManager::DeleteCollections);
        updateGenericAction(StandardActionManager::SynchronizeCollections);
        updateGenericAction(StandardActionManager::CollectionProperties);
        updateGenericAction(StandardActionManager::CopyItems);
        updateGenericAction(StandardActionManager::Paste);
        updateGenericAction(StandardActionManager::DeleteItems);
        updateGenericAction(StandardActionManager::ManageLocalSubscriptions);
        updateGenericAction(StandardActionManager::AddToFavoriteCollections);
        updateGenericAction(StandardActionManager::RemoveFromFavoriteCollections);
        updateGenericAction(StandardActionManager::RenameFavoriteCollection);
        updateGenericAction(StandardActionManager::CopyCollectionToMenu);
        updateGenericAction(StandardActionManager::CopyItemToMenu);
        updateGenericAction(StandardActionManager::MoveItemToMenu);
        updateGenericAction(StandardActionManager::MoveCollectionToMenu);
        updateGenericAction(StandardActionManager::CutItems);
        updateGenericAction(StandardActionManager::CutCollections);
        updateGenericAction(StandardActionManager::CreateResource);
        updateGenericAction(StandardActionManager::DeleteResources);
        updateGenericAction(StandardActionManager::ResourceProperties);
        updateGenericAction(StandardActionManager::SynchronizeResources);
        updateGenericAction(StandardActionManager::ToggleWorkOffline);
        updateGenericAction(StandardActionManager::CopyCollectionToDialog);
        updateGenericAction(StandardActionManager::MoveCollectionToDialog);
        updateGenericAction(StandardActionManager::CopyItemToDialog);
        updateGenericAction(StandardActionManager::MoveItemToDialog);
        updateGenericAction(StandardActionManager::SynchronizeCollectionsRecursive);
        updateGenericAction(StandardActionManager::MoveCollectionsToTrash);
        updateGenericAction(StandardActionManager::MoveItemsToTrash);
        updateGenericAction(StandardActionManager::RestoreCollectionsFromTrash);
        updateGenericAction(StandardActionManager::RestoreItemsFromTrash);
        updateGenericAction(StandardActionManager::MoveToTrashRestoreCollection);
        updateGenericAction(StandardActionManager::MoveToTrashRestoreCollectionAlternative);
        updateGenericAction(StandardActionManager::MoveToTrashRestoreItem);
        updateGenericAction(StandardActionManager::MoveToTrashRestoreItemAlternative);
        updateGenericAction(StandardActionManager::SynchronizeFavoriteCollections);
    }

    void updateGenericAction(StandardActionManager::Type type)
    {
        switch (type) {
        case Akonadi::StandardActionManager::CreateCollection:
            mGenericManager->action(Akonadi::StandardActionManager::CreateCollection)->setText(i18n("Add Address Book Folder..."));

            mGenericManager->action(Akonadi::StandardActionManager::CreateCollection)
                ->setWhatsThis(i18n("Add a new address book folder to the currently selected address book folder."));
            mGenericManager->setContextText(StandardActionManager::CreateCollection,
                                            StandardActionManager::DialogTitle,
                                            i18nc("@title:window", "New Address Book Folder"));

            mGenericManager->setContextText(StandardActionManager::CreateCollection,
                                            StandardActionManager::ErrorMessageText,
                                            ki18n("Could not create address book folder: %1"));

            mGenericManager->setContextText(StandardActionManager::CreateCollection,
                                            StandardActionManager::ErrorMessageTitle,
                                            i18n("Address book folder creation failed"));
            mGenericManager->action(Akonadi::StandardActionManager::CreateCollection)
                ->setProperty("ContentMimeTypes", QStringList() << QStringLiteral("application/x-vnd.kde.contactgroup") << QStringLiteral("text/directory"));

            break;
        case Akonadi::StandardActionManager::CopyCollections:
            mGenericManager->setActionText(Akonadi::StandardActionManager::CopyCollections, ki18np("Copy Address Book Folder", "Copy %1 Address Book Folders"));
            mGenericManager->action(Akonadi::StandardActionManager::CopyCollections)
                ->setWhatsThis(i18n("Copy the selected address book folders to the clipboard."));
            break;
        case Akonadi::StandardActionManager::DeleteCollections:
            mGenericManager->setActionText(Akonadi::StandardActionManager::DeleteCollections,
                                           ki18np("Delete Address Book Folder", "Delete %1 Address Book Folders"));
            mGenericManager->action(Akonadi::StandardActionManager::DeleteCollections)
                ->setWhatsThis(i18n("Delete the selected address book folders from the address book."));

            mGenericManager->setContextText(StandardActionManager::DeleteCollections,
                                            StandardActionManager::MessageBoxText,
                                            ki18np("Do you really want to delete this address book folder and all its sub-folders?",
                                                   "Do you really want to delete %1 address book folders and all their sub-folders?"));
            mGenericManager->setContextText(StandardActionManager::DeleteCollections,
                                            StandardActionManager::MessageBoxTitle,
                                            ki18ncp("@title:window", "Delete address book folder?", "Delete address book folders?"));

            mGenericManager->setContextText(StandardActionManager::DeleteCollections,
                                            StandardActionManager::ErrorMessageText,
                                            ki18n("Could not delete address book folder: %1"));

            mGenericManager->setContextText(StandardActionManager::DeleteCollections,
                                            StandardActionManager::ErrorMessageTitle,
                                            i18n("Address book folder deletion failed"));
            break;
        case Akonadi::StandardActionManager::SynchronizeCollections:
            mGenericManager->setActionText(Akonadi::StandardActionManager::SynchronizeCollections,
                                           ki18np("Update Address Book Folder", "Update %1 Address Book Folders"));
            mGenericManager->action(Akonadi::StandardActionManager::SynchronizeCollections)
                ->setWhatsThis(i18n("Update the content of the selected address book folders."));
            break;
        case Akonadi::StandardActionManager::CutCollections:
            mGenericManager->setActionText(Akonadi::StandardActionManager::CutCollections, ki18np("Cut Address Book Folder", "Cut %1 Address Book Folders"));
            mGenericManager->action(Akonadi::StandardActionManager::CutCollections)
                ->setWhatsThis(i18n("Cut the selected address book folders from the address book."));
            break;
        case Akonadi::StandardActionManager::CollectionProperties:
            mGenericManager->action(Akonadi::StandardActionManager::CollectionProperties)->setText(i18n("Folder Properties..."));
            mGenericManager->action(Akonadi::StandardActionManager::CollectionProperties)
                ->setWhatsThis(i18n("Open a dialog to edit the properties of the selected address book folder."));
            mGenericManager->setContextText(StandardActionManager::CollectionProperties,
                                            StandardActionManager::DialogTitle,
                                            ki18nc("@title:window", "Properties of Address Book Folder %1"));
            break;
        case Akonadi::StandardActionManager::CopyItems:
            mGenericManager->setActionText(Akonadi::StandardActionManager::CopyItems, ki18np("Copy Contact", "Copy %1 Contacts"));
            mGenericManager->action(Akonadi::StandardActionManager::CopyItems)->setWhatsThis(i18n("Copy the selected contacts to the clipboard."));
            break;
        case Akonadi::StandardActionManager::DeleteItems:
            mGenericManager->setActionText(Akonadi::StandardActionManager::DeleteItems, ki18np("Delete Contact", "Delete %1 Contacts"));
            mGenericManager->action(Akonadi::StandardActionManager::DeleteItems)->setWhatsThis(i18n("Delete the selected contacts from the address book."));
            mGenericManager->setContextText(StandardActionManager::DeleteItems,
                                            StandardActionManager::MessageBoxText,
                                            ki18np("Do you really want to delete the selected contact?", "Do you really want to delete %1 contacts?"));

            mGenericManager->setContextText(StandardActionManager::DeleteItems,
                                            StandardActionManager::MessageBoxTitle,
                                            ki18ncp("@title:window", "Delete Contact?", "Delete Contacts?"));

            mGenericManager->setContextText(StandardActionManager::DeleteItems, StandardActionManager::ErrorMessageText, ki18n("Could not delete contact: %1"));

            mGenericManager->setContextText(StandardActionManager::DeleteItems, StandardActionManager::ErrorMessageTitle, i18n("Contact deletion failed"));
            break;
        case Akonadi::StandardActionManager::CutItems:
            mGenericManager->setActionText(Akonadi::StandardActionManager::CutItems, ki18np("Cut Contact", "Cut %1 Contacts"));
            mGenericManager->action(Akonadi::StandardActionManager::CutItems)->setWhatsThis(i18n("Cut the selected contacts from the address book."));
            break;
        case Akonadi::StandardActionManager::CreateResource:
            mGenericManager->action(Akonadi::StandardActionManager::CreateResource)->setText(i18n("Add &Address Book..."));
            mGenericManager->action(Akonadi::StandardActionManager::CreateResource)
                ->setWhatsThis(i18n("Add a new address book<p>"
                                    "You will be presented with a dialog where you can select "
                                    "the type of the address book that shall be added.</p>"));
            mGenericManager->setContextText(StandardActionManager::CreateResource,
                                            StandardActionManager::DialogTitle,
                                            i18nc("@title:window", "Add Address Book"));

            mGenericManager->setContextText(StandardActionManager::CreateResource,
                                            StandardActionManager::ErrorMessageText,
                                            ki18n("Could not create address book: %1"));

            mGenericManager->setContextText(StandardActionManager::CreateResource,
                                            StandardActionManager::ErrorMessageTitle,
                                            i18n("Address book creation failed"));
            break;
        case Akonadi::StandardActionManager::DeleteResources:

            mGenericManager->setActionText(Akonadi::StandardActionManager::DeleteResources, ki18np("&Delete Address Book", "&Delete %1 Address Books"));
            mGenericManager->action(Akonadi::StandardActionManager::DeleteResources)
                ->setWhatsThis(i18n("Delete the selected address books<p>"
                                    "The currently selected address books will be deleted, "
                                    "along with all the contacts and contact groups they contain.</p>"));
            mGenericManager->setContextText(StandardActionManager::DeleteResources,
                                            StandardActionManager::MessageBoxText,
                                            ki18np("Do you really want to delete this address book?", "Do you really want to delete %1 address books?"));

            mGenericManager->setContextText(StandardActionManager::DeleteResources,
                                            StandardActionManager::MessageBoxTitle,
                                            ki18ncp("@title:window", "Delete Address Book?", "Delete Address Books?"));

            break;
        case Akonadi::StandardActionManager::ResourceProperties:

            mGenericManager->action(Akonadi::StandardActionManager::ResourceProperties)->setText(i18n("Address Book Properties..."));
            mGenericManager->action(Akonadi::StandardActionManager::ResourceProperties)
                ->setWhatsThis(i18n("Open a dialog to edit properties of the selected address book."));
            break;
        case Akonadi::StandardActionManager::SynchronizeResources:
            mGenericManager->setActionText(Akonadi::StandardActionManager::SynchronizeResources, ki18np("Update Address Book", "Update %1 Address Books"));

            mGenericManager->action(Akonadi::StandardActionManager::SynchronizeResources)
                ->setWhatsThis(i18n("Updates the content of all folders of the selected address books."));

            break;
        case StandardActionManager::Paste:
            mGenericManager->setContextText(StandardActionManager::Paste, StandardActionManager::ErrorMessageText, ki18n("Could not paste contact: %1"));

            mGenericManager->setContextText(StandardActionManager::Paste, StandardActionManager::ErrorMessageTitle, i18n("Paste failed"));
            break;
        default:
            break;
        }
    }

    static bool hasWritableCollection(const QModelIndex &index, const QString &mimeType)
    {
        const auto collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
        if (collection.isValid()) {
            if (collection.contentMimeTypes().contains(mimeType) && (collection.rights() & Akonadi::Collection::CanCreateItem)) {
                return true;
            }
        }

        const QAbstractItemModel *model = index.model();
        if (!model) {
            return false;
        }

        for (int row = 0; row < model->rowCount(index); ++row) {
            if (hasWritableCollection(model->index(row, 0, index), mimeType)) {
                return true;
            }
        }

        return false;
    }

    bool hasWritableCollection(const QString &mimeType) const
    {
        if (!mCollectionSelectionModel) {
            return false;
        }

        const QAbstractItemModel *collectionModel = mCollectionSelectionModel->model();
        for (int row = 0; row < collectionModel->rowCount(); ++row) {
            if (hasWritableCollection(collectionModel->index(row, 0, QModelIndex()), mimeType)) {
                return true;
            }
        }

        return false;
    }

    void updateActions()
    {
        int itemCount = 0;
        if (mItemSelectionModel) {
            itemCount = mItemSelectionModel->selectedRows().count();
            if (itemCount == 1) {
                const QModelIndex index = mItemSelectionModel->selectedRows().first();
                if (index.isValid()) {
                    const QString mimeType = index.data(EntityTreeModel::MimeTypeRole).toString();
                    if (mimeType == KContacts::Addressee::mimeType()) {
                        if (mGenericManager->action(Akonadi::StandardActionManager::CopyItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::CopyItems, ki18np("Copy Contact", "Copy %1 Contacts"));
                        }
                        QAction *act = mGenericManager->action(Akonadi::StandardActionManager::CopyItemToMenu);
                        if (act) {
                            act->setText(i18n("Copy Contact To"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::CopyItemToDialog);
                        if (act) {
                            act->setText(i18n("Copy Contact To"));
                        }
                        if (mGenericManager->action(Akonadi::StandardActionManager::DeleteItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::DeleteItems, ki18np("Delete Contact", "Delete %1 Contacts"));
                        }
                        if (mGenericManager->action(Akonadi::StandardActionManager::CutItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::CutItems, ki18np("Cut Contact", "Cut %1 Contacts"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::MoveItemToMenu);
                        if (act) {
                            act->setText(i18n("Move Contact To"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::MoveItemToDialog);
                        if (act) {
                            act->setText(i18n("Move Contact To"));
                        }
                        act = mActions.value(StandardContactActionManager::EditItem);
                        if (act) {
                            act->setText(i18n("Edit Contact..."));
                        }
                    } else if (mimeType == KContacts::ContactGroup::mimeType()) {
                        if (mGenericManager->action(Akonadi::StandardActionManager::CopyItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::CopyItems, ki18np("Copy Group", "Copy %1 Groups"));
                        }
                        QAction *act = mGenericManager->action(Akonadi::StandardActionManager::CopyItemToMenu);
                        if (act) {
                            act->setText(i18n("Copy Group To"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::CopyItemToDialog);
                        if (act) {
                            act->setText(i18n("Copy Group To"));
                        }
                        if (mGenericManager->action(Akonadi::StandardActionManager::DeleteItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::DeleteItems, ki18np("Delete Group", "Delete %1 Groups"));
                        }
                        if (mGenericManager->action(Akonadi::StandardActionManager::CutItems)) {
                            mGenericManager->setActionText(Akonadi::StandardActionManager::CutItems, ki18np("Cut Group", "Cut %1 Groups"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::MoveItemToMenu);
                        if (act) {
                            act->setText(i18n("Move Group To"));
                        }
                        act = mGenericManager->action(Akonadi::StandardActionManager::MoveItemToDialog);
                        if (act) {
                            act->setText(i18n("Move Group To"));
                        }
                        act = mActions.value(StandardContactActionManager::EditItem);
                        if (act) {
                            act->setText(i18n("Edit Group..."));
                        }
                    }
                }
            }
        }

        if (mActions.contains(StandardContactActionManager::CreateContact)) {
            mActions[StandardContactActionManager::CreateContact]->setEnabled(hasWritableCollection(KContacts::Addressee::mimeType()));
        }
        if (mActions.contains(StandardContactActionManager::CreateContactGroup)) {
            mActions[StandardContactActionManager::CreateContactGroup]->setEnabled(hasWritableCollection(KContacts::ContactGroup::mimeType()));
        }

        if (mActions.contains(StandardContactActionManager::EditItem)) {
            bool canEditItem = true;

            // only one selected item can be edited
            canEditItem = canEditItem && (itemCount == 1);

            // check whether parent collection allows changing the item
            const QModelIndexList rows = mItemSelectionModel->selectedRows();
            if (rows.count() == 1) {
                const QModelIndex index = rows.first();
                const auto parentCollection = index.data(EntityTreeModel::ParentCollectionRole).value<Collection>();
                if (parentCollection.isValid()) {
                    canEditItem = canEditItem && (parentCollection.rights() & Collection::CanChangeItem);
                }
            }

            mActions.value(StandardContactActionManager::EditItem)->setEnabled(canEditItem);
        }

        Q_EMIT mParent->actionStateUpdated();
    }

    Collection selectedCollection() const
    {
        if (!mCollectionSelectionModel) {
            return {};
        }

        if (mCollectionSelectionModel->selectedIndexes().isEmpty()) {
            return {};
        }

        const QModelIndex index = mCollectionSelectionModel->selectedIndexes().first();
        if (!index.isValid()) {
            return {};
        }

        return index.data(EntityTreeModel::CollectionRole).value<Collection>();
    }

    void slotCreateContact()
    {
        if (mInterceptedActions.contains(StandardContactActionManager::CreateContact)) {
            return;
        }

        QPointer<Akonadi::ContactEditorDialog> dlg = new Akonadi::ContactEditorDialog(Akonadi::ContactEditorDialog::CreateMode, mParentWidget);
        dlg->setDefaultAddressBook(selectedCollection());
        dlg->exec();
        delete dlg;
    }

    void slotCreateContactGroup()
    {
        if (mInterceptedActions.contains(StandardContactActionManager::CreateContactGroup)) {
            return;
        }

        QPointer<Akonadi::ContactGroupEditorDialog> dlg = new Akonadi::ContactGroupEditorDialog(Akonadi::ContactGroupEditorDialog::CreateMode, mParentWidget);
        dlg->setDefaultAddressBook(selectedCollection());
        dlg->exec();
        delete dlg;
    }

    void slotEditItem()
    {
        if (mInterceptedActions.contains(StandardContactActionManager::EditItem)) {
            return;
        }

        if (!mItemSelectionModel) {
            return;
        }

        if (mItemSelectionModel->selectedIndexes().isEmpty()) {
            return;
        }

        const QModelIndex index = mItemSelectionModel->selectedIndexes().first();
        if (!index.isValid()) {
            return;
        }

        const Item item = index.data(EntityTreeModel::ItemRole).value<Item>();
        if (!item.isValid()) {
            return;
        }

        if (Akonadi::MimeTypeChecker::isWantedItem(item, KContacts::Addressee::mimeType())) {
            QPointer<Akonadi::ContactEditorDialog> dlg = new Akonadi::ContactEditorDialog(Akonadi::ContactEditorDialog::EditMode, mParentWidget);
            QObject::connect(dlg.data(), &Akonadi::ContactEditorDialog::error, mParent, [this](const QString &error) {
                slotContactEditorError(error);
            });
            dlg->setContact(item);
            dlg->exec();
            delete dlg;
        } else if (Akonadi::MimeTypeChecker::isWantedItem(item, KContacts::ContactGroup::mimeType())) {
            QPointer<Akonadi::ContactGroupEditorDialog> dlg = new Akonadi::ContactGroupEditorDialog(Akonadi::ContactGroupEditorDialog::EditMode, mParentWidget);
            dlg->setContactGroup(item);
            dlg->exec();
            delete dlg;
        }
    }

    void slotContactEditorError(const QString &error)
    {
        KMessageBox::error(mParentWidget, i18n("Contact cannot be stored: %1", error), i18nc("@title:window", "Failed to store contact"));
    }

    KActionCollection *const mActionCollection;
    QWidget *const mParentWidget;
    StandardActionManager *mGenericManager = nullptr;
    QItemSelectionModel *mCollectionSelectionModel = nullptr;
    QItemSelectionModel *mItemSelectionModel = nullptr;
    QHash<StandardContactActionManager::Type, QAction *> mActions;
    QSet<StandardContactActionManager::Type> mInterceptedActions;
    StandardContactActionManager *const mParent;
};

StandardContactActionManager::StandardContactActionManager(KActionCollection *actionCollection, QWidget *parent)
    : QObject(parent)
    , d(new StandardContactActionManagerPrivate(actionCollection, parent, this))
{
}

StandardContactActionManager::~StandardContactActionManager() = default;

void StandardContactActionManager::setCollectionSelectionModel(QItemSelectionModel *selectionModel)
{
    d->mCollectionSelectionModel = selectionModel;
    d->mGenericManager->setCollectionSelectionModel(selectionModel);

    connect(selectionModel->model(), &QAbstractItemModel::rowsInserted, this, [this]() {
        d->updateActions();
    });
    connect(selectionModel->model(), &QAbstractItemModel::rowsRemoved, this, [this]() {
        d->updateActions();
    });
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, [this]() {
        d->updateActions();
    });

    d->updateActions();
}

void StandardContactActionManager::setItemSelectionModel(QItemSelectionModel *selectionModel)
{
    d->mItemSelectionModel = selectionModel;
    d->mGenericManager->setItemSelectionModel(selectionModel);

    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, [this]() {
        d->updateActions();
    });

    d->updateActions();
}

QAction *StandardContactActionManager::createAction(Type type)
{
    QAction *action = d->mActions.value(type);
    if (action) {
        return action;
    }

    switch (type) {
    case CreateContact:
        action = new QAction(d->mParentWidget);
        action->setIcon(QIcon::fromTheme(QStringLiteral("contact-new")));
        action->setText(i18n("New &Contact..."));
        action->setWhatsThis(i18n(
            "Create a new contact<p>You will be presented with a dialog where you can add data about a person, including addresses and phone numbers.</p>"));
        d->mActions.insert(CreateContact, action);
        d->mActionCollection->addAction(QStringLiteral("akonadi_contact_create"), action);
        d->mActionCollection->setDefaultShortcut(action, QKeySequence(Qt::CTRL | Qt::Key_N));
        connect(action, &QAction::triggered, this, [this]() {
            d->slotCreateContact();
        });
        break;
    case CreateContactGroup:
        action = new QAction(d->mParentWidget);
        action->setIcon(QIcon::fromTheme(QStringLiteral("user-group-new")));
        action->setText(i18n("New &Group..."));
        action->setWhatsThis(i18n("Create a new group<p>You will be presented with a dialog where you can add a new group of contacts.</p>"));
        d->mActions.insert(CreateContactGroup, action);
        d->mActionCollection->addAction(QStringLiteral("akonadi_contact_group_create"), action);
        d->mActionCollection->setDefaultShortcut(action, QKeySequence(Qt::CTRL | Qt::Key_G));
        connect(action, &QAction::triggered, this, [this]() {
            d->slotCreateContactGroup();
        });
        break;
    case EditItem:
        action = new QAction(d->mParentWidget);
        action->setIcon(QIcon::fromTheme(QStringLiteral("document-edit")));
        action->setText(i18n("Edit Contact..."));
        action->setWhatsThis(
            i18n("Edit the selected contact<p>You will be presented with a dialog where you can edit the data stored about a person, including addresses and "
                 "phone numbers.</p>"));
        action->setEnabled(false);
        d->mActions.insert(EditItem, action);
        d->mActionCollection->addAction(QStringLiteral("akonadi_contact_item_edit"), action);
        d->mActionCollection->setDefaultShortcut(action, QKeySequence(Qt::CTRL | Qt::Key_E));

        connect(action, &QAction::triggered, this, [this]() {
            d->slotEditItem();
        });
        break;
    default:
        Q_ASSERT(false); // should never happen
        break;
    }

    return action;
}

QAction *StandardContactActionManager::createAction(StandardActionManager::Type type)
{
    QAction *act = d->mGenericManager->action(type);
    if (!act) {
        act = d->mGenericManager->createAction(type);
    }
    d->updateGenericAction(type);
    return act;
}

void StandardContactActionManager::createAllActions()
{
    createAction(CreateContact);
    createAction(CreateContactGroup);
    createAction(EditItem);

    d->mGenericManager->createAllActions();
    d->updateGenericAllActions();

    d->updateActions();
}

QAction *StandardContactActionManager::action(Type type) const
{
    if (d->mActions.contains(type)) {
        return d->mActions.value(type);
    }

    return nullptr;
}

QAction *StandardContactActionManager::action(StandardActionManager::Type type) const
{
    return d->mGenericManager->action(type);
}

void StandardContactActionManager::setActionText(StandardActionManager::Type type, const KLocalizedString &text)
{
    d->mGenericManager->setActionText(type, text);
}

void StandardContactActionManager::interceptAction(Type type, bool intercept)
{
    if (intercept) {
        d->mInterceptedActions.insert(type);
    } else {
        d->mInterceptedActions.remove(type);
    }
}

void StandardContactActionManager::interceptAction(StandardActionManager::Type type, bool intercept)
{
    d->mGenericManager->interceptAction(type, intercept);
}

Akonadi::Collection::List StandardContactActionManager::selectedCollections() const
{
    return d->mGenericManager->selectedCollections();
}

Akonadi::Item::List StandardContactActionManager::selectedItems() const
{
    return d->mGenericManager->selectedItems();
}

void StandardContactActionManager::setCollectionPropertiesPageNames(const QStringList &names)
{
    d->mGenericManager->setCollectionPropertiesPageNames(names);
}

#include "moc_standardcontactactionmanager.cpp"
