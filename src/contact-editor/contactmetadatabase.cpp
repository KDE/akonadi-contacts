/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
