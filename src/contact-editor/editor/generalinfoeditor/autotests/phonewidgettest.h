/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
class PhoneWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit PhoneWidgetTest(QObject *parent = nullptr);
    ~PhoneWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

