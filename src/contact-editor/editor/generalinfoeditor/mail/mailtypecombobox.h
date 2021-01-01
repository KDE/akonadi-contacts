/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MAILTYPECOMBOBOX_H
#define MAILTYPECOMBOBOX_H

#include "../../widgets/contacteditorcombobox.h"
#include "contacteditor_private_export.h"

namespace ContactEditor {
class CONTACTEDITOR_TESTS_EXPORT MailTypeCombobox : public ContactEditor::ContactEditorComboBox
{
    Q_OBJECT
public:
    explicit MailTypeCombobox(QWidget *parent = nullptr);
    ~MailTypeCombobox();
};
}

#endif // MAILTYPECOMBOBOX_H
