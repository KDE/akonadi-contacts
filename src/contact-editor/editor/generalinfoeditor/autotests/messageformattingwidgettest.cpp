/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messageformattingwidgettest.h"
#include "../messageformattingwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QTest>

MessageFormattingWidgetTest::MessageFormattingWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MessageFormattingWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::MessageFormattingWidget w;

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mMailPreferFormatting = w.findChild<QComboBox *>(QStringLiteral("mMailPreferFormatting"));
    QVERIFY(mMailPreferFormatting);
    QVERIFY(mMailPreferFormatting->count() > 0);

    auto mAllowRemoteContent = w.findChild<QCheckBox *>(QStringLiteral("mAllowRemoteContent"));
    QVERIFY(mAllowRemoteContent);
    QVERIFY(!mAllowRemoteContent->text().isEmpty());
    QVERIFY(!mAllowRemoteContent->isChecked());
}

QTEST_MAIN(MessageFormattingWidgetTest)

#include "moc_messageformattingwidgettest.cpp"
