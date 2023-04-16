/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "../../widgets/kwidgetlister_p.h"
namespace KContacts
{
class Addressee;
}
namespace AkonadiContactWidgets
{
class MessagingWidget;
class MessagingWidgetLister : public KWidgetLister
{
    Q_OBJECT
public:
    explicit MessagingWidgetLister(QWidget *parent = nullptr);
    ~MessagingWidgetLister() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);

protected:
    QWidget *createWidget(QWidget *) override;

private:
    void slotAddWidget(MessagingWidget *w);
    void slotRemoveWidget(MessagingWidget *w);
    void slotPreferredChanged(MessagingWidget *w);
    void reconnectWidget(MessagingWidget *w);
    void updateAddRemoveButton();
};
}
