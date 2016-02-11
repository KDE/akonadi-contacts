/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/


#ifndef CUSTOMFIELDSWIDGETTEST_H
#define CUSTOMFIELDSWIDGETTEST_H

#include <QObject>

class CustomFieldsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CustomFieldsWidgetTest(QObject *parent = Q_NULLPTR);
    ~CustomFieldsWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CUSTOMFIELDSWIDGETTEST_H
