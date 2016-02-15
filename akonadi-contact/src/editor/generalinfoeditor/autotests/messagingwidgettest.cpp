/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

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


#include "messagingwidgettest.h"
#include "../messaging/messagingwidget.h"
#include <KLineEdit>
#include <QComboBox>
#include <QTest>
#include <QToolButton>

MessagingWidgetTest::MessagingWidgetTest(QObject *parent)
    : QObject(parent)
{

}

MessagingWidgetTest::~MessagingWidgetTest()
{

}

void MessagingWidgetTest::shouldHaveDefaultValues()
{
    Akonadi::MessagingWidget w;
    KLineEdit *line = w.findChild<KLineEdit *>(QStringLiteral("messaginglineedit"));
    QVERIFY(line);

    QComboBox *protocolCombo = w.findChild<QComboBox *>(QStringLiteral("protocol"));
    QVERIFY(protocolCombo);
    QVERIFY(protocolCombo->count() > 0);

    QToolButton *add = w.findChild<QToolButton *>(QStringLiteral("addbutton"));
    QVERIFY(add);
    QToolButton *remove= w.findChild<QToolButton *>(QStringLiteral("removebutton"));
    QVERIFY(remove);
}

QTEST_MAIN(MessagingWidgetTest)
