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


#include "preferedlineeditwidgettest.h"
#include "../preferedlineeditwidget.h"
#include <QAction>
#include <QIcon>
#include <QTest>

PreferedLineEditWidgetTest::PreferedLineEditWidgetTest(QObject *parent)
    : QObject(parent)
{

}

PreferedLineEditWidgetTest::~PreferedLineEditWidgetTest()
{

}

void PreferedLineEditWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::PreferedLineEditWidget w;
    QAction *act = w.findChild<QAction *>(QStringLiteral("preferedaction"));
    QVERIFY(act);
    QVERIFY(!w.prefered());
}

void PreferedLineEditWidgetTest::shouldChangePreferedValue()
{
    Akonadi::PreferedLineEditWidget w;
    QAction *act = w.findChild<QAction *>(QStringLiteral("preferedaction"));
    QIcon disabled = act->icon();
    w.setPrefered(true);
    QVERIFY(w.prefered());
    QIcon enabled = act->icon();
    w.setPrefered(false);
    QVERIFY(!w.prefered());
    QCOMPARE(act->icon(), disabled);

    w.setPrefered(true);
    QCOMPARE(act->icon(), enabled);

}

QTEST_MAIN(PreferedLineEditWidgetTest)
