/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "utils.h"

#include <KContacts/Addressee>

void Akonadi::Utils::splitCustomField(const QString &str, QString &app, QString &name, QString &value)
{
    const int colon = str.indexOf(QLatin1Char(':'));
    if (colon != -1) {
        const QString tmp = str.left(colon);
        value = str.mid(colon + 1);

        const int dash = tmp.indexOf(QLatin1Char('-'));
        if (dash != -1) {
            app = tmp.left(dash);
            name = tmp.mid(dash + 1);
        }
    }
}

QString Akonadi::Utils::loadCustom(const KContacts::Addressee &contact, const QString &key)
{
    return contact.custom(QStringLiteral("KADDRESSBOOK"), key);
}

void Akonadi::Utils::storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value)
{
    if (value.isEmpty()) {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), key);
    } else {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), key, value);
    }
}
