/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_SHOWADDRESSACTION_H
#define AKONADI_SHOWADDRESSACTION_H

namespace KContacts
{
class Address;
}

namespace Akonadi
{
/**
 * @short A contact action to show the address of a contact on a map.
 *
 * This class provides the functionality to show the postal address
 * of a contact on a map in a webbrowser.
 *
 * Example:
 *
 * @code
 *
 * const KContacts::Addressee contact = ...
 *
 * const KContacts::Address::List addresses = contact.addresses();
 * if ( !addresses.isEmpty() ) {
 *   Akonadi::ShowAddressAction action;
 *   action.showAddress( addresses.first() );
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class ShowAddressAction
{
public:
    void showAddress(const KContacts::Address &address);
};
}

#endif
