/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QVariantList>
#include <QWidget>

namespace KContacts
{
class Addressee;
}

namespace ContactEditor
{
class CustomFieldEditorWidget;
class CustomFieldsListWidget;
class CustomFieldsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomFieldsWidget(QWidget *parent = nullptr);
    ~CustomFieldsWidget() override;
    void storeContact(KContacts::Addressee &contact) const;
    void loadContact(const KContacts::Addressee &contact);

    void setReadOnly(bool readOnly);
    void setLocalCustomFieldDescriptions(const QVariantList &descriptions);
    Q_REQUIRED_RESULT QVariantList localCustomFieldDescriptions() const;

private:
    ContactEditor::CustomFieldEditorWidget *mCustomFieldEditorWidget = nullptr;
    ContactEditor::CustomFieldsListWidget *mCustomFieldsListWidget = nullptr;
};
}
