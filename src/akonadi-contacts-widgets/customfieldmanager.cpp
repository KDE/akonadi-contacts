/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldmanager_p.h"

#include <KConfig>
#include <KConfigGroup>

void CustomFieldManager::setGlobalCustomFieldDescriptions(const CustomField::List &customFields)
{
    KConfig config(QStringLiteral("akonadi_contactrc"));
    KConfigGroup group(&config, QStringLiteral("GlobalCustomFields"));

    group.deleteGroup();
    for (const CustomField &field : customFields) {
        const QString key = field.key();
        const QString value = CustomField::typeToString(field.type()) + u':' + field.title();

        group.writeEntry(key, value);
    }
}

CustomField::List CustomFieldManager::globalCustomFieldDescriptions()
{
    KConfig config(QStringLiteral("akonadi_contactrc"));
    const KConfigGroup group(&config, QStringLiteral("GlobalCustomFields"));

    CustomField::List customFields;

    const QStringList keys = group.keyList();
    customFields.reserve(keys.count());
    for (const QString &key : keys) {
        CustomField field;
        field.setKey(key);
        field.setScope(CustomField::GlobalScope);

        const QString value = group.readEntry(key, QString());
        const int pos = value.indexOf(u':');
        if (pos != -1) {
            field.setType(CustomField::stringToType(value.left(pos - 1)));
            field.setTitle(value.mid(pos + 1));
        }

        customFields << field;
    }

    return customFields;
}
