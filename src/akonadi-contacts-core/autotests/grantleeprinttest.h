/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrantleePrintTest : public QObject
{
    Q_OBJECT
public:
    explicit GrantleePrintTest(QObject *parent = nullptr);
    ~GrantleePrintTest() override;
private Q_SLOTS:
    void shouldReturnEmptyStringWhenNotContentAndNoContacts();
    void shouldReturnEmptyStringWhenAddContentWithoutContacts();
    void shouldReturnStringWhenAddContentAndContacts();
    void shouldReturnEmails();

    void shouldDisplayContactInfo_data();
    void shouldDisplayContactInfo();
};
