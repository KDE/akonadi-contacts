/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "../../widgets/kwidgetlister_p.h"
#include "akonadi_contact_widgets_private_export.h"
namespace KContacts
{
class Addressee;
}
namespace Akonadi
{
class PhoneWidget;
class AKONADI_CONTACT_WIDGETS_TESTS_EXPORT PhoneWidgetLister : public KWidgetLister
{
    Q_OBJECT
public:
    explicit PhoneWidgetLister(QWidget *parent = nullptr);
    ~PhoneWidgetLister() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

protected:
    QWidget *createWidget(QWidget *) override;

private:
    void slotAddWidget(PhoneWidget *w);
    void slotRemoveWidget(PhoneWidget *w);
    void slotPreferredChanged(PhoneWidget *w);
    void reconnectWidget(PhoneWidget *w);
    void updateAddRemoveButton();
};
}
