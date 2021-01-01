/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contacteditorcombobox.h"

using namespace ContactEditor;

ContactEditorComboBox::ContactEditorComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

ContactEditorComboBox::~ContactEditorComboBox()
{
}

QSize ContactEditorComboBox::minimumSizeHint() const
{
    return QSize(150, QComboBox::minimumSizeHint().height());
}
