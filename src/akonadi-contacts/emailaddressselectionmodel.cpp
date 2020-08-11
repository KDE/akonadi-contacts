/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailaddressselectionmodel.h"
#include <AkonadiCore/Session>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/EntityDisplayAttribute>
#include <AkonadiCore/ChangeRecorder>
#include <Akonadi/Contact/ContactsTreeModel>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

using namespace Akonadi;

EmailAddressSelectionModel::EmailAddressSelectionModel(QObject *parent)
    : QObject(parent)
{
    Akonadi::Session *session = new Akonadi::Session("InternalEmailAddressSelectionWidgetModel", this);

    Akonadi::ItemFetchScope scope;
    scope.fetchFullPayload(true);
    scope.fetchAttribute<Akonadi::EntityDisplayAttribute>();

    Akonadi::ChangeRecorder *changeRecorder = new Akonadi::ChangeRecorder(this);
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
