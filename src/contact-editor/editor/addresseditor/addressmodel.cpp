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

#include "addressmodel.h"

using namespace ContactEditor;

AddressModel::AddressModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

AddressModel::~AddressModel() = default;

KContacts::Address::List AddressModel::addresses() const
{
    return mAddresses;
}

void AddressModel::setAddresses(const KContacts::Address::List &addresses)
{
    beginResetModel();
    mAddresses = addresses;
    endResetModel();
}

void AddressModel::addAddress(const KContacts::Address &address)
{
    if (!address.isEmpty()) {
        beginInsertRows({}, mAddresses.size(), mAddresses.size());
        mAddresses.push_back(address);
        endInsertRows();
    }
}

void AddressModel::replaceAddress(const KContacts::Address &address, int row)
{
    if (row < 0 || row >= mAddresses.size()) {
        return;
    }

    mAddresses[row] = address;
    emit dataChanged(index(row, 0), index(row, 0));
}

void AddressModel::removeAddress(int row)
{
    if (row < 0 || row >= mAddresses.size()) {
        return;
    }

    beginRemoveRows({}, row, row);
    mAddresses.remove(row);
    endRemoveRows();
}

int AddressModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return mAddresses.size();
}

QVariant AddressModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    switch (role) {
        case Qt::DisplayRole:
        {
            const auto addr = mAddresses.at(index.row());
            QString str = QLatin1String("<b>") + KContacts::Address::typeLabel(addr.type()) + QLatin1String("</b><br/>");
            if (!addr.label().isEmpty()) {
                str += addr.label().toHtmlEscaped().replace(QLatin1Char('\n'), QLatin1String("<br/>"));
            } else {
                str += addr.formattedAddress().trimmed().toHtmlEscaped().replace(QLatin1Char('\n'), QLatin1String("<br/>"));
            }
            return str;
        }
        case Qt::UserRole:
            return QVariant::fromValue(mAddresses.at(index.row()));
    }

    return {};
}
