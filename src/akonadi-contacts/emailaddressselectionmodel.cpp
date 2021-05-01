/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectionmodel.h"
#include <Akonadi/Contact/ContactsTreeModel>
#include <AkonadiCore/ChangeRecorder>
#include <AkonadiCore/EntityDisplayAttribute>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/Session>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

using namespace Akonadi;

EmailAddressSelectionModel::EmailAddressSelectionModel(QObject *parent)
    : QObject(parent)
{
    auto session = new Akonadi::Session("InternalEmailAddressSelectionWidgetModel", this);

    Akonadi::ItemFetchScope scope;
    scope.fetchFullPayload(true);
    scope.fetchAttribute<Akonadi::EntityDisplayAttribute>();

    auto changeRecorder = new Akonadi::ChangeRecorder(this);
    changeRecorder->setSession(session);
    changeRecorder->fetchCollection(true);
    changeRecorder->setItemFetchScope(scope);
    changeRecorder->setCollectionMonitored(Akonadi::Collection::root());
    changeRecorder->setMimeTypeMonitored(KContacts::Addressee::mimeType(), true);
    changeRecorder->setMimeTypeMonitored(KContacts::ContactGroup::mimeType(), true);

    mModel = new Akonadi::ContactsTreeModel(changeRecorder, this);
}

EmailAddressSelectionModel::~EmailAddressSelectionModel()
{
}

Akonadi::ContactsTreeModel *EmailAddressSelectionModel::model() const
{
    return mModel;
}
