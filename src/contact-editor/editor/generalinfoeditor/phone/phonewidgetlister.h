/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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

#ifndef PHONEWIDGETLISTER_H
#define PHONEWIDGETLISTER_H

#include "../../widgets/kwidgetlister_p.h"
#include "contacteditor_private_export.h"
namespace KContacts
{
class Addressee;
}
namespace ContactEditor
{
class PhoneWidget;
class CONTACTEDITOR_TESTS_EXPORT PhoneWidgetLister : public KWidgetLister
{
    Q_OBJECT
public:
    explicit PhoneWidgetLister(QWidget *parent = nullptr);
    ~PhoneWidgetLister();

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

protected:
    QWidget *createWidget(QWidget *) override;

private Q_SLOTS:
    void slotAddWidget(PhoneWidget *w);
    void slotRemoveWidget(PhoneWidget *w);
    void slotPreferredChanged(PhoneWidget *w);

private:
    void reconnectWidget(PhoneWidget *w);
    void updateAddRemoveButton();
};
}
#endif // PHONEWIDGETLISTER_H
