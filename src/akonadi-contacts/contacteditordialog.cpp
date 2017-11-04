/*
    This file is part of Akonadi Contact.

    Copyright (c) 2007-2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "contacteditordialog.h"

#include "contacteditor.h"

#include <collectioncombobox.h>
#include <item.h>

#include <kcontacts/addressee.h>

#include <KLocalizedString>
#include <KConfig>

#include <QGridLayout>
#include <QLabel>
#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactEditorDialog::Private
{
public:
    Private(ContactEditorDialog::Mode mode, ContactEditorDialog::DisplayMode displaymode, ContactEditor::AbstractContactEditorWidget *editorWidget, ContactEditorDialog *parent)
        : q(parent)
        , mAddressBookBox(nullptr)
        , mMode(mode)
    {
        QWidget *mainWidget = new QWidget(q);

        q->setWindowTitle(mode == ContactEditorDialog::CreateMode ? i18n("New Contact") : i18n("Edit Contact"));
        QVBoxLayout *mainLayout = new QVBoxLayout(q);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, q);
        q->connect(buttonBox, &QDialogButtonBox::accepted, q, [this]() {
            slotOkClicked();
        });
        q->connect(buttonBox, &QDialogButtonBox::rejected, q, [this]() {
            slotCancelClicked();
        });

        mainLayout->addWidget(mainWidget);
        mainLayout->addWidget(buttonBox);

        QGridLayout *layout = new QGridLayout(mainWidget);
        layout->setMargin(0);

        if (editorWidget) {
            mEditor = new AkonadiContactEditor(mode == ContactEditorDialog::CreateMode ? AkonadiContactEditor::CreateMode : AkonadiContactEditor::EditMode, editorWidget, q);
        } else {
            mEditor = new AkonadiContactEditor(mode == ContactEditorDialog::CreateMode ? AkonadiContactEditor::CreateMode : AkonadiContactEditor::EditMode,
                                               displaymode == ContactEditorDialog::FullMode ? AkonadiContactEditor::FullMode : AkonadiContactEditor::VCardMode, q);
        }

        if (mode == ContactEditorDialog::CreateMode) {
            QLabel *label = new QLabel(i18n("Add to:"), mainWidget);

            mAddressBookBox = new CollectionComboBox(mainWidget);
            mAddressBookBox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
            mAddressBookBox->setAccessRightsFilter(Collection::CanCreateItem);

            layout->addWidget(label, 0, 0);
            layout->addWidget(mAddressBookBox, 0, 1);
        }

        layout->addWidget(mEditor, 1, 0, 1, 2);
        layout->setColumnStretch(1, 1);

        connect(mEditor, &AkonadiContactEditor::contactStored,
                q, &ContactEditorDialog::contactStored);

        connect(mEditor, &AkonadiContactEditor::error,
                q, &ContactEditorDialog::error);

        connect(mEditor, &AkonadiContactEditor::finished, q, [this]() {
            slotFinish();
        });

        readConfig();
    }

    void slotOkClicked()
    {
        if (mAddressBookBox) {
            mEditor->setDefaultAddressBook(mAddressBookBox->currentCollection());
        }
        mEditor->saveContactInAddressBook();
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
        KConfigGroup group(&config, QStringLiteral("ContactEditor"));
        const QSize size = group.readEntry("Size", QSize(800, 500));
        if (size.isValid()) {
            q->resize(size);
        }
    }

    void writeConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("ContactEditor"));
        group.writeEntry("Size", q->size());
        group.sync();
    }

    ContactEditorDialog *q;
    CollectionComboBox *mAddressBookBox = nullptr;
    ContactEditorDialog::Mode mMode;
    AkonadiContactEditor *mEditor = nullptr;
};

ContactEditorDialog::ContactEditorDialog(Mode mode, QWidget *parent)
    : QDialog(parent)
    , d(new Private(mode, FullMode, nullptr, this))
{
}

ContactEditorDialog::ContactEditorDialog(Mode mode, ContactEditor::AbstractContactEditorWidget *editorWidget, QWidget *parent)
    : QDialog(parent)
    , d(new Private(mode, FullMode, editorWidget, this))
{
}

ContactEditorDialog::ContactEditorDialog(Mode mode, DisplayMode displayMode, QWidget *parent)
    : QDialog(parent)
    , d(new Private(mode, displayMode, nullptr, this))
{
}

ContactEditorDialog::~ContactEditorDialog()
{
    d->writeConfig();
    delete d;
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
    //Nothing
}

#include "moc_contacteditordialog.cpp"
