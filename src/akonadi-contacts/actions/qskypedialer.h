/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "qdialer.h"

#include <QString>

class QDBusInterface;

class QSkypeDialer : public QDialer
{
public:
    explicit QSkypeDialer(const QString &applicationName);
    ~QSkypeDialer() override;

    Q_REQUIRED_RESULT bool dialNumber(const QString &number) override;
    Q_REQUIRED_RESULT bool sendSms(const QString &number, const QString &text) override;

private:
    bool initializeSkype();

    QDBusInterface *mInterface = nullptr;
};
