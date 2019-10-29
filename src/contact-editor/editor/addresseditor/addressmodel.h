/*
    This file is part of Contact Editor.

    Copyright (C) 2019 Volker Krause <vkrause@kde.org>

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

#ifndef CONTACTEDITOR_ADDRESSMODEL_H
#define CONTACTEDITOR_ADDRESSMODEL_H

#include <QAbstractListModel>

#include <KContacts/Address>

namespace ContactEditor {

class AddressModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AddressModel(QObject *parent = nullptr);
    ~AddressModel();

    KContacts::Address::List addresses() const;
    void setAddresses(const KContacts::Address::List &addresses);
    void addAddress(const KContacts::Address &address);
    void replaceAddress(const KContacts::Address &address, int row);
    void removeAddress(int row);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    KContacts::Address::List mAddresses;
};

}

#endif // CONTACTEDITOR_ADDRESSMODEL_H
