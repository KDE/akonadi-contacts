/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

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

MessagingWidgetTest::~MessagingWidgetTest()
{
}

void MessagingWidgetTest::shouldHaveDefaultValues()
{
    ContactEditor::MessagingWidget w;
    KLineEdit *line = w.findChild<KLineEdit *>(QStringLiteral("messaginglineedit"));
    QVERIFY(line);

    QComboBox *protocolCombo = w.findChild<QComboBox *>(QStringLiteral("protocol"));
    QVERIFY(protocolCombo);
    QVERIFY(protocolCombo->count() > 0);

    QToolButton *add = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(add);
    QToolButton *remove = w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(remove);
}

QTEST_MAIN(MessagingWidgetTest)
