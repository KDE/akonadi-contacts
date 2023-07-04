/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "customfieldsmodel.h"
#include <QWidget>
class QTreeView;
namespace KContacts
{
class Addressee;
}
class CustomFieldsModel;
namespace Akonadi
{
class CustomFieldsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomFieldsListWidget(QWidget *parent = nullptr);
    ~CustomFieldsListWidget() override;
    void storeContact(KContacts::Addressee &contact) const;
    void loadContact(const KContacts::Addressee &contact);
    void setReadOnly(bool readOnly);

    void setLocalCustomFieldDescriptions(const QVariantList &descriptions);
    Q_REQUIRED_RESULT QVariantList localCustomFieldDescriptions() const;
public Q_SLOTS:
    void slotAddNewField(const CustomField &field);

private:
    CustomField::List mLocalCustomFields;
    QTreeView *mCustomFieldList = nullptr;
    CustomFieldsModel *mModel = nullptr;
};
}
