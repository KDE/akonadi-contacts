/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class NicknameWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit NicknameWidgetTest(QObject *parent = nullptr);
    ~NicknameWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

