/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messagingwidgettest.h"
#include "../messaging/messagingwidget.h"
#include <KLineEdit>
#include <QComboBox>
#include <QTest>
#include <QToolButton>

MessagingWidgetTest::MessagingWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MessagingWidgetTest::~MessagingWidgetTest() = default;

void MessagingWidgetTest::shouldHaveDefaultValues()
{
    Akonadi::MessagingWidget w;
    auto line = w.findChild<KLineEdit *>(QStringLiteral("messaginglineedit"));
    QVERIFY(line);

    auto protocolCombo = w.findChild<QComboBox *>(QStringLiteral("protocol"));
    QVERIFY(protocolCombo);
    QVERIFY(protocolCombo->count() > 0);

    auto add = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(add);
    auto remove = w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(remove);
}

QTEST_MAIN(MessagingWidgetTest)

#include "moc_messagingwidgettest.cpp"
