/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ContactSelectTypeComboboxTest : public QObject
{
    Q_OBJECT
public:
    explicit ContactSelectTypeComboboxTest(QObject *parent = nullptr);
    ~ContactSelectTypeComboboxTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

