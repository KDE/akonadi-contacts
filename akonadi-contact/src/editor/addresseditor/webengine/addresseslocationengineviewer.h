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


#ifndef AddressesLocationEngineViewer_H
#define AddressesLocationEngineViewer_H

#include <QWebEngineView>
#include <KContacts/Address>
namespace Akonadi
{
class AddressesLocationGrantleeFormater;
class AddressesLocationEngineViewer : public QWebEngineView
{
    Q_OBJECT
public:
    explicit AddressesLocationEngineViewer(QWidget *parent = Q_NULLPTR);
    ~AddressesLocationEngineViewer();

    KContacts::Address::List addresses() const;
    void setAddresses(const KContacts::Address::List &addresses);
    void setReadOnly(bool readOnly);

public Q_SLOTS:
    void addAddress(const KContacts::Address &address);
    void replaceAddress(const KContacts::Address &address, int index);

private Q_SLOTS:
    void slotLinkClicked(const QUrl &url);

Q_SIGNALS:
    void modifyAddress(const KContacts::Address &address, int currentIndex);

private:
    void updateView();
    void editAddress(int index);
    void removeAddress(int index);
    KContacts::Address::List mAddresses;
    AddressesLocationGrantleeFormater *mAddressesLocationGrantleeFormatter;
};
}
#endif
