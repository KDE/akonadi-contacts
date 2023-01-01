/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "qdialer.h"
class QDBusInterface;

class QEkigaDialer : public QDialer
{
public:
    explicit QEkigaDialer(const QString &applicationName);
    ~QEkigaDialer() override;

    Q_REQUIRED_RESULT bool dialNumber(const QString &number) override;
    Q_REQUIRED_RESULT bool sendSms(const QString &number, const QString &text) override;

private:
    bool initializeEkiga();
    QDBusInterface *mInterface = nullptr;
};
