/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

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

#include "qekigadialer.h"

#include <KLocalizedString>

#include <QProcess>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusReply>

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

    QDBusInterface *interface = new QDBusInterface(service, path, QString(), QDBusConnection::sessionBus());
    if (!interface->isValid()) {
        delete interface;
        interface = new QDBusInterface(service, path, QString(), QDBusConnection::sessionBus());
    }

    return interface;
}

QEkigaDialer::QEkigaDialer(const QString &applicationName)
    : QDialer(applicationName)
    , mInterface(nullptr)
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
        if (!QProcess::startDetached(QStringLiteral("ekiga"), QStringList())) {
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
    Q_UNUSED(number);
    Q_UNUSED(text);
    mErrorMessage = i18n("Sending an SMS is currently not supported on Ekiga.");
    return false;
}
