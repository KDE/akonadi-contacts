/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonewidgettest.h"
#include "../phone/phonewidget.h"
#include "../phone/phonecomboboxtype.h"
#include <QTest>
#include <QLineEdit>
#include <QToolButton>

PhoneWidgetTest::PhoneWidgetTest(QObject *parent)
    : QObject(parent)
{
}

PhoneWidgetTest::~PhoneWidgetTest()
{
}

void PhoneWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::PhoneWidget w;
    QLineEdit *line = w.findChild<QLineEdit *>(QStringLiteral("phonenumber"));
    QVERIFY(line);
    QToolButton *addButton = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(addButton);

    ContactEditor::PhoneComboBoxType *combotype = w.findChild<ContactEditor::PhoneComboBoxType *>(QStringLiteral("phonetype"));
    QVERIFY(combotype);

    QToolButton *removeButton = w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(removeButton);
}

QTEST_MAIN(PhoneWidgetTest)
