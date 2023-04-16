/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QAbstractListModel>

#include <KContacts/Address>

namespace AkonadiContactWidgets
{
class AddressModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AddressModel(QObject *parent = nullptr);
    ~AddressModel() override;

    KContacts::Address::List addresses() const;
    void setAddresses(const KContacts::Address::List &addresses);
    void addAddress(const KContacts::Address &address);
    void replaceAddress(const KContacts::Address &address, int row);
    void removeAddress(int row);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    KContacts::Address::List mAddresses;
};

}
