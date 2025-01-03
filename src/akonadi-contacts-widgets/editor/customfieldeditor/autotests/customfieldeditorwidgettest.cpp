/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldeditorwidgettest.h"
#include "../customfieldeditorwidget.h"
#include <KLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTest>

CustomFieldEditorWidgetTest::CustomFieldEditorWidgetTest(QObject *parent)
    : QObject(parent)
{
}

CustomFieldEditorWidgetTest::~CustomFieldEditorWidgetTest() = default;

void CustomFieldEditorWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::CustomFieldEditorWidget w;
    auto fieldname = w.findChild<KLineEdit *>(QStringLiteral("fieldname"));
    QVERIFY(fieldname);
    QVERIFY(fieldname->text().isEmpty());
    QVERIFY(fieldname->trapReturnKey());

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
    Akonadi::CustomFieldEditorWidget w;
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
    Akonadi::CustomFieldEditorWidget w;
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

#include "moc_customfieldeditorwidgettest.cpp"
