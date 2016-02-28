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

#include "mailwidgetlister.h"
#include "mailwidget.h"

#include <KContacts/Addressee>
#include <QDebug>
using namespace Akonadi;

MailWidgetLister::MailWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

MailWidgetLister::~MailWidgetLister()
{

}

void MailWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    KContacts::Email::List mailList = contact.emailList();
    if (mailList.isEmpty()) {
        setNumberOfShownWidgetsTo(1);
    } else {
        setNumberOfShownWidgetsTo(mailList.count());
        const QList<QWidget *> widgetList = widgets();
        auto wIt = widgetList.constBegin();
        auto wEnd = widgetList.constEnd();
        for (int i = 0; wIt != wEnd; ++wIt, ++i) {
            MailWidget *w = qobject_cast<MailWidget *>(*wIt);
            w->setMail(mailList.at(i));
        }
    }
}

void MailWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    const QList<QWidget *> widgetList = widgets();
    KContacts::Email::List emailList;
    for (QWidget *widget : widgetList) {
        MailWidget *w = qobject_cast<MailWidget *>(widget);
        KContacts::Email newEmail = w->email();
        if (newEmail.isValid()) {
            emailList << newEmail;
        }
    }
    contact.setEmailList(emailList);
}

QWidget *MailWidgetLister::createWidget(QWidget *parent)
{
    MailWidget *w = new MailWidget(parent);
    reconnectWidget(w);
    return w;
}

void MailWidgetLister::reconnectWidget(MailWidget *w)
{
    connect(w, &MailWidget::addWidget, this, &MailWidgetLister::slotAddWidget, Qt::UniqueConnection);
    connect(w, &MailWidget::removeWidget, this, &MailWidgetLister::slotRemoveWidget, Qt::UniqueConnection);
    connect(w, &MailWidget::preferredChanged, this, &MailWidgetLister::slotPreferredChanged, Qt::UniqueConnection);
}

void MailWidgetLister::slotAddWidget(MailWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void MailWidgetLister::slotRemoveWidget(MailWidget *w)
{
    if (widgets().count() == 1) {
        w->clearWidget();
    } else {
        removeWidget(w);
        updateAddRemoveButton();
    }
}

void MailWidgetLister::slotPreferredChanged(MailWidget *w)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        if (widget != w) {
            (static_cast<MailWidget *>(widget))->setPreferred(false);
        }
    }
}

void MailWidgetLister::updateAddRemoveButton()
{
    const QList<QWidget *> widgetList = widgets();
    const int numberOfWidget(widgetList.count());
    bool addButtonEnabled = false;
    if (numberOfWidget <= widgetsMinimum()) {
        addButtonEnabled = true;
    } else if (numberOfWidget >= widgetsMaximum()) {
        addButtonEnabled = false;
    } else {
        addButtonEnabled = true;
    }

    for (QWidget *widget : widgetList) {
        MailWidget *w = qobject_cast<MailWidget *>(widget);
        w->updateAddRemoveButton(addButtonEnabled);
    }
}
