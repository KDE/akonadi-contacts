/*
    SPDX-FileCopyrightText: 2008 Kevin Krammer <kevin.krammer@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "akonadi_serializer_contactgroup.h"

#include <Akonadi/AbstractDifferencesReporter>
#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/Item>

#include <KContacts/ContactGroup>
#include <KContacts/ContactGroupTool>
#include <KLocalizedString>

#include <qplugin.h>

using namespace Akonadi;

//// ItemSerializerPlugin interface

bool SerializerPluginContactGroup::deserialize(Item &item, const QByteArray &label, QIODevice &data, int version)
{
    Q_UNUSED(label)
    Q_UNUSED(version)

    KContacts::ContactGroup contactGroup;

    if (!KContacts::ContactGroupTool::convertFromXml(&data, contactGroup)) {
        // TODO: error reporting
        return false;
    }

    item.setPayload<KContacts::ContactGroup>(contactGroup);

    return true;
}

void SerializerPluginContactGroup::serialize(const Item &item, const QByteArray &label, QIODevice &data, int &version)
{
    Q_UNUSED(label)
    Q_UNUSED(version)

    if (!item.hasPayload<KContacts::ContactGroup>()) {
        return;
    }

    KContacts::ContactGroupTool::convertToXml(item.payload<KContacts::ContactGroup>(), &data);
}

//// DifferencesAlgorithmInterface interface

static bool compareString(const QString &left, const QString &right)
{
    if (left.isEmpty() && right.isEmpty()) {
        return true;
    } else {
        return left == right;
    }
}

static QString toString(const KContacts::Addressee &contact)
{
    return contact.fullEmail();
}

template<class T> static void compareVector(AbstractDifferencesReporter *reporter, const QString &id, const QVector<T> &left, const QVector<T> &right)
{
    for (int i = 0; i < left.count(); ++i) {
        if (!right.contains(left[i])) {
            reporter->addProperty(AbstractDifferencesReporter::AdditionalLeftMode, id, toString(left[i]), QString());
        }
    }

    for (int i = 0; i < right.count(); ++i) {
        if (!left.contains(right[i])) {
            reporter->addProperty(AbstractDifferencesReporter::AdditionalRightMode, id, QString(), toString(right[i]));
        }
    }
}

void SerializerPluginContactGroup::compare(Akonadi::AbstractDifferencesReporter *reporter, const Akonadi::Item &leftItem, const Akonadi::Item &rightItem)
{
    Q_ASSERT(reporter);
    Q_ASSERT(leftItem.hasPayload<KContacts::ContactGroup>());
    Q_ASSERT(rightItem.hasPayload<KContacts::ContactGroup>());

    reporter->setLeftPropertyValueTitle(i18n("Changed Contact Group"));
    reporter->setRightPropertyValueTitle(i18n("Conflicting Contact Group"));

    const auto leftContactGroup = leftItem.payload<KContacts::ContactGroup>();
    const auto rightContactGroup = rightItem.payload<KContacts::ContactGroup>();

    if (!compareString(leftContactGroup.name(), rightContactGroup.name())) {
        reporter->addProperty(AbstractDifferencesReporter::ConflictMode, i18n("Name"), leftContactGroup.name(), rightContactGroup.name());
    }

    // using job->exec() is ok here, not a hot path
    auto leftJob = new Akonadi::ContactGroupExpandJob(leftContactGroup);
    leftJob->exec();

    auto rightJob = new Akonadi::ContactGroupExpandJob(rightContactGroup);
    rightJob->exec();

    compareVector(reporter, i18n("Member"), leftJob->contacts(), rightJob->contacts());
}

//// GidExtractorInterface

QString SerializerPluginContactGroup::extractGid(const Item &item) const
{
    if (!item.hasPayload<KContacts::ContactGroup>()) {
        return {};
    }
    return item.payload<KContacts::ContactGroup>().id();
}
