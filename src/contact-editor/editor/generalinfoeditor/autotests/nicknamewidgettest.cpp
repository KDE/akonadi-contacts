/*
    This file is part of Contact Editor.

    Copyright (C) 2017-2019 Laurent Montel <montel@kde.org>

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

#include "nicknamewidgettest.h"
#include "editor/generalinfoeditor/nicknamewidget.h"

#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

#include <KLineEdit>

NicknameWidgetTest::NicknameWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void NicknameWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::NicknameWidget editor;

    QVBoxLayout *topLayout = editor.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(topLayout);
    QCOMPARE(topLayout->margin(), 0);

    QLabel *nickNameLabel = editor.findChild<QLabel *>(QStringLiteral("nicknamelabel"));
    QVERIFY(nickNameLabel);
    QVERIFY(!nickNameLabel->text().isEmpty());

    KLineEdit *mNickName = editor.findChild<KLineEdit *>(QStringLiteral("nickname"));
    QVERIFY(mNickName);
    QVERIFY(mNickName->trapReturnKey());
    QVERIFY(!mNickName->placeholderText().isEmpty());
}

QTEST_MAIN(NicknameWidgetTest)
