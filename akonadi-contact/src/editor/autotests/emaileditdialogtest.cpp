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

#include "emaileditdialogtest.h"
#include "../emaileditwidget.h"
#include <qtest.h>
#include <QListWidget>
#include <KContacts/Email>
#include <qpushbutton.h>
EmailEditDialogTest::EmailEditDialogTest(QObject *parent)
    : QObject(parent)
{

}

EmailEditDialogTest::~EmailEditDialogTest()
{

}

void EmailEditDialogTest::shouldHaveDefaultValue()
{
    EmailEditDialog dlg;
    QListWidget *listwidget = qFindChild<QListWidget *>(&dlg, QLatin1String("emailListBox"));
    QVERIFY(listwidget);
    QCOMPARE(listwidget->count(), 0);

    QPushButton *button = qFindChild<QPushButton *>(&dlg, QLatin1String("add"));
    QVERIFY(button);
    button = qFindChild<QPushButton *>(&dlg, QLatin1String("remove"));
    QVERIFY(button);
    button = qFindChild<QPushButton *>(&dlg, QLatin1String("edit"));
    QVERIFY(button);
    button = qFindChild<QPushButton *>(&dlg, QLatin1String("standard"));
    QVERIFY(button);
}

void EmailEditDialogTest::shouldAddItems()
{
    EmailEditDialog dlg;
    QListWidget *listwidget = qFindChild<QListWidget *>(&dlg, QLatin1String("emailListBox"));
    KContacts::Email::List lst;
    lst << KContacts::Email(QLatin1String("foo"));
    lst << KContacts::Email(QLatin1String("bla"));
    lst << KContacts::Email(QLatin1String("bli"));
    dlg.setEmailList(lst);
    QCOMPARE(listwidget->count(), lst.count());
}

void EmailEditDialogTest::shouldDontAddTwiceItem()
{
    EmailEditDialog dlg;
    QListWidget *listwidget = qFindChild<QListWidget *>(&dlg, QLatin1String("emailListBox"));
    KContacts::Email::List lst;
    lst << KContacts::Email(QLatin1String("foo"));
    lst << KContacts::Email(QLatin1String("bla"));
    lst << KContacts::Email(QLatin1String("bli"));
    lst << KContacts::Email(QLatin1String("bli"));
    dlg.setEmailList(lst);
    QCOMPARE(listwidget->count(), (lst.count()-1));
}

QTEST_MAIN(EmailEditDialogTest)
