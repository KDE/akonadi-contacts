/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include <QList>
#include <QSharedDataPointer>
#include <QString>

namespace Akonadi
{
class Item;
class EmailAddressSelectionPrivate;

/*!
 * \class Akonadi::EmailAddressSelection
 * \brief An selection of an email address and corresponding name.
 * \inmodule AkonadiContactCore
 * \inheaderfile Akonadi/EmailAddressSelection
 *
 * This class encapsulates the selection of an email address and name
 * as it is returned by EmailAddressSelectionWidget or EmailAddressSelectionDialog.
 *
 * It offers convenience methods to retrieve the quoted version of the
 * email address and access to the Akonadi item that is associated with
 * this address.
 *
 * \author Tobias Koenig <tokoe@kde.org>
 * \since 4.5
 */
class AKONADI_CONTACT_CORE_EXPORT EmailAddressSelection
{
public:
    /*!
     * A list of email address selection objects.
     */
    using List = QList<EmailAddressSelection>;

    /*!
     * Creates a new email address selection.
     */
    EmailAddressSelection();

    /*!
     * Creates a new email address selection from an \a other selection.
     */
    EmailAddressSelection(const EmailAddressSelection &other);

    /*!
     * Replaces this email address selection with the \a other selection.
     */
    EmailAddressSelection &operator=(const EmailAddressSelection &other);

    /*!
     * Destroys the email address selection.
     */
    ~EmailAddressSelection();

    /*!
     * Returns whether the selection is valid.
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Returns the name that is associated with the selected email address.
     */
    [[nodiscard]] QString name() const;
    void setName(const QString &name);

    /*!
     * Returns the address part of the selected email address.
     *
     * \note If a contact group has been selected, the name of the contact
     *       group is returned here and must be expanded by the caller.
     */
    [[nodiscard]] QString email() const;
    void setEmail(const QString &email);

    /*!
     * Returns the name and email address together, properly quoted if needed.
     *
     * \note If a contact group has been selected, the name of the contact
     *       group is returned here and must be expanded by the caller.
     */
    [[nodiscard]] QString quotedEmail() const;

    /*!
     * Returns the Akonadi item that is associated with the selected email address.
     */
    [[nodiscard]] Akonadi::Item item() const;

    /*!
     */
    void setItem(const Akonadi::Item &item);

private:
    friend class EmailAddressSelectionWidget;

    QSharedDataPointer<EmailAddressSelectionPrivate> d;
};
}

Q_DECLARE_TYPEINFO(Akonadi::EmailAddressSelection, Q_RELOCATABLE_TYPE);
