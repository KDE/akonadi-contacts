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
#include "addresseslocationviewer.h"
#include "addresslocationwidget.h"
#include <QHBoxLayout>


AddressesLocationWidget::AddressesLocationWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setMargin(0);
    AddressLocationWidget *addressLocationWidget = new AddressLocationWidget(this);
    addressLocationWidget->setObjectName(QStringLiteral("addresslocationwidget"));
    topLayout->addWidget(addressLocationWidget);

    mAddressesLocationViewer = new AddressesLocationViewer(this);
    mAddressesLocationViewer->setObjectName(QStringLiteral("addresseslocationviewer"));
    topLayout->addWidget(mAddressesLocationViewer);
    connect(mAddressesLocationViewer, &AddressesLocationViewer::modifyAddress, addressLocationWidget, &AddressLocationWidget::slotModifyAddress);
    connect(addressLocationWidget, &AddressLocationWidget::addNewAddress, mAddressesLocationViewer, &AddressesLocationViewer::addAddress);

    setLayout(topLayout);
}

AddressesLocationWidget::~AddressesLocationWidget()
{

}

KContacts::Address::List AddressesLocationWidget::addresses() const
{
    return mAddressesLocationViewer->addresses();
}

void AddressesLocationWidget::setAddresses(const KContacts::Address::List &addresses)
{
    mAddressesLocationViewer->setAddresses(addresses);
}
