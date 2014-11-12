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

#include "contactgroupeditordialog.h"

#include "contactgroupeditor.h"
#include "contactgroupeditor_p.h"

#include <collectioncombobox.h>
#include <item.h>
#include <kcontacts/contactgroup.h>
#include <KLocalizedString>
#include <klocalizedstring.h>

#include <klineedit.h>
#include <KConfig>

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QVBoxLayout>

using namespace Akonadi;

class ContactGroupEditorDialog::Private
{
public:
    Private(ContactGroupEditorDialog *qq, ContactGroupEditorDialog::Mode mode)
        : q(qq)
        , mAddressBookBox(0)
        , mEditor(0)
        , mMode(mode)
    {
    }

    void slotGroupNameChanged(const QString &name)
    {
        bool isValid = !(name.contains(QLatin1Char('@')) || name.contains(QLatin1Char('.')));
        okButton->setEnabled(!name.isEmpty() && isValid);
        mEditor->groupNameIsValid(isValid);
    }

    void readConfig()
    {
        KConfig config(QLatin1String("akonadi_contactrc"));
        KConfigGroup group(&config, QLatin1String("ContactGroupEditorDialog"));
        const QSize size = group.readEntry("Size", QSize(470, 400));
        if (size.isValid()) {
            q->resize(size);
        }
    }
    void writeConfig()
    {
        KConfig config(QLatin1String("akonadi_contactrc"));
        KConfigGroup group(&config, QLatin1String("ContactGroupEditorDialog"));
        group.writeEntry("Size", q->size());
        group.sync();
    }
    ContactGroupEditorDialog *q;
    CollectionComboBox *mAddressBookBox;
    ContactGroupEditor *mEditor;
    ContactGroupEditorDialog::Mode mMode;
    QPushButton *okButton;
};

ContactGroupEditorDialog::ContactGroupEditorDialog(Mode mode, QWidget *parent)
    : QDialog(parent), d(new Private(this, mode))
{
    setWindowTitle(mode == CreateMode ? i18n("New Contact Group") : i18n("Edit Contact Group"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    d->okButton = buttonBox->button(QDialogButtonBox::Ok);
    d->okButton->setDefault(true);
    d->okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactGroupEditorDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactGroupEditorDialog::reject);
    mainLayout->addWidget(buttonBox);

    // Disable default button, so that finish editing of
    // a member with the Enter key does not close the dialog
    d->okButton->setAutoDefault(false);
    buttonBox->button(QDialogButtonBox::Cancel)->setAutoDefault(false);

    QWidget *mainWidget = new QWidget(this);

    QGridLayout *layout = new QGridLayout(mainWidget);

    d->mEditor = new Akonadi::ContactGroupEditor(mode == CreateMode ?
                                                 Akonadi::ContactGroupEditor::CreateMode : Akonadi::ContactGroupEditor::EditMode,
                                                 this);

    if (mode == CreateMode) {
        QLabel *label = new QLabel(i18n("Add to:"), mainWidget);

        d->mAddressBookBox = new CollectionComboBox(mainWidget);
        d->mAddressBookBox->setMimeTypeFilter(QStringList() << KContacts::ContactGroup::mimeType());
        d->mAddressBookBox->setAccessRightsFilter(Collection::CanCreateItem);

        layout->addWidget(label, 0, 0);
        layout->addWidget(d->mAddressBookBox, 0, 1);
    }

    layout->addWidget(d->mEditor, 1, 0, 1, 2);
    layout->setColumnStretch(1, 1);

    connect(d->mEditor, &ContactGroupEditor::contactGroupStored, this, &ContactGroupEditorDialog::contactGroupStored);
    connect(d->mEditor->d->mGui.groupName, SIGNAL(textChanged(QString)),
            this, SLOT(slotGroupNameChanged(QString)));

    d->okButton->setEnabled(!d->mEditor->d->mGui.groupName->text().isEmpty());
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(buttonBox);
    d->readConfig();
}

ContactGroupEditorDialog::~ContactGroupEditorDialog()
{
    d->writeConfig();
    delete d;
}

void ContactGroupEditorDialog::setContactGroup(const Akonadi::Item &group)
{
    d->mEditor->loadContactGroup(group);
}

void ContactGroupEditorDialog::setDefaultAddressBook(const Akonadi::Collection &addressbook)
{
    if (d->mMode == EditMode) {
        return;
    }

    d->mAddressBookBox->setDefaultCollection(addressbook);
}

ContactGroupEditor *ContactGroupEditorDialog::editor() const
{
    return d->mEditor;
}

void ContactGroupEditorDialog::slotAccepted()
{
    if (d->mAddressBookBox) {
        d->mEditor->setDefaultAddressBook(d->mAddressBookBox->currentCollection());
    }

    if (d->mEditor->saveContactGroup()) {
        accept();
    }
}

#include "moc_contactgroupeditordialog.cpp"
