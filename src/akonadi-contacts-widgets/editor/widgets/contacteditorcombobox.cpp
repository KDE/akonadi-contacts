/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contacteditorcombobox.h"

using namespace Akonadi;

ContactEditorComboBox::ContactEditorComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

ContactEditorComboBox::~ContactEditorComboBox() = default;

QSize ContactEditorComboBox::minimumSizeHint() const
{
    return {150, QComboBox::minimumSizeHint().height()};
}

#include "moc_contacteditorcombobox.cpp"
