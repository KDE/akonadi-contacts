/*
    SPDX-FileCopyrightText: 2007 Till Adam <adam@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef __AKONADI_SERIALIZER_ADDRESSEE_H__
#define __AKONADI_SERIALIZER_ADDRESSEE_H__

#include <QObject>

#include <AkonadiCore/differencesalgorithminterface.h>
#include <AkonadiCore/gidextractorinterface.h>
#include <AkonadiCore/itemserializerplugin.h>
#include <kcontacts/vcardconverter.h>

namespace Akonadi
{
class SerializerPluginAddressee : public QObject, public ItemSerializerPlugin, public DifferencesAlgorithmInterface, public GidExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(Akonadi::ItemSerializerPlugin)
    Q_INTERFACES(Akonadi::DifferencesAlgorithmInterface)
    Q_INTERFACES(Akonadi::GidExtractorInterface)
    Q_PLUGIN_METADATA(IID "org.kde.akonadi.SerializerPluginAddressee")
public:
    bool deserialize(Item &item, const QByteArray &label, QIODevice &data, int version) override;
    void serialize(const Item &item, const QByteArray &label, QIODevice &data, int &version) override;

    void compare(Akonadi::AbstractDifferencesReporter *reporter, const Akonadi::Item &leftItem, const Akonadi::Item &rightItem) override;

    QString extractGid(const Item &item) const override;

private:
    KContacts::VCardConverter m_converter;
};
}

#endif
