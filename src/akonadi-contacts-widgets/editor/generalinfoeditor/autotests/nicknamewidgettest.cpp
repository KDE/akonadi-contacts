/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "nicknamewidgettest.h"
#include "editor/generalinfoeditor/nicknamewidget.h"

#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

#include <QLineEdit>

NicknameWidgetTest::NicknameWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void NicknameWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::NicknameWidget editor;

    auto topLayout = editor.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(topLayout);
    QCOMPARE(topLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto nickNameLabel = editor.findChild<QLabel *>(QStringLiteral("nicknamelabel"));
    QVERIFY(nickNameLabel);
    QVERIFY(!nickNameLabel->text().isEmpty());

    auto mNickName = editor.findChild<QLineEdit *>(QStringLiteral("nickname"));
    QVERIFY(mNickName);
    QVERIFY(!mNickName->placeholderText().isEmpty());
}

QTEST_MAIN(NicknameWidgetTest)

#include "moc_nicknamewidgettest.cpp"
