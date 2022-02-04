/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactdefaultactions.h"

#include "actions/dialphonenumberaction.h"
#include "actions/sendsmsaction.h"

#include <KContacts/Address>
#include <KContacts/Addressee>
#include <KContacts/PhoneNumber>

#include <KCountry>

#include <QDesktopServices>
#include <QUrl>
#include <QUrlQuery>

using namespace Akonadi;

class Akonadi::ContactDefaultActionsPrivate
{
};

ContactDefaultActions::ContactDefaultActions(QObject *parent)
    : QObject(parent)
    , d(nullptr)
{
}

ContactDefaultActions::~ContactDefaultActions() = default;

void ContactDefaultActions::connectToView(QObject *view)
{
    const QMetaObject *metaObject = view->metaObject();

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("urlClicked(const QUrl&)").constData()) != -1) {
        connect(view, SIGNAL(urlClicked(QUrl)), SLOT(showUrl(QUrl)));
    }

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("emailClicked(const QString&, const QString&)").constData()) != -1) {
        // clang-format off
        connect(view, SIGNAL(emailClicked(QString,QString)), this, SLOT(sendEmail(QString,QString)));
        // clang-format on
    }

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("phoneNumberClicked(const KContacts::PhoneNumber&)").constData()) != -1) {
        connect(view, SIGNAL(phoneNumberClicked(KContacts::PhoneNumber)), this, SLOT(dialPhoneNumber(KContacts::PhoneNumber)));
    }

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("smsClicked(const KContacts::PhoneNumber&)").constData()) != -1) {
        connect(view, SIGNAL(smsClicked(KContacts::PhoneNumber)), this, SLOT(sendSms(KContacts::PhoneNumber)));
    }

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("addressClicked(const KContacts::Address&)").constData()) != -1) {
        connect(view, SIGNAL(addressClicked(KContacts::Address)), this, SLOT(showAddress(KContacts::Address)));
    }
}

void ContactDefaultActions::showUrl(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

void ContactDefaultActions::sendEmail(const QString &name, const QString &address)
{
    KContacts::Addressee contact;
    contact.setNameFromString(name);

    QUrl url;
    url.setScheme(QStringLiteral("mailto"));
    url.setPath(contact.fullEmail(address));
    QDesktopServices::openUrl(url);
}

void ContactDefaultActions::dialPhoneNumber(const KContacts::PhoneNumber &number)
{
    DialPhoneNumberAction action;
    action.dialNumber(number);
}

void ContactDefaultActions::sendSms(const KContacts::PhoneNumber &number)
{
    SendSmsAction action;
    action.sendSms(number);
}

void ContactDefaultActions::showAddress(const KContacts::Address &address)
{
    // ### move geo: URI generation to KContacts::Address?
    QUrl url;
    url.setScheme(QStringLiteral("geo"));
    if (address.geo().isValid()) {
        url.setPath(QString::number(address.geo().latitude()) + QLatin1Char(',') + QString::number(address.geo().longitude()));
    } else if (!address.isEmpty()) {
        url.setPath(QStringLiteral("0,0"));
        QStringList q;
        if (!address.street().isEmpty()) {
            q.push_back(address.street());
        }
        if (!address.locality().isEmpty()) {
            q.push_back(address.postalCode().isEmpty() ? address.locality() : (address.postalCode() + QLatin1Char(' ') + address.locality()));
        }
        if (!address.region().isEmpty()) {
            q.push_back(address.region());
        }
        if (!address.country().isEmpty()) {
            const auto c = KCountry::fromName(address.country());
            q.push_back(c.alpha2());
        }
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("q"), q.join(QLatin1String(", ")));
        url.setQuery(query);
    } else {
        return;
    }

    QDesktopServices::openUrl(url);
}
