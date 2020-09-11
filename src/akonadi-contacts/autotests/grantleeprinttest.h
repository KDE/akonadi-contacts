/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEPRINTTEST_H
#define GRANTLEEPRINTTEST_H

#include <QObject>

class GrantleePrintTest : public QObject
{
    Q_OBJECT
public:
    explicit GrantleePrintTest(QObject *parent = nullptr);
    ~GrantleePrintTest();
private Q_SLOTS:
    void shouldReturnEmptyStringWhenNotContentAndNoContacts();
    void shouldReturnEmptyStringWhenAddContentWithoutContacts();
    void shouldReturnStringWhenAddContentAndContacts();
    void shouldReturnEmails();

    void shouldDisplayContactInfo_data();
    void shouldDisplayContactInfo();
};

#endif // GRANTLEEPRINTTEST_H
