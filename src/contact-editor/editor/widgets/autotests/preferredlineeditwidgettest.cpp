/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "preferredlineeditwidgettest.h"
#include "../preferredlineeditwidget.h"
#include <QAction>
#include <QIcon>
#include <QTest>

PreferredLineEditWidgetTest::PreferredLineEditWidgetTest(QObject *parent)
    : QObject(parent)
{
}

PreferredLineEditWidgetTest::~PreferredLineEditWidgetTest()
{
}

void PreferredLineEditWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::PreferredLineEditWidget w;
    auto act = w.findChild<QAction *>(QStringLiteral("preferredaction"));
    QVERIFY(act);
    QVERIFY(!w.preferred());
}

void PreferredLineEditWidgetTest::shouldChangePreferredValue()
{
    ContactEditor::PreferredLineEditWidget w;
    auto act = w.findChild<QAction *>(QStringLiteral("preferredaction"));
    QIcon disabled = act->icon();
    w.setPreferred(true);
    QVERIFY(w.preferred());
    QIcon enabled = act->icon();
    w.setPreferred(false);
    QVERIFY(!w.preferred());
    QCOMPARE(act->icon(), disabled);

    w.setPreferred(true);
    QCOMPARE(act->icon(), enabled);
}

QTEST_MAIN(PreferredLineEditWidgetTest)
