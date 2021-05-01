/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldswidgettest.h"
#include "../customfieldeditorwidget.h"
#include "../customfieldslistwidget.h"
#include "../customfieldswidget.h"
#include <QTest>

CustomFieldsWidgetTest::CustomFieldsWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CustomFieldsWidgetTest::~CustomFieldsWidgetTest()
{
}

void CustomFieldsWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::CustomFieldsWidget w;
    auto customFieldEditorWidget = w.findChild<ContactEditor::CustomFieldEditorWidget *>(QStringLiteral("customfieldeditorwidget"));
    QVERIFY(customFieldEditorWidget);

    auto customFieldsListWidget = w.findChild<ContactEditor::CustomFieldsListWidget *>(QStringLiteral("customfieldslistwidget"));
    QVERIFY(customFieldsListWidget);
}

QTEST_MAIN(CustomFieldsWidgetTest)
