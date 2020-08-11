/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactmetadataattributetest.h"

#include "attributes/contactmetadataattribute_p.h"

#include <QTest>

QTEST_MAIN(ContactMetaDataAttributeTest)

static QVariantMap testData()
{
    QVariantMap data;
    data.insert(QStringLiteral("key1"), QStringLiteral("value1"));
    data.insert(QStringLiteral("key2"), QStringLiteral("value2"));

    return data;
}

void ContactMetaDataAttributeTest::type()
{
    Akonadi::ContactMetaDataAttribute attribute;

    QVERIFY(attribute.type() == "contactmetadata");
}

void ContactMetaDataAttributeTest::clone()
{
    const QVariantMap content1 = testData();

    Akonadi::ContactMetaDataAttribute attribute1;
    attribute1.setMetaData(content1);

    Akonadi::ContactMetaDataAttribute *attribute2 = static_cast<Akonadi::ContactMetaDataAttribute *>(attribute1.clone());
    const QVariantMap content2 = attribute2->metaData();

    QVERIFY(content1 == content2);
}

void ContactMetaDataAttributeTest::serialization()
{
    const QVariantMap content1 = testData();

    Akonadi::ContactMetaDataAttribute attribute1;
    attribute1.setMetaData(content1);

    const QByteArray data = attribute1.serialized();

    Akonadi::ContactMetaDataAttribute attribute2;
    attribute2.deserialize(data);

    const QVariantMap content2 = attribute2.metaData();

    QVERIFY(content1 == content2);
}
