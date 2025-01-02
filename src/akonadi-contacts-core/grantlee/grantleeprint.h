/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include <GrantleeTheme/GenericFormatter>
#include <KContacts/Addressee>

namespace KAddressBookGrantlee
{
/** Grantlee-based contact printing. */
class AKONADI_CONTACT_CORE_EXPORT GrantleePrint : public GrantleeTheme::GenericFormatter
{
public:
    GrantleePrint();
    explicit GrantleePrint(const QString &themePath);
    ~GrantleePrint();

    [[nodiscard]] QString contactsToHtml(const KContacts::Addressee::List &contacts);

private:
    AKONADI_CONTACT_CORE_NO_EXPORT void init();
};
}
