/*
    This file is part of Akonadi Contact.

    Copyright (C) 2017 Laurent Montel <montel@kde.org>

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


#include "messageformattingwidgettest.h"
#include "../messageformattingwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QTest>

MessageFormattingWidgetTest::MessageFormattingWidgetTest(QObject *parent)
    : QObject(parent)
{

}

void MessageFormattingWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::MessageFormattingWidget w;

    QLabel *label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    QComboBox *mMailPreferFormatting = w.findChild<QComboBox *>(QStringLiteral("mMailPreferFormatting"));
    QVERIFY(mMailPreferFormatting);
    QVERIFY(mMailPreferFormatting->count() > 0);

    QCheckBox *mAllowRemoteContent = w.findChild<QCheckBox *>(QStringLiteral("mAllowRemoteContent"));
    QVERIFY(mAllowRemoteContent);
    QVERIFY(!mAllowRemoteContent->text().isEmpty());
    QVERIFY(!mAllowRemoteContent->isChecked());
}

QTEST_MAIN(MessageFormattingWidgetTest)
