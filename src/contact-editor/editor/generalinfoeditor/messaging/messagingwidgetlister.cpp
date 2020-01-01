/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2020 Laurent Montel <montel.org>

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
#include "../../utils/utils.h"

#include <KContacts/Addressee>
using namespace ContactEditor;

MessagingWidgetLister::MessagingWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

MessagingWidgetLister::~MessagingWidgetLister()
{
}

void MessagingWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    const auto imaddresses = contact.imppList();
    if (imaddresses.isEmpty()) {
        setNumberOfShownWidgetsTo(1);
    } else {
        setNumberOfShownWidgetsTo(imaddresses.count());
        const QList<QWidget *> widgetList = widgets();
        auto wIt = widgetList.constBegin();
        auto wEnd = widgetList.constEnd();
        for (int i = 0; wIt != wEnd; ++wIt, ++i) {
            MessagingWidget *w = qobject_cast<MessagingWidget *>(*wIt);
            w->setIMAddress(imaddresses.at(i));
        }
    }
}

void MessagingWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    KContacts::Impp::List imaddresses;
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        MessagingWidget *w = qobject_cast<MessagingWidget *>(widget);
        imaddresses << w->imAddress();
    }
    contact.setImppList(imaddresses);
}

void MessagingWidgetLister::setReadOnly(bool readOnly)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        MessagingWidget *w = qobject_cast<MessagingWidget *>(widget);
        w->setReadOnly(readOnly);
    }
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
    connect(w, &MessagingWidget::preferredChanged, this, &MessagingWidgetLister::slotPreferredChanged, Qt::UniqueConnection);
}

void MessagingWidgetLister::slotPreferredChanged(MessagingWidget *w)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        if (widget != w) {
            (static_cast<MessagingWidget *>(widget))->setPreferred(false);
        }
    }
}

void MessagingWidgetLister::slotAddWidget(MessagingWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void MessagingWidgetLister::slotRemoveWidget(MessagingWidget *w)
{
    if (widgets().count() == 1) {
        w->clearWidget();
    } else {
        removeWidget(w);
        updateAddRemoveButton();
    }
}

void MessagingWidgetLister::updateAddRemoveButton()
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
        MessagingWidget *w = qobject_cast<MessagingWidget *>(*wIt);
        w->updateAddRemoveButton(addButtonEnabled);
    }
}
