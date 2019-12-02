/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#include "showaddressaction.h"

#include "contactactionssettings.h"

#include <kcontacts/address.h>
#include <KRun>

#include <QDesktopServices>

using namespace Akonadi;

static void replaceArguments(QString &templateStr, const KContacts::Address &address)
{
    templateStr.replace(QLatin1String("%s"), address.street()).
    replace(QLatin1String("%r"), address.region()).
    replace(QLatin1String("%l"), address.locality()).
    replace(QLatin1String("%z"), address.postalCode()).
    replace(QLatin1String("%n"), address.country()).
    replace(QLatin1String("%c"), address.countryToISO(address.country()));
}

void ShowAddressAction::showAddress(const KContacts::Address &address)
{
    // synchronize
    ContactActionsSettings::self()->load();

    if (ContactActionsSettings::self()->showAddressAction() == ContactActionsSettings::UseBrowser) {
        QString urlTemplate = ContactActionsSettings::self()->addressUrl();
        replaceArguments(urlTemplate, address);
        if (!urlTemplate.isEmpty()) {
            QDesktopServices::openUrl(QUrl(urlTemplate));
        }
    } else if (ContactActionsSettings::self()->showAddressAction() == ContactActionsSettings::UseExternalAddressApplication) {
        QString commandTemplate = ContactActionsSettings::self()->addressCommand();
        replaceArguments(commandTemplate, address);

        if (!commandTemplate.isEmpty()) {
            KRun::runCommand(commandTemplate, nullptr);
        }
    } else if (ContactActionsSettings::self()->showAddressAction() == ContactActionsSettings::UseGooglemap) {
        QString urlTemplate = QStringLiteral("https://maps.google.com/maps?q=%s,%l,%c");
        replaceArguments(urlTemplate, address);
        if (!urlTemplate.isEmpty()) {
            QDesktopServices::openUrl(QUrl(urlTemplate));
        }
    } else if (ContactActionsSettings::self()->showAddressAction() == ContactActionsSettings::UseMapquest) {
        QString urlTemplate = QStringLiteral("https://www.mapquest.com/search/result?query=%s,%l,%c");
        replaceArguments(urlTemplate, address);
        if (!urlTemplate.isEmpty()) {
            QDesktopServices::openUrl(QUrl(urlTemplate));
        }
    } else if (ContactActionsSettings::self()->showAddressAction() == ContactActionsSettings::UseOpenStreetMap) {
        QString urlTemplate = QStringLiteral("https://www.openstreetmap.org/search?query=%s,%l,%c");
        replaceArguments(urlTemplate, address);
        if (!urlTemplate.isEmpty()) {
            QDesktopServices::openUrl(QUrl(urlTemplate));
        }
    }
}
