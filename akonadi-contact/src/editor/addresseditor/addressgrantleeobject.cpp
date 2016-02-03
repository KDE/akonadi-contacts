/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#include "addressgrantleeobject.h"
#include "iconnamecache_p.h"
#include <KIconLoader>
#include <KLocalizedString>
#include <QUrlQuery>

AddressGrantleeObject::AddressGrantleeObject(const KContacts::Address &address, int addressIndex, QObject *parent)
    : QObject(parent),
      mAddress(address),
      mAddressIndex(addressIndex)
{

}

AddressGrantleeObject::~AddressGrantleeObject()
{

}

QString AddressGrantleeObject::formattedAddress() const
{
    QString str;
    if (mAddress.label().isEmpty()) {
        str = mAddress.formattedAddress().trimmed().toHtmlEscaped();
    } else {
        str = mAddress.label().toHtmlEscaped();
    }
    return str;
}

QString AddressGrantleeObject::createActionUrl(const QString &actionName) const
{
    QUrl url;
    url.setScheme(QStringLiteral("addresslocationaction"));
    url.setPath(actionName);
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("id"), QString::number(mAddressIndex));
    url.setQuery(query);
    return url.toDisplayString();
}

QString AddressGrantleeObject::preferredAddressAction() const
{
    QString text;
    if (preferredAddress()) {
        const QString iconPath = IconNameCache::instance()->iconPath(QStringLiteral("bookmarks"), KIconLoader::Small);
        text = QStringLiteral("<img class=\"headimage\" title=\"%1\" src=\"file:///%2\"></a>\n")
                .arg(i18n("Remove Address"), iconPath );
    }
    return text;
}

QString AddressGrantleeObject::removeAddressAction() const
{
    const QString iconPath = IconNameCache::instance()->iconPath(QStringLiteral("edit-delete"), KIconLoader::Small);
    const QString text = QStringLiteral("<a href=\"%1\"><img class=\"headimage\" title=\"%3\" src=\"file:///%2\"></a>\n")
                         .arg(createActionUrl(QStringLiteral("removeaddress")), iconPath, i18n("Remove Address"));
    return text;
}

QString AddressGrantleeObject::modifyAddressAction() const
{
    const QString iconPath = IconNameCache::instance()->iconPath(QStringLiteral("document-edit"), KIconLoader::Small);
    const QString text = QStringLiteral("<a href=\"%1\"><img class=\"headimage\" title=\"%3\" src=\"file:///%2\"></a>\n")
                         .arg(createActionUrl(QStringLiteral("editaddress")), iconPath, i18n("Edit Address"));
    return text;
}

QString AddressGrantleeObject::type() const
{
    //TODO
    return {};
}

bool AddressGrantleeObject::preferredAddress() const
{
    return (mAddress.type() & KContacts::Address::Pref);
}
