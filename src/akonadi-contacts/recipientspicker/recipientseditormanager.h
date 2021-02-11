/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef RECIPIENTSEDITORMANAGER_H
#define RECIPIENTSEDITORMANAGER_H

#include "akonadi-contact_export.h"
#include <QObject>

namespace Akonadi
{
class EmailAddressSelectionModel;
}

namespace Akonadi
{
class AKONADI_CONTACT_EXPORT RecipientsEditorManager : public QObject
{
    Q_OBJECT
public:
    explicit RecipientsEditorManager(QObject *parent = nullptr);
    ~RecipientsEditorManager() override;

    static RecipientsEditorManager *self();
    Q_REQUIRED_RESULT Akonadi::EmailAddressSelectionModel *model();

private:
    Akonadi::EmailAddressSelectionModel *mModel = nullptr;
};
}

#endif // RECIPIENTSEDITORMANAGER_H
