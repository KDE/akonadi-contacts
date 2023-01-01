/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class BlogfeedWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit BlogfeedWidgetTest(QObject *parent = nullptr);
    ~BlogfeedWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
