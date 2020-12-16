/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSESLOCATIONWIDGET_H
#define ADDRESSESLOCATIONWIDGET_H
#include <QSplitter>
#include <KContacts/Addressee>

class QTreeView;

namespace ContactEditor {
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
    Q_REQUIRED_RESULT bool hasNoSavedData() const;
private:
    AddressLocationWidget *mAddressLocationWidget = nullptr;
    QTreeView *mAddressesLocationView = nullptr;
    AddressModel *const mAddressModel;
    bool mReadOnly = false;
};
}
#endif // ADDRESSESLOCATIONWIDGET_H
