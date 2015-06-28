/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#include "improtocols.h"

#include <kiconloader.h>
#include <kservicetypetrader.h>
#include <QDebug>
#include <KService>
IMProtocols *IMProtocols::mSelf = Q_NULLPTR;

IMProtocols::IMProtocols()
{
    const KService::List list = KServiceTypeTrader::self()->query(QStringLiteral("KABC/IMProtocol"));
    KService::List::ConstIterator it = list.constBegin();
    KService::List::ConstIterator lastItem = list.constEnd();
    QMap<QString, QString> sortingMap;
    for ( ; it != lastItem; ++it )
    {
        IMProtocolInfo info((*it)->name(), (*it)->icon());
        const QString propertyName = (*it)->property(QStringLiteral("X-KDE-InstantMessagingKABCField")).toString();
        mPluginInfos.insert(propertyName, info);
        sortingMap.insert((*it)->name(), propertyName);
    }

    QMapIterator<QString, QString> sortedIt(sortingMap);
    while (sortedIt.hasNext()) {
        sortedIt.next();
        mSortedProtocols.append(sortedIt.value());
    }
}

IMProtocols::~IMProtocols()
{
}

IMProtocols *IMProtocols::self()
{
    if (!mSelf) {
        mSelf = new IMProtocols;
    }

    return mSelf;
}

QStringList IMProtocols::protocols() const
{
    return mSortedProtocols;
}

QString IMProtocols::name(const QString &protocol) const
{
    if (!mPluginInfos.contains(protocol)) {
        return QString();
    }

    return mPluginInfos.value(protocol).name();
}

QString IMProtocols::icon(const QString &protocol) const
{
    if (!mPluginInfos.contains(protocol)) {
        return QString();
    }

    return mPluginInfos.value(protocol).icon();
}


IMProtocolInfo::IMProtocolInfo()
{

}

IMProtocolInfo::IMProtocolInfo(const QString &name, const QString &icon)
    : mName(name),
      mIcon(icon)
{

}

QString IMProtocolInfo::name() const
{
    return mName;
}

void IMProtocolInfo::setName(const QString &name)
{
    mName = name;
}

QString IMProtocolInfo::icon() const
{
    return mIcon;
}

void IMProtocolInfo::setIcon(const QString &icon)
{
    mIcon = icon;
}
