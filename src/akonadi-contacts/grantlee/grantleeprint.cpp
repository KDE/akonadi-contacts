/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeprint.h"
#include "contactgrantleewrapper.h"

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>
#else
#include <KTextTemplate/Context>
#include <KTextTemplate/Engine>
#include <KTextTemplate/MetaType>
#include <KTextTemplate/TemplateLoader>
#endif

#include <QMetaProperty>
#include <QVariant>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_BEGIN_LOOKUP(QUrl)
#else
KTEXTTEMPLATE_BEGIN_LOOKUP(QUrl)
#endif
if (property == QLatin1String("scheme")) {
    return object.scheme();
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_END_LOOKUP
#else
KTEXTTEMPLATE_END_LOOKUP
#endif

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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::registerMetaType<QUrl>();
#else
    KTextTemplate::registerMetaType<QUrl>();
#endif
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
