/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldeditorwidgettest.h"
#include "../customfieldeditorwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

CustomFieldEditorWidgetTest::CustomFieldEditorWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CustomFieldEditorWidgetTest::~CustomFieldEditorWidgetTest()
{
}

void CustomFieldEditorWidgetTest::shouldHaveDefaultValue()
{
    ContactEditor::CustomFieldEditorWidget w;
    auto fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    QVERIFY(fieldname);
    QVERIFY(fieldname->text().isEmpty());

    auto label = w.findChild<QLabel *>(QStringLiteral("labeltitle"));
    QVERIFY(label);
    auto addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    QVERIFY(addfield);
    QVERIFY(!addfield->isEnabled());

    auto combobox = w.findChild<QComboBox *>(QStringLiteral("fieldtype"));
    QVERIFY(combobox);
    QVERIFY(combobox->count() > 0);
    QCOMPARE(combobox->currentIndex(), 0);
}

void CustomFieldEditorWidgetTest::shouldEnableAddButtonWhenTextIsNotEmpty()
{
    ContactEditor::CustomFieldEditorWidget w;
    auto fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    QVERIFY(fieldname->text().isEmpty());
    auto addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    QVERIFY(!addfield->isEnabled());

    fieldname->setText(QStringLiteral("foo"));
    QVERIFY(addfield->isEnabled());
    fieldname->clear();
    QVERIFY(!addfield->isEnabled());
}

void CustomFieldEditorWidgetTest::shouldClearEditorWhenPressAdd()
{
    ContactEditor::CustomFieldEditorWidget w;
    auto fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    auto addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    auto combobox = w.findChild<QComboBox *>(QStringLiteral("fieldtype"));
    combobox->setCurrentIndex(1);
    fieldname->setText(QStringLiteral("foo"));
    QTest::mouseClick(addfield, Qt::LeftButton);
    QVERIFY(fieldname->text().isEmpty());
    QVERIFY(!addfield->isEnabled());
    QCOMPARE(combobox->currentIndex(), 0);
}

QTEST_MAIN(CustomFieldEditorWidgetTest)
