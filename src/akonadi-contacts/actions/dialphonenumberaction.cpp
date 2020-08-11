/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dialphonenumberaction.h"

#include "contactactionssettings.h"
#include "qdialer.h"
#include "qsflphonedialer.h"
#include "qskypedialer.h"
#include "qekigadialer.h"

#include <kcontacts/phonenumber.h>
#include <KLocalizedString>
#include <KMessageBox>
#include <KDialogJobUiDelegate>
#include <KIO/CommandLauncherJob>

#include <QDesktopServices>

using namespace Akonadi;

void DialPhoneNumberAction::dialNumber(const KContacts::PhoneNumber &number)
{
    // synchronize
    ContactActionsSettings::self()->load();

    QDialer *dialer = nullptr;
    // we handle skype separated
    if (ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseSkype) {
        dialer = new QSkypeDialer(QStringLiteral("AkonadiContacts"));
    } else if (ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseSflPhone) {
        dialer = new QSflPhoneDialer(QStringLiteral("AkonadiContacts"));
    } else if (ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseEkiga) {
        dialer = new QEkigaDialer(QStringLiteral("AkonadiContacts"));
    }
    if (dialer) {
        if (!dialer->dialNumber(number.normalizedNumber())) {
            KMessageBox::sorry(nullptr, dialer->errorMessage());
        }
        delete dialer;
        return;
    }

    if (ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseSystemDefault) {
        QUrl url;
        url.setScheme(QStringLiteral("tel"));
        url.setPath(number.normalizedNumber());
        QDesktopServices::openUrl(url);
        return;
    }

    QString command = ContactActionsSettings::self()->phoneCommand();
    if (command.isEmpty()) {
        KMessageBox::sorry(nullptr, i18n("There is no application set which could be executed.\nPlease go to the settings dialog and configure one."));
        return;
    }

    /*
     * %N the raw number
     * %n the number with all additional non-number characters removed
     */
    command.replace(QLatin1String("%N"), number.number());
    command.replace(QLatin1String("%n"), number.normalizedNumber());

    KIO::CommandLauncherJob *job = new KIO::CommandLauncherJob(command);
    job->setUiDelegate(new KDialogJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));
    job->start();

}
