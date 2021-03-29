/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Felix Mauch (felix_mauch@web.de)

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

namespace KContacts
{
class PhoneNumber;
}

class SendSmsAction
{
public:
    void sendSms(const KContacts::PhoneNumber &number);
};

