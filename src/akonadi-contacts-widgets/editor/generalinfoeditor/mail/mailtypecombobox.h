/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "../../widgets/contacteditorcombobox.h"
#include "contacteditor_private_export.h"

namespace AkonadiContactWidgets
{
class CONTACTEDITOR_TESTS_EXPORT MailTypeCombobox : public AkonadiContactWidgets::ContactEditorComboBox
{
    Q_OBJECT
public:
    explicit MailTypeCombobox(QWidget *parent = nullptr);
    ~MailTypeCombobox() override;
};
}