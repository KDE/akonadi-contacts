/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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
namespace Akonadi
{
class CustomFieldsModel;
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
    [[nodiscard]] QVariantList localCustomFieldDescriptions() const;
public Q_SLOTS:
    void slotAddNewField(const CustomField &field);

private:
    CustomField::List mLocalCustomFields;
    QTreeView *mCustomFieldList = nullptr;
    CustomFieldsModel *mModel = nullptr;
};
}
