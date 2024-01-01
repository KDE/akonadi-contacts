/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MessagingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MessagingWidgetTest(QObject *parent = nullptr);
    ~MessagingWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
