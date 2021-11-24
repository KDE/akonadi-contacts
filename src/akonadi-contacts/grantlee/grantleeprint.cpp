/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeprint.h"
#include "contactgrantleewrapper.h"

#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>

#include <QMetaProperty>
#include <QVariant>

GRANTLEE_BEGIN_LOOKUP(QUrl)
if (property == QLatin1String("scheme")) {
    return object.scheme();
}
GRANTLEE_END_LOOKUP

using namespace KAddressBookGrantlee;

GrantleePrint::GrantleePrint()
{
    init();
}

GrantleePrint::GrantleePrint(const QString &themePath)
    : GrantleeTheme::GenericFormatter(QStringLiteral("theme.html"), themePath)
{
    init();
}

GrantleePrint::~GrantleePrint() = default;

void GrantleePrint::init()
{
    Grantlee::registerMetaType<QUrl>();
}

QString GrantleePrint::contactsToHtml(const KContacts::Addressee::List &contacts)
{
    if (!errorMessage().isEmpty()) {
        return errorMessage();
    }

    if (contacts.isEmpty()) {
        return {};
    }
    QVariantList contactsList;
    contactsList.reserve(contacts.count());
    for (const KContacts::Addressee &contact : contacts) {
        contactsList.push_back(QVariant::fromValue(ContactGrantleeWrapper(contact)));
    }
    QVariantHash mapping;
    mapping.insert(QStringLiteral("contacts"), contactsList);

    return render(mapping);
}
