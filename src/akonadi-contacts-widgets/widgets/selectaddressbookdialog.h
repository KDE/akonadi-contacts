/*
    SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <Akonadi/CollectionDialog>

#include <memory>

namespace Akonadi
{
class SelectAddressBookDialogPrivate;
/*!
 * \class Akonadi::SelectAddressBookDialog
 * \brief The SelectAddressBookDialog class This class allows to select addressbook where saving contacts
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/SelectAddressBookDialog
 * \since 5.1
 */
class AKONADI_CONTACT_WIDGETS_EXPORT SelectAddressBookDialog : public Akonadi::CollectionDialog
{
    Q_OBJECT
public:
    /*!
     * Creates a new select address book dialog.
     *
     * \a parent The parent widget.
     */
    explicit SelectAddressBookDialog(QWidget *parent = nullptr);

    /*!
     * Destroys the select address book dialog.
     */
    ~SelectAddressBookDialog() override;

private:
    std::unique_ptr<SelectAddressBookDialogPrivate> const d;
};
}
