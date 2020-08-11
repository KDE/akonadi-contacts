/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_EMAILADDRESSSELECTION_P_H
#define AKONADI_EMAILADDRESSSELECTION_P_H

#include <QSharedData>
#include <QString>

#include <item.h>

namespace Akonadi {
class Q_DECL_HIDDEN EmailAddressSelection::Private : public QSharedData
{
public:
    Private();
    Private(const Private &other);

    QString mName;
    QString mEmailAddress;
    Akonadi::Item mItem;
};
}

#endif
