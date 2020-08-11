/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mailwidgetlister.h"
#include "mailwidget.h"

#include <KContacts/Addressee>
using namespace ContactEditor;

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
    emailList.reserve(widgetList.count());
    for (QWidget *widget : widgetList) {
        MailWidget *w = qobject_cast<MailWidget *>(widget);
        KContacts::Email newEmail = w->email();
        if (newEmail.isValid()) {
            emailList << newEmail;
        }
    }
    contact.setEmailList(emailList);
}

void MailWidgetLister::setReadOnly(bool readOnly)
{
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        MailWidget *w = qobject_cast<MailWidget *>(widget);
        w->setReadOnly(readOnly);
    }
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
