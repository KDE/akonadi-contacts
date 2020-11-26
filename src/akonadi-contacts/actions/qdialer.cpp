/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>
    SPDX-FileCopyrightText: 2010 Bjoern Ricks <bjoern.ricks@intevation.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "qdialer.h"

#include <KLocalizedString>

QDialer::QDialer(const QString &applicationName)
    : mApplicationName(applicationName)
{
}

QDialer::~QDialer()
{
}

bool QDialer::dialNumber(const QString &number)
{
    Q_UNUSED(number)
    mErrorMessage = i18n("Dialing a number is not supported");

    return false;
}

bool QDialer::sendSms(const QString &number, const QString &text)
{
    Q_UNUSED(number)
    Q_UNUSED(text)
    mErrorMessage = i18n("Sending an SMS is not supported");

    return false;
}

QString QDialer::errorMessage() const
{
    return mErrorMessage;
}
