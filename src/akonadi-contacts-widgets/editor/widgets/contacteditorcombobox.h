/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi_contact_widgets_private_export.h"
#include <QComboBox>
namespace Akonadi
{
class AKONADI_CONTACT_WIDGETS_TESTS_EXPORT ContactEditorComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ContactEditorComboBox(QWidget *parent = nullptr);
    ~ContactEditorComboBox() override;

protected:
    QSize minimumSizeHint() const override;
};
}
