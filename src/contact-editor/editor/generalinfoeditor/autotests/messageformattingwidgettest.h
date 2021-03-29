/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MessageFormattingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MessageFormattingWidgetTest(QObject *parent = nullptr);
    ~MessageFormattingWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

