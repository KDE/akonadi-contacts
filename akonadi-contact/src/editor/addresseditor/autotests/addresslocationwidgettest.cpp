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


#include "addresslocationwidgettest.h"
#include "../addresslocationwidget.h"
#include <QLabel>
#include <QPushButton>
#include <KComboBox>
#include <KLineEdit>
#include <QTest>
#include <QCheckBox>

AddressLocationWidgetTest::AddressLocationWidgetTest(QObject *parent)
    : QObject(parent)
{

}

AddressLocationWidgetTest::~AddressLocationWidgetTest()
{

}

void AddressLocationWidgetTest::shouldHaveDefaultValue()
{
    AddressLocationWidget w;

    QLabel *streetlabel = w.findChild<QLabel *>(QStringLiteral("streetlabel"));
    QVERIFY(streetlabel);
    KLineEdit *mStreetEdit = w.findChild<KLineEdit *>(QStringLiteral("streetlineedit"));
    QVERIFY(mStreetEdit);


    QLabel *postofficeboxlabel = w.findChild<QLabel *>(QStringLiteral("postofficeboxlabel"));
    QVERIFY(postofficeboxlabel);
    KLineEdit *postofficeboxlineedit = w.findChild<KLineEdit *>(QStringLiteral("postofficeboxlineedit"));
    QVERIFY(postofficeboxlineedit);

    QLabel *localitylabel = w.findChild<QLabel *>(QStringLiteral("localitylabel"));
    QVERIFY(localitylabel);
    KLineEdit *localitylineedit = w.findChild<KLineEdit *>(QStringLiteral("localitylineedit"));
    QVERIFY(localitylineedit);

    QLabel *regionlabel = w.findChild<QLabel *>(QStringLiteral("regionlabel"));
    QVERIFY(regionlabel);
    KLineEdit *regionlineedit = w.findChild<KLineEdit *>(QStringLiteral("regionlineedit"));
    QVERIFY(regionlineedit);

    QLabel *postalcodelabel = w.findChild<QLabel *>(QStringLiteral("postalcodelabel"));
    QVERIFY(postalcodelabel);
    KLineEdit *postalcodelineedit = w.findChild<KLineEdit *>(QStringLiteral("postalcodelineedit"));
    QVERIFY(postalcodelineedit);

    QLabel *countrylabel = w.findChild<QLabel *>(QStringLiteral("countrylabel"));
    QVERIFY(countrylabel);
    KComboBox *countrycombobox = w.findChild<KComboBox *>(QStringLiteral("countrylabel"));
    QVERIFY(countrycombobox);

    QCheckBox *preferredcheckbox = w.findChild<QCheckBox *>(QStringLiteral("preferredcheckbox"));
    QVERIFY(preferredcheckbox);

    QPushButton *addbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("addbuttonaddress"));
    QVERIFY(addbuttonaddress);
}

QTEST_MAIN(AddressLocationWidgetTest)
