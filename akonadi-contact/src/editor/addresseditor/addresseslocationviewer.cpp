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

#include "addresseslocationviewer.h"
#include "addresseslocationgrantleeformater.h"
#include <KMessageBox>
#include <KLocalizedString>
#include <QUrlQuery>
#include <QWebSettings>
#include <QDebug>

AddressesLocationViewer::AddressesLocationViewer(QWidget *parent)
    : QWebView(parent),
      mAddressesLocationGrantleeFormatter(new AddressesLocationGrantleeFormater(this))
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    settings()->setAttribute(QWebSettings::JavaEnabled, false);
    settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    connect(this, &AddressesLocationViewer::linkClicked, this, &AddressesLocationViewer::slotLinkClicked);
}

AddressesLocationViewer::~AddressesLocationViewer()
{

}

void AddressesLocationViewer::setReadOnly(bool readOnly)
{
    mAddressesLocationGrantleeFormatter->setReadOnly(readOnly);
    updateView();
}

void AddressesLocationViewer::slotLinkClicked(const QUrl &url)
{
    if (url.scheme() == QLatin1String("addresslocationaction")) {
        const QString urlPath(url.path());
        if (url.hasQuery()) {
            const QUrlQuery urlQuery(url);
            const int addressId = urlQuery.queryItemValue(QStringLiteral("id")).toInt();
            if (urlPath == QStringLiteral("removeaddress")) {
                removeAddress(addressId);
            } else if (urlPath == QStringLiteral("editaddress")) {
                editAddress(addressId);
            } else {
                qDebug() << "Unknown url" << url;
            }
        }
    }
}

void AddressesLocationViewer::removeAddress(int index)
{
    if (index < 0) {
        return;
    } else if (index < mAddresses.count()) {
        const int result = KMessageBox::questionYesNo(this, i18n("Do you really want to delete this address?"));

        if (result != KMessageBox::Yes) {
            return;
        }
        mAddresses.remove(index);
        updateView();
    }
}

void AddressesLocationViewer::editAddress(int index)
{
    if (index < 0) {
        return;
    } else if (index < mAddresses.count()) {
        //TODO remove it from list ?
        modifyAddress(mAddresses.at(index), index);
    }
}

void AddressesLocationViewer::updateView()
{
    const QString html = mAddressesLocationGrantleeFormatter->formatAddresses(mAddresses);
    setHtml(html, QUrl(QStringLiteral("file://")));
}

void AddressesLocationViewer::addAddress(const KContacts::Address &address)
{
    if (!address.isEmpty()) {
        mAddresses.append(address);
        updateView();
    }
}

KContacts::Address::List AddressesLocationViewer::addresses() const
{
    return mAddresses;
}

void AddressesLocationViewer::setAddresses(const KContacts::Address::List &addresses)
{
    mAddresses = addresses;
}
