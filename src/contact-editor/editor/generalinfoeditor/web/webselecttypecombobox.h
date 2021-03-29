/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "../../widgets/contacteditorcombobox.h"
#include "contacteditor_private_export.h"

namespace ContactEditor
{
class CONTACTEDITOR_TESTS_EXPORT WebSelectTypeCombobox : public ContactEditor::ContactEditorComboBox
{
    Q_OBJECT
public:
    explicit WebSelectTypeCombobox(QWidget *parent = nullptr);
    ~WebSelectTypeCombobox() override;
};
}

