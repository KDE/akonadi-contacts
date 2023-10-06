/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <KContacts/Addressee>
#include <QSplitter>

class QTreeView;

namespace Akonadi
{
class AddressModel;
class AddressLocationWidget;

class AddressesLocationWidget : public QSplitter
{
    Q_OBJECT
public:
    explicit AddressesLocationWidget(QWidget *parent = nullptr);
    ~AddressesLocationWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);
    [[nodiscard]] bool hasNoSavedData() const;

private:
    AddressLocationWidget *const mAddressLocationWidget;
    QTreeView *const mAddressesLocationView;
    AddressModel *const mAddressModel;
    bool mReadOnly = false;
};
}
