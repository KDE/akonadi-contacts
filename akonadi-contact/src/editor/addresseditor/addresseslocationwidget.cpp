/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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
#ifdef QTWEBENGINE_SUPPORT_OPTION
#include "webengine/addresseslocationengineviewer.h"
#else
#include "webkit/addresseslocationviewer.h"
#endif
#include "addresslocationwidget.h"
using namespace Akonadi;

AddressesLocationWidget::AddressesLocationWidget(QWidget *parent)
    : QSplitter(parent)
{
    setChildrenCollapsible(false);
    mAddressLocationWidget = new AddressLocationWidget(this);
    addWidget(mAddressLocationWidget);
    mAddressLocationWidget->setObjectName(QStringLiteral("addresslocationwidget"));
#ifdef QTWEBENGINE_SUPPORT_OPTION
    mAddressesLocationViewer = new AddressesLocationEngineViewer(this);
    mAddressesLocationViewer->setObjectName(QStringLiteral("addresseslocationviewer"));
    addWidget(mAddressesLocationViewer);
    connect(mAddressesLocationViewer, &AddressesLocationEngineViewer::modifyAddress, mAddressLocationWidget, &AddressLocationWidget::slotModifyAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::addNewAddress, mAddressesLocationViewer, &AddressesLocationEngineViewer::addAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddressCanceled, mAddressesLocationViewer, &AddressesLocationEngineViewer::updateAddressCanceled);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddress, mAddressesLocationViewer, &AddressesLocationEngineViewer::replaceAddress);
#else
    mAddressesLocationViewer = new AddressesLocationViewer(this);
    mAddressesLocationViewer->setObjectName(QStringLiteral("addresseslocationviewer"));
    addWidget(mAddressesLocationViewer);
    connect(mAddressesLocationViewer, &AddressesLocationViewer::modifyAddress, mAddressLocationWidget, &AddressLocationWidget::slotModifyAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::addNewAddress, mAddressesLocationViewer, &AddressesLocationViewer::addAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddress, mAddressesLocationViewer, &AddressesLocationViewer::replaceAddress);
    connect(mAddressLocationWidget, &AddressLocationWidget::updateAddressCanceled, mAddressesLocationViewer, &AddressesLocationViewer::updateAddressCanceled);
#endif
    setSizes(QList<int>() << 400 << 300);
}

AddressesLocationWidget::~AddressesLocationWidget()
{

}

void AddressesLocationWidget::loadContact(const KContacts::Addressee &contact)
{
    mAddressesLocationViewer->setAddresses(contact.addresses());
}

void AddressesLocationWidget::storeContact(KContacts::Addressee &contact) const
{
    // delete all previous addresses
    const KContacts::Address::List oldAddresses = contact.addresses();
    for (int i = 0; i < oldAddresses.count(); ++i) {
        contact.removeAddress(oldAddresses.at(i));
    }

    const KContacts::Address::List addressList = mAddressesLocationViewer->addresses();
    // insert the new ones
    for (int i = 0; i < addressList.count(); ++i) {
        const KContacts::Address address(addressList.at(i));
        if (!address.isEmpty()) {
            contact.insertAddress(address);
        }
    }
}

void AddressesLocationWidget::setReadOnly(bool readOnly)
{
    mAddressesLocationViewer->setReadOnly(readOnly);
    mAddressLocationWidget->setReadOnly(readOnly);
}
