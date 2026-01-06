/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"

#include "emailaddressselectionwidget.h"

#include <KContacts/Addressee>
#include <QDialog>
namespace Akonadi
{
class AKONADI_CONTACT_WIDGETS_EXPORT AbstractEmailAddressSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AbstractEmailAddressSelectionDialog(QWidget *parent = nullptr);
    ~AbstractEmailAddressSelectionDialog() override;

    /*!
     * Returns the list of selected email addresses.
     */
    [[nodiscard]] virtual Akonadi::EmailAddressSelection::List selectedAddresses() const = 0;

    /*!
     * Returns the email address selection view that is used.
     */
    [[nodiscard]] virtual Akonadi::EmailAddressSelectionWidget *view() const = 0;
Q_SIGNALS:
    void insertAddresses(const KContacts::Addressee::List &list);
};
}
