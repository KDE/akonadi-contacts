/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <QObject>

namespace Akonadi
{
class EmailAddressSelectionModel;
}

namespace AkonadiContactWidgets
{
class AKONADI_CONTACT_CORE_EXPORT RecipientsEditorManager : public QObject
{
    Q_OBJECT
public:
    explicit RecipientsEditorManager(QObject *parent = nullptr);
    ~RecipientsEditorManager() override;

    static RecipientsEditorManager *self();
    Q_REQUIRED_RESULT Akonadi::EmailAddressSelectionModel *model();

private:
    Akonadi::EmailAddressSelectionModel *const mModel;
};
}
