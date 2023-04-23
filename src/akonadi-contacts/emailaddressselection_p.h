/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <QSharedData>
#include <QString>

#include <Akonadi/Item>

namespace Akonadi
{
class AKONADI_CONTACT_CORE_EXPORT EmailAddressSelectionPrivate : public QSharedData
{
public:
    EmailAddressSelectionPrivate();
    EmailAddressSelectionPrivate(const EmailAddressSelectionPrivate &other);

    QString mName;
    QString mEmailAddress;
    Akonadi::Item mItem;
};
}
