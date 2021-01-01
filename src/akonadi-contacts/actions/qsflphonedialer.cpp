/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "qsflphonedialer.h"

#include <KLocalizedString>

#include <QProcess>
#include <QDBusConnection>
#include <QDBusConnectionInterface>

#if !defined(Q_OS_WIN)
#include <unistd.h>
#else
#include <windows.h>
#endif

static bool isSflPhoneServiceRegistered()
{
    const QString service(QStringLiteral("org.sflphone.SFLphone"));

    QDBusConnectionInterface *interface = QDBusConnection::sessionBus().interface();
    if (interface->isServiceRegistered(service)) {
        return true;
    }

    interface = QDBusConnection::sessionBus().interface();
    if (interface->isServiceRegistered(service)) {
        return true;
    }
    return false;
}

QSflPhoneDialer::QSflPhoneDialer(const QString &applicationName)
    : QDialer(applicationName)
{
}

QSflPhoneDialer::~QSflPhoneDialer()
{
}

bool QSflPhoneDialer::initializeSflPhone()
{
    // first check whether dbus interface is available yet
    if (!isSflPhoneServiceRegistered()) {
        // it could be skype is not running yet, so start it now
        if (!QProcess::startDetached(QStringLiteral("sflphone-client-kde"), QStringList())) {
            mErrorMessage = i18n("Unable to start sflphone-client-kde process, check that sflphone-client-kde executable is in your PATH variable.");
            return false;
        }

        const int runs = 100;
        for (int i = 0; i < runs; ++i) {
            if (!isSflPhoneServiceRegistered()) {
#if !defined(Q_OS_WIN)
                ::sleep(2);
#else
                Sleep(2000);
#endif
            } else {
                return true;
            }
        }
    }
    return true;
}

bool QSflPhoneDialer::dialNumber(const QString &number)
{
    if (!initializeSflPhone()) {
        return false;
    }

    QStringList arguments;
    arguments << QStringLiteral("--place-call");
    arguments << number;
    if (!QProcess::startDetached(QStringLiteral("sflphone-client-kde"), arguments)) {
        return false;
    }

    return true;
}

bool QSflPhoneDialer::sendSms(const QString &number, const QString &text)
{
    if (!initializeSflPhone()) {
        return false;
    }

    QStringList arguments;
    arguments << QStringLiteral("--send-text");
    arguments << number;
    arguments << QStringLiteral("--message");
    arguments << text;
    if (!QProcess::startDetached(QStringLiteral("sflphone-client-kde"), arguments)) {
        return false;
    }
    return true;
}
