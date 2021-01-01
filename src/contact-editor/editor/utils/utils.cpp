/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "utils.h"

#include <KContacts/Addressee>

void ContactEditor::Utils::splitCustomField(const QString &str, QString &app, QString &name, QString &value)
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

QString ContactEditor::Utils::loadCustom(const KContacts::Addressee &contact, const QString &key)
{
    return contact.custom(QStringLiteral("KADDRESSBOOK"), key);
}

void ContactEditor::Utils::storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value)
{
    if (value.isEmpty()) {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), key);
    } else {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), key, value);
    }
}
