/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <QObject>

namespace Akonadi
{
class ContactsTreeModel;

/*!
 * \class Akonadi::EmailAddressSelectionModel
 * \brief Model for selecting email addresses.
 * \inmodule AkonadiContactCore
 * \inheaderfile Akonadi/EmailAddressSelectionModel
 */
class AKONADI_CONTACT_CORE_EXPORT EmailAddressSelectionModel : public QObject
{
    Q_OBJECT
public:
    explicit EmailAddressSelectionModel(QObject *parent = nullptr);
    ~EmailAddressSelectionModel() override;
    [[nodiscard]] Akonadi::ContactsTreeModel *model() const;

private:
    Akonadi::ContactsTreeModel *mModel = nullptr;
};
}
