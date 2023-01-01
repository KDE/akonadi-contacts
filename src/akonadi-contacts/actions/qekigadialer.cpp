/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "qekigadialer.h"

#include <KLocalizedString>

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusReply>
#include <QProcess>
#include <QStandardPaths>

#if !defined(Q_OS_WIN)
#include <unistd.h>
#else
#include <windows.h>
#endif

static bool isEkigaServiceRegistered()
{
    const QString service(QStringLiteral("org.ekiga.Ekiga"));

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

static QDBusInterface *searchEkigaDBusInterface()
{
    const QString service(QStringLiteral("org.ekiga.Ekiga"));
    const QString path(QStringLiteral("/org/ekiga/Ekiga"));

    auto interface = new QDBusInterface(service, path, QString(), QDBusConnection::sessionBus());
    if (!interface->isValid()) {
        delete interface;
        interface = new QDBusInterface(service, path, QString(), QDBusConnection::sessionBus());
    }

    return interface;
}

QEkigaDialer::QEkigaDialer(const QString &applicationName)
    : QDialer(applicationName)
{
}

QEkigaDialer::~QEkigaDialer()
{
    delete mInterface;
}

bool QEkigaDialer::initializeEkiga()
{
    // first check whether dbus interface is available yet
    if (!isEkigaServiceRegistered()) {
        // it could be ekiga is not running yet, so start it now
        const QString progFullPath = QStandardPaths::findExecutable(QStringLiteral("ekiga"));
        if (progFullPath.isEmpty() || !QProcess::startDetached(QStringLiteral("ekiga"), QStringList())) {
            mErrorMessage = i18n("Unable to start ekiga process, check that ekiga executable is in your PATH variable.");
            return false;
        }

        const int runs = 100;
        for (int i = 0; i < runs; ++i) {
            if (!isEkigaServiceRegistered()) {
#if !defined(Q_OS_WIN)
                ::sleep(2);
#else
                Sleep(2000);
#endif
            } else {
                break;
            }
        }
    }

    // check again for the dbus interface
    mInterface = searchEkigaDBusInterface();

    if (!mInterface->isValid()) {
        delete mInterface;
        mInterface = nullptr;

        mErrorMessage = i18n("Ekiga Public API (D-Bus) seems to be disabled.");
        return false;
    }

    return true;
}

bool QEkigaDialer::dialNumber(const QString &number)
{
    if (!initializeEkiga()) {
        return false;
    }
    QDBusReply<void> reply = mInterface->call(QStringLiteral("Call"), number);
    return true;
}

bool QEkigaDialer::sendSms(const QString &number, const QString &text)
{
    Q_UNUSED(number)
    Q_UNUSED(text)
    mErrorMessage = i18n("Sending an SMS is currently not supported on Ekiga.");
    return false;
}
