/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QSharedData>
#include <QString>

#include <Akonadi/Item>

namespace Akonadi
{
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

