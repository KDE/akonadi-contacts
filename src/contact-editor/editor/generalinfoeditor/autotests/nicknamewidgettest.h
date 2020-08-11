/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef NICKNAMEWIDGETTEST_H
#define NICKNAMEWIDGETTEST_H

#include <QObject>

class NicknameWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit NicknameWidgetTest(QObject *parent = nullptr);
    ~NicknameWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // NICKNAMEWIDGETTEST_H
