/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef UTILS_H
#define UTILS_H

#include <QString>
namespace KContacts {
class Addressee;
}

namespace ContactEditor {
namespace Utils {
void splitCustomField(const QString &str, QString &app, QString &name, QString &value);
Q_REQUIRED_RESULT QString loadCustom(const KContacts::Addressee &contact, const QString &key);
void storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value);
}
}
#endif // UTILS_H
