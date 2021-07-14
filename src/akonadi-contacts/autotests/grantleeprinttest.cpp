/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeprinttest.h"
#include "grantlee/grantleeprint.h"
#include <QTest>

GrantleePrintTest::GrantleePrintTest(QObject *parent)
    : QObject(parent)
{
}

GrantleePrintTest::~GrantleePrintTest()
{
}

void GrantleePrintTest::shouldReturnEmptyStringWhenNotContentAndNoContacts()
{
    KAddressBookGrantlee::GrantleePrint grantleePrint;
    KContacts::Addressee::List lst;
    QVERIFY(grantleePrint.contactsToHtml(lst).isEmpty());
}

void GrantleePrintTest::shouldReturnEmptyStringWhenAddContentWithoutContacts()
{
    KAddressBookGrantlee::GrantleePrint grantleePrint;
    grantleePrint.setTemplateContent(QStringLiteral("foo"));
    KContacts::Addressee::List lst;
    QVERIFY(grantleePrint.contactsToHtml(lst).isEmpty());
}

void GrantleePrintTest::shouldReturnStringWhenAddContentAndContacts()
{
    KAddressBookGrantlee::GrantleePrint grantleePrint;
    grantleePrint.setTemplateContent(QStringLiteral("foo"));
    KContacts::Addressee::List lst;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    address.insertEmail(QStringLiteral("foo@kde.org"), true);
    lst << address;

    QCOMPARE(grantleePrint.contactsToHtml(lst), QStringLiteral("foo"));
}

void GrantleePrintTest::shouldReturnEmails()
{
    KAddressBookGrantlee::GrantleePrint grantleePrint;
    KContacts::Addressee::List lst;
    KContacts::Addressee address;
    address.setName(QStringLiteral("foo1"));
    address.insertEmail(QStringLiteral("foo@kde.org"), true);
    lst << address;
    grantleePrint.setTemplateContent(
        QStringLiteral("{% if contacts %}{% for contact in contacts %}{% if contact.name %}{{ contact.name }}{% endif %}{% endfor %}{% endif %}"));

    QCOMPARE(grantleePrint.contactsToHtml(lst), QStringLiteral("foo1"));
}

void GrantleePrintTest::shouldDisplayContactInfo_data()
{
    QTest::addColumn<QString>("variable");
    QTest::addColumn<QString>("result");
    QTest::newRow("name") << QStringLiteral("name") << QStringLiteral("foo1");
    QTest::newRow("organization") << QStringLiteral("organization") << QStringLiteral("kde");
    QTest::newRow("note") << QStringLiteral("note") << QStringLiteral("foo-note");
    QTest::newRow("title") << QStringLiteral("title") << QStringLiteral("foo-title");
    QTest::newRow("nickName") << QStringLiteral("nickName") << QStringLiteral("foo-nickname");
    QTest::newRow("familyName") << QStringLiteral("familyName") << QStringLiteral("foo-familyname");
    QTest::newRow("role") << QStringLiteral("role") << QStringLiteral("foo-role");
    QTest::newRow("suffix") << QStringLiteral("suffix") << QStringLiteral("foo-suffix");
    QTest::newRow("prefix") << QStringLiteral("prefix") << QStringLiteral("foo-prefix");
    QTest::newRow("department") << QStringLiteral("department") << QStringLiteral("foo-department");
    QTest::newRow("office") << QStringLiteral("office") << QStringLiteral("foo-office");
    QTest::newRow("profession") << QStringLiteral("profession") << QStringLiteral("foo-profession");
    QTest::newRow("manager") << QStringLiteral("managersName") << QStringLiteral("foo-managersname");
    QTest::newRow("assistant") << QStringLiteral("assistantsName") << QStringLiteral("foo-assistantsname");
    QTest::newRow("spouse") << QStringLiteral("spousesName") << QStringLiteral("foo-spousesname");
    QTest::newRow("givenname") << QStringLiteral("givenName") << QStringLiteral("foo-givenname");
    QTest::newRow("additionalname") << QStringLiteral("additionalName") << QStringLiteral("foo-additionalname");
}

void GrantleePrintTest::shouldDisplayContactInfo()
{
    QFETCH(QString, variable);
    QFETCH(QString, result);

    KAddressBookGrantlee::GrantleePrint grantleePrint;
    KContacts::Addressee::List lst;
    KContacts::Addressee address;
    address.setGivenName(QStringLiteral("foo-givenname"));
    address.setAdditionalName(QStringLiteral("foo-additionalname"));
    address.setName(QStringLiteral("foo1"));
    address.insertEmail(QStringLiteral("foo@kde.org"), true);
    address.setOrganization(QStringLiteral("kde"));
    address.insertLang(KContacts::Lang(QStringLiteral("fr")));
    address.setNote(QStringLiteral("foo-note"));
    address.setTitle(QStringLiteral("foo-title"));
    address.setNickName(QStringLiteral("foo-nickname"));
    address.setFamilyName(QStringLiteral("foo-familyname"));
    address.setRole(QStringLiteral("foo-role"));
    address.setSuffix(QStringLiteral("foo-suffix"));
    address.setPrefix(QStringLiteral("foo-prefix"));
    address.setDepartment(QStringLiteral("foo-department"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Office"), QStringLiteral("foo-office"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"), QStringLiteral("foo-profession"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Office"), QStringLiteral("foo-office"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-ManagersName"), QStringLiteral("foo-managersname"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-AssistantsName"), QStringLiteral("foo-assistantsname"));
    address.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-SpousesName"), QStringLiteral("foo-spousesname"));

    lst << address;
    grantleePrint.setTemplateContent(
        QStringLiteral("{% if contacts %}{% for contact in contacts %}{% if contact.%1 %}{{ contact.%1 }}{% endif %}{% endfor %}{% endif %}").arg(variable));

    QCOMPARE(grantleePrint.contactsToHtml(lst), result);
}

QTEST_MAIN(GrantleePrintTest)
