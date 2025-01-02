/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class PreferredLineEditWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit PreferredLineEditWidgetTest(QObject *parent = nullptr);
    ~PreferredLineEditWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangePreferredValue();
};
