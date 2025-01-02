/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "../../widgets/contacteditorcombobox.h"
#include "akonadi_contact_widgets_private_export.h"

namespace Akonadi
{
class AKONADI_CONTACT_WIDGETS_TESTS_EXPORT MailTypeCombobox : public Akonadi::ContactEditorComboBox
{
    Q_OBJECT
public:
    explicit MailTypeCombobox(QWidget *parent = nullptr);
    ~MailTypeCombobox() override;
};
}
