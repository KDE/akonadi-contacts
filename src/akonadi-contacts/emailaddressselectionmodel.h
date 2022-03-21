/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"
#include <QObject>

namespace Akonadi
{
class ContactsTreeModel;
class AKONADI_CONTACT_EXPORT EmailAddressSelectionModel : public QObject
{
    Q_OBJECT
public:
    explicit EmailAddressSelectionModel(QObject *parent = nullptr);
    ~EmailAddressSelectionModel() override;
    Q_REQUIRED_RESULT Akonadi::ContactsTreeModel *model() const;

private:
    Akonadi::ContactsTreeModel *mModel = nullptr;
};
}
