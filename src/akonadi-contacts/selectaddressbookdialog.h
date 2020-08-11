/*
    SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef SELECTADDRESSBOOKDIALOG_H
#define SELECTADDRESSBOOKDIALOG_H

#include <AkonadiWidgets/CollectionDialog>
#include "akonadi-contact_export.h"

namespace Akonadi {
class SelectAddressBookDialogPrivate;
/**
 * @brief The SelectAddressBookDialog class This class allows to select addressbook where saving contacts
 * @since 5.1
 */
class AKONADI_CONTACT_EXPORT SelectAddressBookDialog : public Akonadi::CollectionDialog
{
    Q_OBJECT
public:
    explicit SelectAddressBookDialog(QWidget *parent = nullptr);
    ~SelectAddressBookDialog();

private:
    SelectAddressBookDialogPrivate *const d;
};
}

#endif // SELECTADDRESSBOOKDIALOG_H
