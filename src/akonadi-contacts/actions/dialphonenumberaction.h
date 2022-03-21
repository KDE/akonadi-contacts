/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

namespace KContacts
{
class PhoneNumber;
}

namespace Akonadi
{
/**
 * @short An action to dial the phone number of a contact.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class DialPhoneNumberAction
{
public:
    void dialNumber(const KContacts::PhoneNumber &number);
};
}
