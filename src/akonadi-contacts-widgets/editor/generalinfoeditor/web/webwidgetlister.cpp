/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "webwidgetlister.h"
#include "webwidget.h"

#include <KContacts/Addressee>
using namespace ContactEditor;

WebWidgetLister::WebWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

WebWidgetLister::~WebWidgetLister() = default;

void WebWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    KContacts::ResourceLocatorUrl::List resourceLocatorList = contact.extraUrlList();
    if (resourceLocatorList.isEmpty()) {
        setNumberOfShownWidgetsTo(1);
    } else {
        setNumberOfShownWidgetsTo(resourceLocatorList.count());
        const QList<QWidget *> widgetList = widgets();
        auto wIt = widgetList.constBegin();
        auto wEnd = widgetList.constEnd();
        for (int i = 0; wIt != wEnd; ++wIt, ++i) {
            auto w = qobject_cast<WebWidget *>(*wIt);
            w->loadWebSite(resourceLocatorList.at(i));
        }
    }
}

void WebWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    const QList<QWidget *> widgetList = widgets();
    KContacts::ResourceLocatorUrl::List resourceLocatorList;
    for (QWidget *widget : widgetList) {
        auto w = qobject_cast<WebWidget *>(widget);
        KContacts::ResourceLocatorUrl newUrl = w->url();
        if (newUrl.isValid()) {
            resourceLocatorList << newUrl;
        }
    }
    contact.setExtraUrlList(resourceLocatorList);
}

void WebWidgetLister::setReadOnly(bool readOnly)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        auto w = qobject_cast<WebWidget *>(widget);
        w->setReadOnly(readOnly);
    }
}

QWidget *WebWidgetLister::createWidget(QWidget *parent)
{
    auto w = new WebWidget(parent);
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
        auto w = qobject_cast<WebWidget *>(*wIt);
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

#include "moc_webwidgetlister.cpp"
