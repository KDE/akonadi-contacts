/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MESSAGINGWIDGETTEST_H
#define MESSAGINGWIDGETTEST_H

#include <QObject>

class MessagingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MessagingWidgetTest(QObject *parent = nullptr);
    ~MessagingWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // MESSAGINGWIDGETTEST_H
