/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "qdialer.h"

class QSflPhoneDialer : public QDialer
{
public:
    explicit QSflPhoneDialer(const QString &applicationName);
    ~QSflPhoneDialer() override;

    Q_REQUIRED_RESULT bool dialNumber(const QString &number) override;
    Q_REQUIRED_RESULT bool sendSms(const QString &number, const QString &text) override;

private:
    bool initializeSflPhone();
};
