/*
    This file is part of Contact Editor.

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

#ifndef CONTACTEDITOR_CONTACT_IMPROTOCOLS_H
#define CONTACTEDITOR_CONTACT_IMPROTOCOLS_H

#include <kplugininfo.h>

#include "contacteditor_export.h"

class IMProtocolInfo
{
public:
    IMProtocolInfo();

    IMProtocolInfo(const QString &name, const QString &icon);

    Q_REQUIRED_RESULT QString icon() const;
    void setIcon(const QString &icon);
    Q_REQUIRED_RESULT QString name() const;
    void setName(const QString &name);
private:
    QString mName;
    QString mIcon;
};

class CONTACTEDITOR_EXPORT IMProtocols
{
public:
    ~IMProtocols();

    static IMProtocols *self();

    /**
     * Returns the protocol identifiers in a sorted order.
     */
    Q_REQUIRED_RESULT QStringList protocols() const;

    Q_REQUIRED_RESULT QString name(const QString &protocol) const;
    Q_REQUIRED_RESULT QString icon(const QString &protocol) const;

private:
    Q_DISABLE_COPY(IMProtocols)
    IMProtocols();

    static IMProtocols *mSelf;

    QMap<QString, IMProtocolInfo> mPluginInfos;
    QStringList mSortedProtocols;
};

#endif
