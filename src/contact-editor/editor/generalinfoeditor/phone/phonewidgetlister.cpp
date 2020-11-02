/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonewidgetlister.h"
#include "phonewidget.h"

#include <KContacts/Addressee>
using namespace ContactEditor;

PhoneWidgetLister::PhoneWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

PhoneWidgetLister::~PhoneWidgetLister()
{
}

void PhoneWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    const KContacts::PhoneNumber::List phoneNumbers = contact.phoneNumbers();
    if (phoneNumbers.isEmpty()) {
        setNumberOfShownWidgetsTo(1);
    } else {
        setNumberOfShownWidgetsTo(phoneNumbers.count());
        const QList<QWidget *> widgetList = widgets();
        auto wIt = widgetList.constBegin();
        auto wEnd = widgetList.constEnd();
        for (int i = 0; wIt != wEnd; ++wIt, ++i) {
            auto *w = qobject_cast<PhoneWidget *>(*wIt);
            w->loadPhone(phoneNumbers.at(i));
        }
    }
}

void PhoneWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    KContacts::PhoneNumber::List phoneNumbers;
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        auto *w = qobject_cast<PhoneWidget *>(widget);
        KContacts::PhoneNumber number = w->storePhone();
        if (!number.isEmpty()) {
            phoneNumbers << number;
        }
    }
    contact.setPhoneNumbers(phoneNumbers);
}

void PhoneWidgetLister::setReadOnly(bool readOnly)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        auto *w = qobject_cast<PhoneWidget *>(widget);
        w->setReadOnly(readOnly);
    }
}

QWidget *PhoneWidgetLister::createWidget(QWidget *parent)
{
    auto *w = new PhoneWidget(parent);
    reconnectWidget(w);
    return w;
}

void PhoneWidgetLister::reconnectWidget(PhoneWidget *w)
{
    connect(w, &PhoneWidget::addWidget, this, &PhoneWidgetLister::slotAddWidget, Qt::UniqueConnection);
    connect(w, &PhoneWidget::removeWidget, this, &PhoneWidgetLister::slotRemoveWidget, Qt::UniqueConnection);
    connect(w, &PhoneWidget::preferredChanged, this, &PhoneWidgetLister::slotPreferredChanged, Qt::UniqueConnection);
}

void PhoneWidgetLister::slotAddWidget(PhoneWidget *w)
{
    addWidgetAfterThisWidget(w);
    updateAddRemoveButton();
}

void PhoneWidgetLister::slotRemoveWidget(PhoneWidget *w)
{
    if (widgets().count() == 1) {
        w->clearWidget();
    } else {
        removeWidget(w);
        updateAddRemoveButton();
    }
}

void PhoneWidgetLister::slotPreferredChanged(PhoneWidget *w)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        if (widget != w) {
            (static_cast<PhoneWidget *>(widget))->setPreferred(false);
        }
    }
}

void PhoneWidgetLister::updateAddRemoveButton()
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
        auto *w = qobject_cast<PhoneWidget *>(widget);
        w->updateAddRemoveButton(addButtonEnabled);
    }
}
