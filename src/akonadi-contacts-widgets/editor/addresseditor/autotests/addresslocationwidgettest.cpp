/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresslocationwidgettest.h"
#include "../addresslocationwidget.h"
#include "../selectaddresstypecombobox.h"
#include <KLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTest>

using namespace Akonadi;

AddressLocationWidgetTest::AddressLocationWidgetTest(QObject *parent)
    : QObject(parent)
{
}

AddressLocationWidgetTest::~AddressLocationWidgetTest() = default;

void AddressLocationWidgetTest::shouldHaveDefaultValue()
{
    AddressLocationWidget w;

    auto typeAddress = w.findChild<SelectAddressTypeComboBox *>(QStringLiteral("typeaddress"));
    QVERIFY(typeAddress);

    auto streetlabel = w.findChild<QLabel *>(QStringLiteral("streetlabel"));
    QVERIFY(streetlabel);
    auto mStreetEdit = w.findChild<KLineEdit *>(QStringLiteral("streetlineedit"));
    QVERIFY(mStreetEdit);

    auto postofficeboxlabel = w.findChild<QLabel *>(QStringLiteral("postofficeboxlabel"));
    QVERIFY(postofficeboxlabel);
    auto postofficeboxlineedit = w.findChild<KLineEdit *>(QStringLiteral("postofficeboxlineedit"));
    QVERIFY(postofficeboxlineedit);

    auto localitylabel = w.findChild<QLabel *>(QStringLiteral("localitylabel"));
    QVERIFY(localitylabel);
    auto localitylineedit = w.findChild<KLineEdit *>(QStringLiteral("localitylineedit"));
    QVERIFY(localitylineedit);

    auto regionlabel = w.findChild<QLabel *>(QStringLiteral("regionlabel"));
    QVERIFY(regionlabel);
    auto regionlineedit = w.findChild<KLineEdit *>(QStringLiteral("regionlineedit"));
    QVERIFY(regionlineedit);

    auto postalcodelabel = w.findChild<QLabel *>(QStringLiteral("postalcodelabel"));
    QVERIFY(postalcodelabel);
    auto postalcodelineedit = w.findChild<KLineEdit *>(QStringLiteral("postalcodelineedit"));
    QVERIFY(postalcodelineedit);

    auto countrylabel = w.findChild<QLabel *>(QStringLiteral("countrylabel"));
    QVERIFY(countrylabel);
    auto countrycombobox = w.findChild<QComboBox *>(QStringLiteral("countrycombobox"));
    QVERIFY(countrycombobox);

    auto preferredcheckbox = w.findChild<QCheckBox *>(QStringLiteral("preferredcheckbox"));
    QVERIFY(preferredcheckbox);

    auto addbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("addbuttonaddress"));
    QVERIFY(addbuttonaddress);

    auto modifybuttonaddress = w.findChild<QPushButton *>(QStringLiteral("modifybuttonaddress"));
    QVERIFY(modifybuttonaddress);

    auto cancelbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("cancelbuttonaddress"));
    QVERIFY(cancelbuttonaddress);
}

void AddressLocationWidgetTest::shouldChangeReadOnlyStatus()
{
    AddressLocationWidget w;

    w.setReadOnly(true);
    auto typeAddress = w.findChild<SelectAddressTypeComboBox *>(QStringLiteral("typeaddress"));
    QCOMPARE(typeAddress->isEnabled(), false);
    auto mStreetEdit = w.findChild<KLineEdit *>(QStringLiteral("streetlineedit"));
    QCOMPARE(mStreetEdit->isReadOnly(), true);
    auto postofficeboxlineedit = w.findChild<KLineEdit *>(QStringLiteral("postofficeboxlineedit"));
    QCOMPARE(postofficeboxlineedit->isReadOnly(), true);
    auto localitylineedit = w.findChild<KLineEdit *>(QStringLiteral("localitylineedit"));
    QCOMPARE(localitylineedit->isReadOnly(), true);
    auto regionlineedit = w.findChild<KLineEdit *>(QStringLiteral("regionlineedit"));
    QCOMPARE(regionlineedit->isReadOnly(), true);
    auto postalcodelineedit = w.findChild<KLineEdit *>(QStringLiteral("postalcodelineedit"));
    QCOMPARE(postalcodelineedit->isReadOnly(), true);
    auto countrycombobox = w.findChild<QComboBox *>(QStringLiteral("countrycombobox"));
    QCOMPARE(countrycombobox->isEnabled(), false);
    auto preferredcheckbox = w.findChild<QCheckBox *>(QStringLiteral("preferredcheckbox"));
    QCOMPARE(preferredcheckbox->isEnabled(), false);
    auto addbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("addbuttonaddress"));
    QCOMPARE(addbuttonaddress->isEnabled(), false);
    auto modifybuttonaddress = w.findChild<QPushButton *>(QStringLiteral("modifybuttonaddress"));
    QCOMPARE(modifybuttonaddress->isEnabled(), false);
    auto cancelbuttonaddress = w.findChild<QPushButton *>(QStringLiteral("cancelbuttonaddress"));
    QCOMPARE(cancelbuttonaddress->isEnabled(), false);
}

QTEST_MAIN(AddressLocationWidgetTest)

#include "moc_addresslocationwidgettest.cpp"
