/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "showaddressaction.h"

#include "contactactionssettings.h"

#include <kcontacts/address.h>
#include <KDialogJobUiDelegate>
#include <KIO/CommandLauncherJob>

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
            KIO::CommandLauncherJob *job = new KIO::CommandLauncherJob(commandTemplate);
            job->setUiDelegate(new KDialogJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));
            job->start();
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
