/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mailwidgettest.h"
#include "../mail/mailwidget.h"
#include <QComboBox>
#include <QLineEdit>
#include <QTest>
#include <QToolButton>

MailWidgetTest::MailWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MailWidgetTest::~MailWidgetTest() = default;

void MailWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::MailWidget w;
    auto line = w.findChild<QLineEdit *>(QStringLiteral("mailedit"));
    QVERIFY(line);
    QVERIFY(line->text().isEmpty());
    auto addButton = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(addButton);

    auto removeButton = w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(removeButton);

    auto mailtype = w.findChild<QComboBox *>(QStringLiteral("mailtype"));
    QVERIFY(mailtype);
}

QTEST_MAIN(MailWidgetTest)

#include "moc_mailwidgettest.cpp"
