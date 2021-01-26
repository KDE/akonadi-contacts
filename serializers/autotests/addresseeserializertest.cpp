/*
    SPDX-FileCopyrightText: 2013 Christian Mollekopf <mollekopf@kolabsys.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <AkonadiCore/Item>
#include <QObject>
#include <QTest>

#include "../akonadi_serializer_addressee.h"

using namespace Akonadi;

class AddresseeSerializerTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testGid()
    {
        const QString uid(QStringLiteral("uid"));
        KContacts::Addressee addressee;
        addressee.setUid(uid);
        Akonadi::Item item;
        item.setMimeType(addressee.mimeType());
        item.setPayload(addressee);
        SerializerPluginAddressee plugin;
        const QString gid = plugin.extractGid(item);
        QCOMPARE(gid, uid);
    }
};

QTEST_MAIN(AddresseeSerializerTest)

#include "addresseeserializertest.moc"
