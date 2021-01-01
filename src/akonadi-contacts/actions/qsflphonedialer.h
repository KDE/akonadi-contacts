/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef QSFLPHONEDIALER_H
#define QSFLPHONEDIALER_H

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
#endif // QSFLPHONEDIALER_H
