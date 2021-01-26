/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CONTACTEDITORCOMBOBOX_H
#define CONTACTEDITORCOMBOBOX_H

#include "contacteditor_private_export.h"
#include <QComboBox>
namespace ContactEditor
{
class CONTACTEDITOR_TESTS_EXPORT ContactEditorComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ContactEditorComboBox(QWidget *parent = nullptr);
    ~ContactEditorComboBox() override;

protected:
    QSize minimumSizeHint() const override;
};
}
#endif // CONTACTEDITORCOMBOBOX_H
