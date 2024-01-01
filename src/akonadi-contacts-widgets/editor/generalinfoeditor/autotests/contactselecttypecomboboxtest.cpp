/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactselecttypecomboboxtest.h"
#include "../mail/mailtypecombobox.h"
#include <QTest>

ContactSelectTypeComboboxTest::ContactSelectTypeComboboxTest(QObject *parent)
    : QObject(parent)
{
}

ContactSelectTypeComboboxTest::~ContactSelectTypeComboboxTest() = default;

void ContactSelectTypeComboboxTest::shouldHaveDefaultValue()
{
    Akonadi::MailTypeCombobox w;
    QCOMPARE(w.count(), 4);
}

QTEST_MAIN(ContactSelectTypeComboboxTest)

#include "moc_contactselecttypecomboboxtest.cpp"
