/*
    SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "selectaddressbookdialog.h"

#include <KConfigGroup>
#include <KLocalizedString>

#include <KContacts/Addressee>
#include <KSharedConfig>

using namespace Akonadi;
class Akonadi::SelectAddressBookDialogPrivate
{
public:
    SelectAddressBookDialogPrivate(SelectAddressBookDialog *qq)
        : q(qq)
    {
        const QStringList mimeTypes(KContacts::Addressee::mimeType());
        q->setMimeTypeFilter(mimeTypes);
        q->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
        q->setWindowTitle(i18nc("@title:window", "Select Address Book"));
        q->setDescription(i18nc("@info", "Select the address book where the contact will be saved:"));
        q->changeCollectionDialogOptions(Akonadi::CollectionDialog::KeepTreeExpanded);
        readConfig();
    }

    ~SelectAddressBookDialogPrivate()
    {
        writeConfig();
    }

    SelectAddressBookDialog *const q;
    void readConfig();
    void writeConfig();
};

void SelectAddressBookDialogPrivate::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectAddressBookDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        q->resize(size);
    }
}

void SelectAddressBookDialogPrivate::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectAddressBookDialog");
    group.writeEntry("Size", q->size());
    group.sync();
}

SelectAddressBookDialog::SelectAddressBookDialog(QWidget *parent)
    : Akonadi::CollectionDialog(parent)
    , d(new Akonadi::SelectAddressBookDialogPrivate(this))
{
}

SelectAddressBookDialog::~SelectAddressBookDialog() = default;
