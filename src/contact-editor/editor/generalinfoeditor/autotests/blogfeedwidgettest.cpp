/*
    This file is part of Contact Editor.

    Copyright (C) 2018 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
    ContactEditor::BlogfeedWidget editor;

    QVBoxLayout *topLayout = editor.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(topLayout);
    int top = -1;
    int bottom = -1;
    int left = -1;
    int right = -1;
    topLayout->getContentsMargins(&left, &top, &right, &bottom);
    QCOMPARE(top, 0);
    QCOMPARE(left, 0);
    QCOMPARE(bottom, 0);
    QCOMPARE(right, 0);

    QLabel *blogFeedLabel = editor.findChild<QLabel *>(QStringLiteral("blogFeedLabel"));
    QVERIFY(blogFeedLabel);
    QVERIFY(!blogFeedLabel->text().isEmpty());

    KLineEdit *mBlogFeed = editor.findChild<KLineEdit *>(QStringLiteral("blogfeed"));
    QVERIFY(mBlogFeed);
    QVERIFY(mBlogFeed->trapReturnKey());
    QVERIFY(!mBlogFeed->placeholderText().isEmpty());
}

QTEST_MAIN(BlogfeedWidgetTest)
