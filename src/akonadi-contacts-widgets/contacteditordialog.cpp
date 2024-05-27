/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contacteditordialog.h"

#include "contacteditor.h"
#include <Akonadi/CollectionComboBox>
#include <Akonadi/Item>

#include <KContacts/Addressee>

#include <KConfig>
#include <KLocalizedString>
#include <KMessageBox>

#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Akonadi;
namespace
{
static const char myContactEditorDialogDialogGroupName[] = "ContactEditor";
}
class Akonadi::ContactEditorDialogPrivate
{
public:
    ContactEditorDialogPrivate(ContactEditorDialog::Mode mode,
                               ContactEditorDialog::DisplayMode displaymode,
                               Akonadi::AbstractContactEditorWidget *editorWidget,
                               ContactEditorDialog *parent)
        : q(parent)
        , mMode(mode)
    {
        auto mainWidget = new QWidget(q);

        q->setWindowTitle(mode == ContactEditorDialog::CreateMode ? i18nc("@title:window", "New Contact") : i18nc("@title:window", "Edit Contact"));
        auto mainLayout = new QVBoxLayout(q);
        auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, q);
        q->connect(buttonBox, &QDialogButtonBox::accepted, q, [this]() {
            slotOkClicked();
        });
        q->connect(buttonBox, &QDialogButtonBox::rejected, q, [this]() {
            slotCancelClicked();
        });

        mainLayout->addWidget(mainWidget);
        mainLayout->addWidget(buttonBox);

        auto layout = new QGridLayout(mainWidget);
        layout->setContentsMargins({});

        if (editorWidget) {
            mEditor = new AkonadiContactEditor(mode == ContactEditorDialog::CreateMode ? AkonadiContactEditor::CreateMode : AkonadiContactEditor::EditMode,
                                               editorWidget,
                                               q);
        } else {
            mEditor = new AkonadiContactEditor(mode == ContactEditorDialog::CreateMode ? AkonadiContactEditor::CreateMode : AkonadiContactEditor::EditMode,
                                               displaymode == ContactEditorDialog::FullMode ? AkonadiContactEditor::FullMode : AkonadiContactEditor::VCardMode,
                                               q);
        }

        if (mode == ContactEditorDialog::CreateMode) {
            auto label = new QLabel(i18nc("@label:textbox", "Add to:"), mainWidget);

            mAddressBookBox = new Akonadi::CollectionComboBox(mainWidget);
            mAddressBookBox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
            mAddressBookBox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);

            layout->addWidget(label, 0, 0);
            layout->addWidget(mAddressBookBox, 0, 1);
        }

        layout->addWidget(mEditor, 1, 0, 1, 2);
        layout->setColumnStretch(1, 1);

        QObject::connect(mEditor, &AkonadiContactEditor::contactStored, q, &ContactEditorDialog::contactStored);

        QObject::connect(mEditor, &AkonadiContactEditor::error, q, &ContactEditorDialog::error);

        QObject::connect(mEditor, &AkonadiContactEditor::finished, q, [this]() {
            slotFinish();
        });

        readConfig();
    }

    void slotOkClicked()
    {
        q->accept();
    }

    void slotFinish()
    {
        q->QDialog::accept();
    }

    void slotCancelClicked()
    {
        q->reject();
    }

    void readConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QLatin1StringView(myContactEditorDialogDialogGroupName));
        const QSize size = group.readEntry("Size", QSize(800, 500));
        if (size.isValid()) {
            q->resize(size);
        }
    }

    void writeConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QLatin1StringView(myContactEditorDialogDialogGroupName));
        group.writeEntry("Size", q->size());
        group.sync();
    }

    ContactEditorDialog *const q;
    Akonadi::CollectionComboBox *mAddressBookBox = nullptr;
    const ContactEditorDialog::Mode mMode;
    Akonadi::AkonadiContactEditor *mEditor = nullptr;
};

ContactEditorDialog::ContactEditorDialog(Mode mode, QWidget *parent)
    : QDialog(parent)
    , d(new ContactEditorDialogPrivate(mode, FullMode, nullptr, this))
{
}

ContactEditorDialog::ContactEditorDialog(Mode mode, Akonadi::AbstractContactEditorWidget *editorWidget, QWidget *parent)
    : QDialog(parent)
    , d(new ContactEditorDialogPrivate(mode, FullMode, editorWidget, this))
{
}

ContactEditorDialog::ContactEditorDialog(Mode mode, DisplayMode displayMode, QWidget *parent)
    : QDialog(parent)
    , d(new ContactEditorDialogPrivate(mode, displayMode, nullptr, this))
{
}

ContactEditorDialog::~ContactEditorDialog()
{
    d->writeConfig();
}

void ContactEditorDialog::setContact(const Akonadi::Item &contact)
{
    d->mEditor->loadContact(contact);
}

void ContactEditorDialog::setDefaultAddressBook(const Akonadi::Collection &addressbook)
{
    if (d->mMode == EditMode) {
        return;
    }

    d->mAddressBookBox->setDefaultCollection(addressbook);
}

AkonadiContactEditor *ContactEditorDialog::editor() const
{
    return d->mEditor;
}

void ContactEditorDialog::accept()
{
    if (d->mEditor->hasNoSavedData()) {
        const int answer = KMessageBox::questionTwoActions(this,
                                                           i18nc("@info", "Location was not saved. Do you want to close editor?"),
                                                           i18nc("@title:window", "Confirmation"),
                                                           KGuiItem(i18nc("@action:button", "Close Editor"), QStringLiteral("dialog-close")),
                                                           KGuiItem(i18nc("@action:button", "Do Not Close"), QStringLiteral("dialog-cancel")));
        if (answer == KMessageBox::ButtonCode::SecondaryAction) {
            return;
        }
    }
    if (d->mAddressBookBox) {
        d->mEditor->setDefaultAddressBook(d->mAddressBookBox->currentCollection());
    }
    d->mEditor->saveContactInAddressBook();
}

void ContactEditorDialog::reject()
{
    if (d->mEditor->hasNoSavedData()) {
        const int answer = KMessageBox::questionTwoActions(this,
                                                           i18nc("@info", "Do you really want to cancel?"),
                                                           i18nc("@title:window", "Confirmation"),
                                                           KGuiItem(i18nc("@action:button", "Cancel Editing"), QStringLiteral("dialog-ok")),
                                                           KGuiItem(i18nc("@action:button", "Do Not Cancel"), QStringLiteral("dialog-cancel")));

        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
            QDialog::reject(); // Discard current changes
        }
    } else {
        QDialog::reject();
    }
}

#include "moc_contacteditordialog.cpp"
