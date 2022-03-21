/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>
    SPDX-FileCopyrightText: 2010 Bjoern Ricks <bjoern.ricks@intevation.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QString>

class QDialer
{
public:
    explicit QDialer(const QString &applicationName);
    virtual ~QDialer();

    Q_REQUIRED_RESULT virtual bool dialNumber(const QString &number);
    Q_REQUIRED_RESULT virtual bool sendSms(const QString &number, const QString &text);

    Q_REQUIRED_RESULT QString errorMessage() const;

protected:
    const QString mApplicationName;
    QString mErrorMessage;
};
