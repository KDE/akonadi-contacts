/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "customfields_p.h"
#include <QWidget>
class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
namespace ContactEditor
{
class CustomFieldEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomFieldEditorWidget(QWidget *parent = nullptr);
    ~CustomFieldEditorWidget();
    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void addNewField(const CustomField &field);

private:
    void slotAddField();
    void slotFielNameChanged(const QString &text);
    void fillTypes();
    QLineEdit *mFieldName = nullptr;
    QPushButton *mAddField = nullptr;
    QCheckBox *mUseAllContacts = nullptr;
    QComboBox *mFieldType = nullptr;
};
}
