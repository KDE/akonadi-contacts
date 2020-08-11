/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CONTACTMETADATAATTRIBUTETEST_H
#define CONTACTMETADATAATTRIBUTETEST_H

#include <QObject>

class ContactMetaDataAttributeTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void type();
    void clone();
    void serialization();
};

#endif
