/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PreferredLineEditWidget_H
#define PreferredLineEditWidget_H

#include <QObject>

class PreferredLineEditWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit PreferredLineEditWidgetTest(QObject *parent = nullptr);
    ~PreferredLineEditWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangePreferredValue();
};

#endif // PreferredLineEditWidget_H
