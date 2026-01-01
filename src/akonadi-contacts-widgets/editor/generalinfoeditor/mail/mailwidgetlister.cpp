/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mailwidgetlister.h"
#include "mailwidget.h"

#include <KContacts/Addressee>
using namespace Akonadi;

MailWidgetLister::MailWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

MailWidgetLister::~MailWidgetLister() = default;

void MailWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    KContacts::Email::List mailList = contact.emailList();
    if (mailList.isEmpty()) {
        setNumberOfShownWidgetsTo(1);
    } else {
        setNumberOfShownWidgetsTo(mailList.count());
        const QList<QWidget *> widgetList = widgets();
        auto with = widgetList.constBegin();
        auto wEnd = widgetList.constEnd();
        for (int i = 0; with != wEnd; ++with, ++i) {
            auto w = qobject_cast<MailWidget *>(*with);
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
        auto w = qobject_cast<MailWidget *>(widget);
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
        auto w = qobject_cast<MailWidget *>(widget);
        w->setReadOnly(readOnly);
    }
    updateAddRemoveButton();
}

QWidget *MailWidgetLister::createWidget(QWidget *parent)
{
    auto w = new MailWidget(parent);
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
    const bool removeButtonEnabled = numberOfWidget > 1;
    for (QWidget *widget : widgetList) {
        auto w = qobject_cast<MailWidget *>(widget);
        w->updateAddRemoveButton(addButtonEnabled, removeButtonEnabled);
    }
}

#include "moc_mailwidgetlister.cpp"
