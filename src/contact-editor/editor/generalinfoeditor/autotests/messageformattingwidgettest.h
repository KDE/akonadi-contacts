/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MESSAGEFORMATTINGWIDGETTEST_H
#define MESSAGEFORMATTINGWIDGETTEST_H

#include <QObject>

class MessageFormattingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MessageFormattingWidgetTest(QObject *parent = nullptr);
    ~MessageFormattingWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MESSAGEFORMATTINGWIDGETTEST_H
