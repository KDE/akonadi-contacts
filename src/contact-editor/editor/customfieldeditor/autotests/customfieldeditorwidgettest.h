/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CustomFieldEditorWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomFieldEditorWidgetTest(QObject *parent = nullptr);
    ~CustomFieldEditorWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEnableAddButtonWhenTextIsNotEmpty();
    void shouldClearEditorWhenPressAdd();
};

