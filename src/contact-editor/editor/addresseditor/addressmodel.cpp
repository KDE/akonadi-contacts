/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
    Q_EMIT dataChanged(index(row, 0), index(row, 0));
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
    case Qt::DisplayRole: {
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
