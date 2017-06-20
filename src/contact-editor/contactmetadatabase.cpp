/*
    This file is part of Contact Editor.

    Copyright (c) 2017 Laurent Montel <montel@kde.org>

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

#include "contactmetadatabase_p.h"

using namespace ContactEditor;

class Q_DECL_HIDDEN ContactMetaDataBase::Private
{
public:
    Private()
        : mDisplayNameMode(-1)
    {
    }

    int mDisplayNameMode;
    QVariantList mCustomFieldDescriptions;
};

ContactMetaDataBase::ContactMetaDataBase()
    : d(new Private)
{
}

ContactMetaDataBase::~ContactMetaDataBase()
{
    delete d;
}

void ContactMetaDataBase::loadMetaData(const QVariantMap &metaData)
{
    d->mDisplayNameMode = metaData.value(QStringLiteral("DisplayNameMode"), -1).toInt();

    d->mCustomFieldDescriptions = metaData.value(QStringLiteral("CustomFieldDescriptions")).toList();
}

QVariantMap ContactMetaDataBase::storeMetaData() const
{
    QVariantMap metaData;
    if (d->mDisplayNameMode != -1) {
        metaData.insert(QStringLiteral("DisplayNameMode"), QVariant(d->mDisplayNameMode));
    }

    if (!d->mCustomFieldDescriptions.isEmpty()) {
        metaData.insert(QStringLiteral("CustomFieldDescriptions"), d->mCustomFieldDescriptions);
    }
    return metaData;
}

void ContactMetaDataBase::setDisplayNameMode(int mode)
{
    d->mDisplayNameMode = mode;
}

int ContactMetaDataBase::displayNameMode() const
{
    return d->mDisplayNameMode;
}

void ContactMetaDataBase::setCustomFieldDescriptions(const QVariantList &descriptions)
{
    d->mCustomFieldDescriptions = descriptions;
}

QVariantList ContactMetaDataBase::customFieldDescriptions() const
{
    return d->mCustomFieldDescriptions;
}
