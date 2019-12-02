/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Felix Mauch (felix_mauch@web.de)

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

#include "sendsmsaction.h"

#include "contactactionssettings.h"
#include "qskypedialer.h"
#include "qsflphonedialer.h"
#include "smsdialog.h"

#include <kcontacts/phonenumber.h>
#include <KLocalizedString>
#include <KMessageBox>
#include <KRun>

#include <QDesktopServices>
#include <QPointer>
#include <QUrl>
#include <QUrlQuery>

#include <memory>

void SendSmsAction::sendSms(const KContacts::PhoneNumber &phoneNumber)
{
    const QString number = phoneNumber.number().trimmed();

    // synchronize
    ContactActionsSettings::self()->load();

    // check for valid config first, so the user doesn't type the message without a way to actually send it
    QString command = ContactActionsSettings::self()->smsCommand();
    if (command.isEmpty() && ContactActionsSettings::self()->sendSmsAction() == ContactActionsSettings::UseExternalSmsApplication) {
        KMessageBox::sorry(nullptr, i18n("There is no application set which could be executed.\nPlease go to the settings dialog and configure one."));
        return;
    }

    QPointer<SmsDialog> dlg(new SmsDialog(number));
    if (dlg->exec() != QDialog::Accepted) {   // the cancel button has been clicked
        delete dlg;
        return;
    }
    const QString message = (dlg != nullptr ? dlg->message() : QString());
    delete dlg;

    std::unique_ptr<QDialer> dialer;
    //   we handle skype separated
    if (ContactActionsSettings::self()->sendSmsAction() == ContactActionsSettings::UseSkypeSms) {
        dialer.reset(new QSkypeDialer(QStringLiteral("AkonadiContacts")));
    } else if (ContactActionsSettings::self()->sendSmsAction() == ContactActionsSettings::UseSflPhoneSms) {
        dialer.reset(new QSflPhoneDialer(QStringLiteral("AkonadiContacts")));
    }
    if (dialer) {
        if (dialer->sendSms(number, message)) {
            // I'm not sure whether here should be a notification.
            // Skype can do a notification itself if whished.
        } else {
            KMessageBox::sorry(nullptr, dialer->errorMessage());
        }
    }

    if (ContactActionsSettings::self()->sendSmsAction() == ContactActionsSettings::UseSystemDefaultSms) {
        QUrl url;
        url.setScheme(QStringLiteral("sms"));
        url.setPath(phoneNumber.normalizedNumber());
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("body"), message);
        url.setQuery(query);
        QDesktopServices::openUrl(url);
        return;
    }

    /*
     * %N the raw number
     * %n the number with all additional non-number characters removed
     */
    command.replace(QLatin1String("%N"), QStringLiteral("\"%1\"").arg(phoneNumber.number()));
    command.replace(QLatin1String("%n"), QStringLiteral("\"%1\"").arg(phoneNumber.normalizedNumber()));
    command.replace(QLatin1String("%t"), QStringLiteral("\"%1\"").arg(message));
    //Bug: 293232 In KDE3 We used %F to replace text
    command.replace(QLatin1String("%F"), message);
    KRun::runCommand(command, nullptr);
}
