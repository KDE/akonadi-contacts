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

#ifndef MAILWIDGETLISTER_H
#define MAILWIDGETLISTER_H

#include "../../widgets/kwidgetlister_p.h"
namespace KContacts
{
class Addressee;
}
namespace Akonadi
{
class MailWidget;
class MailWidgetLister : public KWidgetLister
{
    Q_OBJECT
public:
    explicit MailWidgetLister(QWidget *parent = Q_NULLPTR);
    ~MailWidgetLister();

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;

protected:
    QWidget *createWidget(QWidget *) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotAddWidget(MailWidget *w);
    void slotRemoveWidget(MailWidget *w);
    void slotPreferredChanged(MailWidget *w);

private:
    void reconnectWidget(MailWidget *w);
    void updateAddRemoveButton();
};
}
#endif // MAILWIDGETLISTER_H
