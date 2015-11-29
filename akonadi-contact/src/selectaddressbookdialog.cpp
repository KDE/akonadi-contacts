/*
    Copyright (c) 2013-2015 Montel Laurent <montel@kde.org>
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

#include "selectaddressbookdialog.h"

#include <KLocalizedString>
#include <KConfigGroup>

#include <kcontacts/addressee.h>
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
        q->setDescription(
            i18nc("@info",
                  "Select the address book where the contact will be saved:"));
        q->changeCollectionDialogOptions(Akonadi::CollectionDialog::KeepTreeExpanded);
        readConfig();
    }
    ~SelectAddressBookDialogPrivate()
    {
        writeConfig();
    }

    SelectAddressBookDialog *q;
    void readConfig();
    void writeConfig();
};

void SelectAddressBookDialogPrivate::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SelectAddressBookDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        q->resize(size);
    }
}

void SelectAddressBookDialogPrivate::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SelectAddressBookDialog");
    group.writeEntry("Size", q->size());
    group.sync();
}

SelectAddressBookDialog::SelectAddressBookDialog(QWidget *parent)
    : Akonadi::CollectionDialog(parent),
      d(new Akonadi::SelectAddressBookDialogPrivate(this))
{
}

SelectAddressBookDialog::~SelectAddressBookDialog()
{
    delete d;
}

