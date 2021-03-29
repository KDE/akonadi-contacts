/*
    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "akonadi-contact_export.h"
#include <AkonadiWidgets/CollectionDialog>

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
    explicit SelectAddressBookDialog(QWidget *parent = nullptr);
    ~SelectAddressBookDialog() override;

private:
    SelectAddressBookDialogPrivate *const d;
};
}

