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

#include "messagingwidgetlister.h"
#include "messagingwidget.h"
using namespace Akonadi;

MessagingWidgetLister::MessagingWidgetLister(QWidget *parent)
    : KWidgetLister(1, 4, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

MessagingWidgetLister::~MessagingWidgetLister()
{

}

QWidget *MessagingWidgetLister::createWidget(QWidget *parent)
{
    MessagingWidget *w = new MessagingWidget(parent);
    reconnectWidget(w);
    return w;
}

void MessagingWidgetLister::reconnectWidget(MessagingWidget *w)
{
    connect(w, &MessagingWidget::addWidget, this, &MessagingWidgetLister::slotAddWidget, Qt::UniqueConnection);
    connect(w, &MessagingWidget::removeWidget, this, &MessagingWidgetLister::slotRemoveWidget, Qt::UniqueConnection);
}

void MessagingWidgetLister::slotAddWidget(QWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void MessagingWidgetLister::slotRemoveWidget(QWidget *w)
{
    removeWidget(w);
    updateAddRemoveButton();
}

void MessagingWidgetLister::updateAddRemoveButton()
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
        MessagingWidget *w = qobject_cast<MessagingWidget *>(*wIt);
        w->updateAddRemoveButton(addButtonEnabled, removeButtonEnabled);
    }
}
