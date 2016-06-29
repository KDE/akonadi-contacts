/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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
    Akonadi::CustomFieldEditorWidget w;
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
    Akonadi::CustomFieldEditorWidget w;
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
    Akonadi::CustomFieldEditorWidget w;
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
