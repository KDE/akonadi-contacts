/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2007-2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupeditordialog.h"

#include "contactgroupeditor.h"
#include "contactgroupeditor_p.h"
#include <Akonadi/CollectionComboBox>
#include <Akonadi/Item>
#include <KContacts/ContactGroup>
#include <KLocalizedString>

#include <KConfig>
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
static const char myContactGroupEditorDialogGroupName[] = "ContactGroupEditorDialog";
}
class Akonadi::ContactGroupEditorDialogPrivate
{
public:
    ContactGroupEditorDialogPrivate(ContactGroupEditorDialog *qq, ContactGroupEditorDialog::Mode mode)
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
        KConfigGroup group(&config, myContactGroupEditorDialogGroupName);
        const QSize size = group.readEntry("Size", QSize(470, 400));
        if (size.isValid()) {
            q->resize(size);
        }
    }

    void writeConfig()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, myContactGroupEditorDialogGroupName);
        group.writeEntry("Size", q->size());
        group.sync();
    }

    ContactGroupEditorDialog *const q;
    CollectionComboBox *mAddressBookBox = nullptr;
    ContactGroupEditor *mEditor = nullptr;
    const ContactGroupEditorDialog::Mode mMode;
    QPushButton *okButton = nullptr;
};

ContactGroupEditorDialog::ContactGroupEditorDialog(Mode mode, QWidget *parent)
    : QDialog(parent)
    , d(new ContactGroupEditorDialogPrivate(this, mode))
{
    setWindowTitle(mode == CreateMode ? i18nc("@title:window", "New Contact Group") : i18nc("@title:window", "Edit Contact Group"));
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
    layout->setContentsMargins({});

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
    const int answer = KMessageBox::questionTwoActions(this,
                                                       i18nc("@info", "Do you really want to cancel?"),
                                                       i18nc("@title:window", "Confirmation"),
                                                       KGuiItem(i18nc("@action:button", "Cancel Editing"), QStringLiteral("dialog-ok")),
                                                       KGuiItem(i18nc("@action:button", "Do Not Cancel"), QStringLiteral("dialog-cancel")));

    if (answer == KMessageBox::ButtonCode::PrimaryAction) {
        QDialog::reject(); // Discard current changes
    }
}

#include "moc_contactgroupeditordialog.cpp"
#include <kwidgetsaddons_version.h>
