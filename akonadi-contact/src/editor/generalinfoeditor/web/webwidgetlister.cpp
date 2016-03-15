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

#include "webwidgetlister.h"
#include "webwidget.h"
using namespace Akonadi;

WebWidgetLister::WebWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

WebWidgetLister::~WebWidgetLister()
{

}

void WebWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    //TODO
#if 0
    const KContacts::PhoneNumber::List phoneNumbers = contact.phoneNumbers();
    setNumberOfShownWidgetsTo(phoneNumbers.count());
    QList<QWidget *>::ConstIterator wIt = widgets().constBegin();
    QList<QWidget *>::ConstIterator wEnd = widgets().constEnd();
    for (int i = 0; wIt != wEnd; ++wIt, ++i) {
        PhoneWidget *w = qobject_cast<PhoneWidget *>(*wIt);
        w->loadPhone(phoneNumbers.at(i));
    }
#endif
}

void WebWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    //TODO
}

QWidget *WebWidgetLister::createWidget(QWidget *parent)
{
    WebWidget *w = new WebWidget(parent);
    reconnectWidget(w);
    return w;
}

void WebWidgetLister::reconnectWidget(WebWidget *w)
{
    connect(w, &WebWidget::addWidget, this, &WebWidgetLister::slotAddWidget, Qt::UniqueConnection);
    connect(w, &WebWidget::removeWidget, this, &WebWidgetLister::slotRemoveWidget, Qt::UniqueConnection);
    connect(w, &WebWidget::preferredChanged, this, &WebWidgetLister::slotPreferredChanged, Qt::UniqueConnection);
}

void WebWidgetLister::slotAddWidget(WebWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void WebWidgetLister::slotRemoveWidget(WebWidget *w)
{
    if (widgets().count() == 1) {
        w->clearWidget();
    } else {
        removeWidget(w);
        updateAddRemoveButton();
    }
}

void WebWidgetLister::updateAddRemoveButton()
{
    QList<QWidget *> widgetList = widgets();
    const int numberOfWidget(widgetList.count());
    bool addButtonEnabled = false;
    if (numberOfWidget <= widgetsMinimum()) {
        addButtonEnabled = true;
    } else if (numberOfWidget >= widgetsMaximum()) {
        addButtonEnabled = false;
    } else {
        addButtonEnabled = true;
    }
    QList<QWidget *>::ConstIterator wIt = widgetList.constBegin();
    QList<QWidget *>::ConstIterator wEnd = widgetList.constEnd();
    for (; wIt != wEnd; ++wIt) {
        WebWidget *w = qobject_cast<WebWidget *>(*wIt);
        w->updateAddRemoveButton(addButtonEnabled);
    }
}

void WebWidgetLister::slotPreferredChanged(WebWidget *w)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        if (widget != w) {
            (static_cast<WebWidget *>(widget))->setPreferred(false);
        }
    }
}

