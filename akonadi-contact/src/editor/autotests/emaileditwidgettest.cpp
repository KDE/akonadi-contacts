/*
    Copyright (c) 2015 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/


#include "emaileditwidgettest.h"
#include "../emaileditwidget.h"
#include <QLineEdit>
#include <QToolButton>
#include <qtest.h>
EmailEditWidgetTest::EmailEditWidgetTest(QObject *parent)
    : QObject(parent)
{

}

EmailEditWidgetTest::~EmailEditWidgetTest()
{

}

void EmailEditWidgetTest::shouldHaveDefaultValue()
{
    EmailEditWidget widget;
    QLineEdit *lineedit = qFindChild<QLineEdit *>(&widget, QLatin1String("emailedit"));
    QVERIFY(lineedit);
    QVERIFY(lineedit->text().isEmpty());

    QToolButton *toolButton = qFindChild<QToolButton *>(&widget, QLatin1String("editbutton"));
    QVERIFY(toolButton);
}

void EmailEditWidgetTest::shouldReadOnly()
{
    EmailEditWidget widget;
    widget.setReadOnly(true);
    QLineEdit *lineedit = qFindChild<QLineEdit *>(&widget, QLatin1String("emailedit"));

    QToolButton *toolButton = qFindChild<QToolButton *>(&widget, QLatin1String("editbutton"));
    QVERIFY(lineedit->isReadOnly());
    QVERIFY(!toolButton->isEnabled());
}

QTEST_MAIN(EmailEditWidgetTest)
