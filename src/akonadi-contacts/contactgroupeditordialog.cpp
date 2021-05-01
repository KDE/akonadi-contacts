/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupeditordialog.h"

#include "contactgroupeditor.h"
#include "contactgroupeditor_p.h"

#include <KLocalizedString>
#include <collectioncombobox.h>
#include <item.h>
#include <kcontacts/contactgroup.h>

#include <KConfig>
#include <KMessageBox>

#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactGroupEditorDialog::Private
{
public:
    Private(ContactGroupEditorDialog *qq, ContactGroupEditorDialog::Mode mode)
        : q(qq)
        , mMode(mode)
    {
    }

    void slotGroupNameChanged(const QString &name)
    {
        bool isValid = !(name.contains(QLatin1Char('@')) || name.contains(QLatin1Char('.')));
        okButton->setEnabled(!name.trimmed().isEmpty() && isValid);
        mEditor->groupNameIsValid(isValid);
    }

    void readConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("ContactGroupEditorDialog"));
        const QSize size = group.readEntry("Size", QSize(470, 400));
        if (size.isValid()) {
            q->resize(size);
        }
    }

    void writeConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("ContactGroupEditorDialog"));
        group.writeEntry("Size", q->size());
        group.sync();
    }

    ContactGroupEditorDialog *const q;
    CollectionComboBox *mAddressBookBox = nullptr;
    ContactGroupEditor *mEditor = nullptr;
    ContactGroupEditorDialog::Mode mMode;
    QPushButton *okButton = nullptr;
};

ContactGroupEditorDialog::ContactGroupEditorDialog(Mode mode, QWidget *parent)
    : QDialog(parent)
    , d(new Private(this, mode))
{
    setWindowTitle(mode == CreateMode ? i18n("New Contact Group") : i18n("Edit Contact Group"));
    auto mainLayout = new QVBoxLayout(this);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    d->okButton = buttonBox->button(QDialogButtonBox::Ok);
    d->okButton->setDefault(true);
    d->okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactGroupEditorDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactGroupEditorDialog::reject);

    // Disable default button, so that finish editing of
    // a member with the Enter key does not close the dialog
    d->okButton->setAutoDefault(false);
    buttonBox->button(QDialogButtonBox::Cancel)->setAutoDefault(false);

    auto mainWidget = new QWidget(this);

    auto layout = new QGridLayout(mainWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    d->mEditor = new Akonadi::ContactGroupEditor(mode == CreateMode ? Akonadi::ContactGroupEditor::CreateMode : Akonadi::ContactGroupEditor::EditMode, this);

    if (mode == CreateMode) {
        auto label = new QLabel(i18n("Add to:"), mainWidget);

        d->mAddressBookBox = new CollectionComboBox(mainWidget);
        d->mAddressBookBox->setMimeTypeFilter(QStringList() << KContacts::ContactGroup::mimeType());
        d->mAddressBookBox->setAccessRightsFilter(Collection::CanCreateItem);

        layout->addWidget(label, 0, 0);
        layout->addWidget(d->mAddressBookBox, 0, 1);
    }

    layout->addWidget(d->mEditor, 1, 0, 1, 2);
    layout->setColumnStretch(1, 1);

    connect(d->mEditor, &ContactGroupEditor::contactGroupStored, this, &ContactGroupEditorDialog::contactGroupStored);
    connect(d->mEditor->d->mGui.groupName, &QLineEdit::textChanged, this, [this](const QString &str) {
        d->slotGroupNameChanged(str);
    });

    d->okButton->setEnabled(!d->mEditor->d->mGui.groupName->text().trimmed().isEmpty());
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

void ContactGroupEditorDialog::reject()
{
    if (KMessageBox::questionYesNo(this, i18nc("@info", "Do you really want to cancel?"), i18nc("@title:window", "Confirmation")) == KMessageBox::Yes) {
        QDialog::reject(); // Discard current changes
    }
}

#include "moc_contactgroupeditordialog.cpp"
