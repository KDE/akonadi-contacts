/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonewidgettest.h"
#include "../phone/phonecomboboxtype.h"
#include "../phone/phonewidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>

PhoneWidgetTest::PhoneWidgetTest(QObject *parent)
    : QObject(parent)
{
}

PhoneWidgetTest::~PhoneWidgetTest() = default;

void PhoneWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::PhoneWidget w;
    auto line = w.findChild<QLineEdit *>(QStringLiteral("phonenumber"));
    QVERIFY(line);
    auto addButton = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(addButton);

    auto combotype = w.findChild<Akonadi::PhoneComboBoxType *>(QStringLiteral("phonetype"));
    QVERIFY(combotype);

    auto removeButton = w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(removeButton);
}

QTEST_MAIN(PhoneWidgetTest)

#include "moc_phonewidgettest.cpp"
