/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef QEKIGADIALER_H
#define QEKIGADIALER_H

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

#endif // QEKIGADIALER_H
