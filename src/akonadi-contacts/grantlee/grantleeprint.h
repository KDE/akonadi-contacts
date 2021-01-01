/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEPRINT_H
#define GRANTLEEPRINT_H

#include "akonadi-contact_export.h"

#include <GrantleeTheme/GenericFormatter>
#include <KContacts/Addressee>

namespace KAddressBookGrantlee {

/** Grantlee-based contact printing. */
class AKONADI_CONTACT_EXPORT GrantleePrint : public GrantleeTheme::GenericFormatter
{
public:
    GrantleePrint();
    explicit GrantleePrint(const QString &themePath);
    ~GrantleePrint();

    Q_REQUIRED_RESULT QString contactsToHtml(const KContacts::Addressee::List &contacts);

private:
    void init();
};
}
#endif // GRANTLEEPRINT_H
