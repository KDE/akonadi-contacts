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

#ifndef SELECTEDCOLLECTIONDIALOG_H
#define SELECTEDCOLLECTIONDIALOG_H

#include <CollectionDialog>
#include "akonadi-contact_export.h"

namespace Akonadi
{
class SelectAddressBookDialogPrivate;
/**
 * @brief The SelectAddressBookDialog class This class allows to select addressbook where saving contacts
 * @since 5.1
 */
class AKONADI_CONTACT_EXPORT SelectAddressBookDialog : public Akonadi::CollectionDialog
{
    Q_OBJECT
public:
    explicit SelectAddressBookDialog(QWidget *parent = Q_NULLPTR);
    ~SelectAddressBookDialog();

private:
    SelectAddressBookDialogPrivate *const d;
};
}

#endif // SELECTEDCOLLECTIONDIALOG_H
