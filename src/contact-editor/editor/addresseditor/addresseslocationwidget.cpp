/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2019 Laurent Montel <laurent.montel@kdab.com>

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

#include "addresseslocationwidget.h"
#include "addresslocationwidget.h"
#include "addressdelegate.h"
#include "addressmodel.h"
#include "contacteditor_debug.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>

using namespace ContactEditor;

AddressesLocationWidget::AddressesLocationWidget(QWidget *parent)
    : QSplitter(parent)
    , mAddressModel(new AddressModel(this))
{
    mAddressLocationWidget = new AddressLocationWidget(this);
    mAddressLocationWidget->setObjectName(QStringLiteral("addresslocationwidget"));
    addWidget(mAddressLocationWidget);

    mAddressesLocationView = new QTreeView(this);
    mAddressesLocationView->setRootIsDecorated(false);
    mAddressesLocationView->setHeaderHidden(true);
    mAddressesLocationView->setModel(mAddressModel);
    mAddressesLocationView->setItemDelegate(new AddressDelegate);
    mAddressesLocationView->setContextMenuPolicy(Qt::CustomContextMenu);
    mAddressesLocationView->setObjectName(QStringLiteral("addresseslocationviewer"));
    addWidget(mAddressesLocationView);

    connect(mAddressesLocationView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](const QItemSelection &selection) {
        mAddressLocationWidget->clear();
        if (selection.size() != 1) {
            return;
        }
        const auto idx = selection.at(0).topLeft();
        if (!idx.isValid()) {
            return;
        }
        mAddressLocationWidget->slotModifyAddress(idx.data(Qt::UserRole).value<KContacts::Address>(), idx.row());
    });
    connect(mAddressLocationWidget, &AddressLocationWidget::addNewAddress, mAddressModel, &AddressModel::addAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddressCanceled, mAddressesLocationView->selectionModel(), &QItemSelectionModel::clearSelection);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddress, mAddressModel, &AddressModel::replaceAddress);
    connect(mAddressesLocationView, &QWidget::customContextMenuRequested, this, [this](QPoint pos) {
        const auto idx = mAddressesLocationView->indexAt(pos);
        if (!idx.isValid()) {
            return;
        }
        QMenu menu;
        auto action = menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove Address"));
        action->setEnabled(!mReadOnly);
        connect(action, &QAction::triggered, this, [this, idx]() {
            const auto result = KMessageBox::questionYesNo(this, i18n("Do you really want to delete this address?"));
            if (result == KMessageBox::Yes) {
                mAddressModel->removeAddress(idx.row());
            }
        });
        menu.exec(mAddressesLocationView->viewport()->mapToGlobal(pos));
    });

    setChildrenCollapsible(false);
    setSizes(QList<int>() << 400 << 300);
}

AddressesLocationWidget::~AddressesLocationWidget() = default;

void AddressesLocationWidget::loadContact(const KContacts::Addressee &contact)
{
    mAddressModel->setAddresses(contact.addresses());
}

void AddressesLocationWidget::storeContact(KContacts::Addressee &contact) const
{
    // delete all previous addresses
    const KContacts::Address::List oldAddresses = contact.addresses();
    const int numberOfOldAddresses(oldAddresses.count());
    for (int i = 0; i < numberOfOldAddresses; ++i) {
        contact.removeAddress(oldAddresses.at(i));
    }

    const KContacts::Address::List addressList = mAddressModel->addresses();
    // insert the new ones
    const int numberOfAddress(addressList.count());
    for (int i = 0; i < numberOfAddress; ++i) {
        const KContacts::Address address(addressList.at(i));
        if (!address.isEmpty()) {
            contact.insertAddress(address);
        }
    }
}

void AddressesLocationWidget::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;
    mAddressLocationWidget->setReadOnly(readOnly);
}
