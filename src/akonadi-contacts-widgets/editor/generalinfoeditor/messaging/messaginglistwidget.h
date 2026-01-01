/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace KContacts
{
class Addressee;
}
namespace Akonadi
{
class MessagingWidgetLister;
class MessagingListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessagingListWidget(QWidget *parent = nullptr);
    ~MessagingListWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    Akonadi::MessagingWidgetLister *mMessagingWidgetLister = nullptr;
};
}
