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


#include "preferredlineeditwidgettest.h"
#include "../preferredlineeditwidget.h"
#include <QAction>
#include <QIcon>
#include <QTest>

PreferredLineEditWidget::PreferredLineEditWidget(QObject *parent)
    : QObject(parent)
{

}

PreferredLineEditWidget::~PreferredLineEditWidget()
{

}

void PreferredLineEditWidget::shouldHaveDefaultValue()
{
    Akonadi::PreferredLineEditWidget w;
    QAction *act = w.findChild<QAction *>(QStringLiteral("preferredaction"));
    QVERIFY(act);
    QVERIFY(!w.preferred());
}

void PreferredLineEditWidget::shouldChangePreferredValue()
{
    Akonadi::PreferredLineEditWidget w;
    QAction *act = w.findChild<QAction *>(QStringLiteral("preferredaction"));
    QIcon disabled = act->icon();
    w.setPreferred(true);
    QVERIFY(w.preferred());
    QIcon enabled = act->icon();
    w.setPreferred(false);
    QVERIFY(!w.preferred());
    QCOMPARE(act->icon(), disabled);

    w.setPreferred(true);
    QCOMPARE(act->icon(), enabled);

}

QTEST_MAIN(PreferredLineEditWidget)
