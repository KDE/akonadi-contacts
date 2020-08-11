/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CUSTOMFIELDSWIDGETTEST_H
#define CUSTOMFIELDSWIDGETTEST_H

#include <QObject>

class CustomFieldsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomFieldsWidgetTest(QObject *parent = nullptr);
    ~CustomFieldsWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CUSTOMFIELDSWIDGETTEST_H
