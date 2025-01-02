/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseslocationwidget.h"
#include "addressdelegate.h"
#include "addresslocationwidget.h"
#include "addressmodel.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <QMenu>
#include <QTreeView>

using namespace Akonadi;

AddressesLocationWidget::AddressesLocationWidget(QWidget *parent)
    : QSplitter(parent)
    , mAddressLocationWidget(new AddressLocationWidget(this))
    , mAddressesLocationView(new QTreeView(this))
    , mAddressModel(new AddressModel(this))
{
    mAddressLocationWidget->setObjectName(QLatin1StringView("addresslocationwidget"));
    addWidget(mAddressLocationWidget);

    mAddressesLocationView->setRootIsDecorated(false);
    mAddressesLocationView->setHeaderHidden(true);
    mAddressesLocationView->setModel(mAddressModel);
    mAddressesLocationView->setItemDelegate(new AddressDelegate(this));
    mAddressesLocationView->setContextMenuPolicy(Qt::CustomContextMenu);
    mAddressesLocationView->setObjectName(QLatin1StringView("addresseslocationviewer"));
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
    connect(mAddressLocationWidget, &AddressLocationWidget::removeAddress, mAddressModel, &AddressModel::removeAddress);
    connect(mAddressLocationWidget,
            &AddressLocationWidget::updateAddressCanceled,
            mAddressesLocationView->selectionModel(),
            &QItemSelectionModel::clearSelection);
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
            const auto result = KMessageBox::questionTwoActions(this,
                                                                i18n("Do you really want to delete this address?"),
                                                                QString(),
                                                                KStandardGuiItem::del(),
                                                                KStandardGuiItem::cancel());
            if (result == KMessageBox::ButtonCode::PrimaryAction) {
                mAddressModel->removeAddress(idx.row());
            }
        });
        menu.exec(mAddressesLocationView->viewport()->mapToGlobal(pos));
    });

    setChildrenCollapsible(false);
    setSizes({400, 300});
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

bool AddressesLocationWidget::hasNoSavedData() const
{
    return mAddressLocationWidget->wasChanged();
}

#include "moc_addresseslocationwidget.cpp"
