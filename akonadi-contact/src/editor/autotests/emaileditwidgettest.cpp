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
#include <KContacts/Addressee>
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
    QLineEdit *lineedit = widget.findChild<QLineEdit *>(QLatin1String("emailedit"));
    QVERIFY(lineedit);
    QVERIFY(lineedit->text().isEmpty());

    QToolButton *toolButton = widget.findChild<QToolButton *>(QLatin1String("editbutton"));
    QVERIFY(toolButton);
}

void EmailEditWidgetTest::shouldReadOnly()
{
    EmailEditWidget widget;
    widget.setReadOnly(true);
    QLineEdit *lineedit = widget.findChild<QLineEdit *>(QLatin1String("emailedit"));

    QToolButton *toolButton = widget.findChild<QToolButton *>(QLatin1String("editbutton"));
    QVERIFY(lineedit->isReadOnly());
    QVERIFY(!toolButton->isEnabled());
}

void EmailEditWidgetTest::shouldSelectFirstEmail()
{
    EmailEditWidget widget;
    QLineEdit *lineedit = widget.findChild<QLineEdit *>(QLatin1String("emailedit"));
    KContacts::Addressee addr;
    KContacts::Email::List lst;
    const QString firstEmail(QLatin1String("foo@kde.org"));
    lst << KContacts::Email(firstEmail);
    lst << KContacts::Email(QLatin1String("foo2@kde.org"));
    addr.setEmailList(lst);
    widget.loadContact(addr);
    QCOMPARE(lineedit->text(), firstEmail);
}

void EmailEditWidgetTest::shouldChangeEmail()
{
    EmailEditWidget widget;
    QLineEdit *lineedit = widget.findChild<QLineEdit *>(QLatin1String("emailedit"));
    KContacts::Addressee addr;
    KContacts::Email::List lst;
    const QString firstEmail(QLatin1String("foo@kde.org"));
    lst << KContacts::Email(firstEmail);
    lst << KContacts::Email(QLatin1String("foo2@kde.org"));
    addr.setEmailList(lst);
    widget.loadContact(addr);
    const QString changedEmail(QLatin1String("foo3@kde.org"));
    lineedit->setText(changedEmail);
    KContacts::Addressee result;
    widget.storeContact(result);
    QVERIFY(!result.emailList().isEmpty());
    QCOMPARE(result.emailList().first().mail(), changedEmail);
}

QTEST_MAIN(EmailEditWidgetTest)
