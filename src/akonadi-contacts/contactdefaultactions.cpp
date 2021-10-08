/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactdefaultactions.h"

#include "actions/dialphonenumberaction.h"
#include "actions/sendsmsaction.h"
#include "actions/showaddressaction.h"

#include <KContacts/Address>
#include <KContacts/Addressee>
#include <KContacts/PhoneNumber>
#include <QDesktopServices>
#include <QUrl>

using namespace Akonadi;

class Q_DECL_HIDDEN ContactDefaultActions::Private
{
};

ContactDefaultActions::ContactDefaultActions(QObject *parent)
    : QObject(parent)
    , d(nullptr)
{
}

ContactDefaultActions::~ContactDefaultActions()
{
}

void ContactDefaultActions::connectToView(QObject *view)
{
    const QMetaObject *metaObject = view->metaObject();

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("urlClicked(const QUrl&)").constData()) != -1) {
        connect(view, SIGNAL(urlClicked(QUrl)), SLOT(showUrl(QUrl)));
    }

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("emailClicked(const QString&, const QString&)").constData()) != -1) {
        connect(view, SIGNAL(emailClicked(QString, QString)), this, SLOT(sendEmail(QString, QString)));
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
    ShowAddressAction action;
    action.showAddress(address);
}
