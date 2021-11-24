/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "recipientseditormanager.h"

#include "emailaddressselectionmodel.h"

using namespace Akonadi;

RecipientsEditorManager::RecipientsEditorManager(QObject *parent)
    : QObject(parent)
{
}

RecipientsEditorManager::~RecipientsEditorManager() = default;

RecipientsEditorManager *RecipientsEditorManager::self()
{
    static RecipientsEditorManager s_self;
    return &s_self;
}

Akonadi::EmailAddressSelectionModel *RecipientsEditorManager::model()
{
    if (!mModel) {
        mModel = new Akonadi::EmailAddressSelectionModel(this);
    }
    return mModel;
}
