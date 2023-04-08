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
namespace ContactEditor
{
class MailWidget;
class MailWidgetLister : public KWidgetLister
{
    Q_OBJECT
public:
    explicit MailWidgetLister(QWidget *parent = nullptr);
    ~MailWidgetLister() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

protected:
    QWidget *createWidget(QWidget *) override;

private:
    void slotAddWidget(MailWidget *w);
    void slotRemoveWidget(MailWidget *w);
    void slotPreferredChanged(MailWidget *w);
    void reconnectWidget(MailWidget *w);
    void updateAddRemoveButton();
};
}
