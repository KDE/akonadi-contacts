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

#include "phonewidgetlister.h"
#include "phonewidget.h"
using namespace Akonadi;

PhoneWidgetLister::PhoneWidgetLister(QWidget *parent)
    : KWidgetLister(1, 4, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

PhoneWidgetLister::~PhoneWidgetLister()
{

}

void PhoneWidgetLister::loadContact(const KContacts::Addressee &contact)
{

}

void PhoneWidgetLister::storeContact(KContacts::Addressee &contact) const
{

}

QWidget *PhoneWidgetLister::createWidget(QWidget *parent)
{
    PhoneWidget *w = new PhoneWidget(parent);
    reconnectWidget(w);
    return w;
}

void PhoneWidgetLister::reconnectWidget(PhoneWidget *w)
{
    connect(w, &PhoneWidget::addWidget, this, &PhoneWidgetLister::slotAddWidget, Qt::UniqueConnection);
    connect(w, &PhoneWidget::removeWidget, this, &PhoneWidgetLister::slotRemoveWidget, Qt::UniqueConnection);
}

void PhoneWidgetLister::slotAddWidget(QWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void PhoneWidgetLister::slotRemoveWidget(QWidget *w)
{
    removeWidget(w);
    updateAddRemoveButton();
}

void PhoneWidgetLister::updateAddRemoveButton()
{
    QList<QWidget *> widgetList = widgets();
    const int numberOfWidget(widgetList.count());
    bool addButtonEnabled = false;
    bool removeButtonEnabled = false;
    if (numberOfWidget <= widgetsMinimum()) {
        addButtonEnabled = true;
        removeButtonEnabled = false;
    } else if (numberOfWidget >= widgetsMaximum()) {
        addButtonEnabled = false;
        removeButtonEnabled = true;
    } else {
        addButtonEnabled = true;
        removeButtonEnabled = true;
    }
    QList<QWidget *>::ConstIterator wIt = widgetList.constBegin();
    QList<QWidget *>::ConstIterator wEnd = widgetList.constEnd();
    for (; wIt != wEnd; ++wIt) {
        PhoneWidget *w = qobject_cast<PhoneWidget *>(*wIt);
        w->updateAddRemoveButton(addButtonEnabled, removeButtonEnabled);
    }
}
