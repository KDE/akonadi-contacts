/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "blogfeedwidgettest.h"
#include "editor/generalinfoeditor/blogfeedwidget.h"

#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

#include <KLineEdit>

BlogfeedWidgetTest::BlogfeedWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void BlogfeedWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::BlogfeedWidget editor;

    auto topLayout = editor.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(topLayout);
    QCOMPARE(topLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto blogFeedLabel = editor.findChild<QLabel *>(QStringLiteral("blogFeedLabel"));
    QVERIFY(blogFeedLabel);
    QVERIFY(!blogFeedLabel->text().isEmpty());

    auto mBlogFeed = editor.findChild<KLineEdit *>(QStringLiteral("blogfeed"));
    QVERIFY(mBlogFeed);
    QVERIFY(mBlogFeed->trapReturnKey());
    QVERIFY(!mBlogFeed->placeholderText().isEmpty());
}

QTEST_MAIN(BlogfeedWidgetTest)

#include "moc_blogfeedwidgettest.cpp"
