/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldeditorwidgettest.h"
#include "../customfieldeditorwidget.h"
#include <QTest>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

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
    QLineEdit *fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    QVERIFY(fieldname);
    QVERIFY(fieldname->text().isEmpty());

    QLabel *label = w.findChild<QLabel *>(QStringLiteral("labeltitle"));
    QVERIFY(label);
    QPushButton *addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    QVERIFY(addfield);
    QVERIFY(!addfield->isEnabled());

    QComboBox *combobox = w.findChild<QComboBox *>(QStringLiteral("fieldtype"));
    QVERIFY(combobox);
    QVERIFY(combobox->count() > 0);
    QCOMPARE(combobox->currentIndex(), 0);
}

void CustomFieldEditorWidgetTest::shouldEnableAddButtonWhenTextIsNotEmpty()
{
    ContactEditor::CustomFieldEditorWidget w;
    QLineEdit *fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    QVERIFY(fieldname->text().isEmpty());
    QPushButton *addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    QVERIFY(!addfield->isEnabled());

    fieldname->setText(QStringLiteral("foo"));
    QVERIFY(addfield->isEnabled());
    fieldname->clear();
    QVERIFY(!addfield->isEnabled());
}

void CustomFieldEditorWidgetTest::shouldClearEditorWhenPressAdd()
{
    ContactEditor::CustomFieldEditorWidget w;
    QLineEdit *fieldname = w.findChild<QLineEdit *>(QStringLiteral("fieldname"));
    QPushButton *addfield = w.findChild<QPushButton *>(QStringLiteral("addfield"));
    QComboBox *combobox = w.findChild<QComboBox *>(QStringLiteral("fieldtype"));
    combobox->setCurrentIndex(1);
    fieldname->setText(QStringLiteral("foo"));
    QTest::mouseClick(addfield, Qt::LeftButton);
    QVERIFY(fieldname->text().isEmpty());
    QVERIFY(!addfield->isEnabled());
    QCOMPARE(combobox->currentIndex(), 0);
}

QTEST_MAIN(CustomFieldEditorWidgetTest)
