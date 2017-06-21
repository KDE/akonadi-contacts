/*
    This file is part of Akonadi Contact.

    Copyright (C) 2017 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
