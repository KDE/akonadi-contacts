/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldslistwidgettest.h"
#include <QTest>
CustomFielsListWidgetTest::CustomFielsListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CustomFielsListWidgetTest::~CustomFielsListWidgetTest() = default;

QTEST_MAIN(CustomFielsListWidgetTest)

#include "moc_customfieldslistwidgettest.cpp"
