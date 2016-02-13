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
#include "../../im/imaddress.h"
#include "../../utils/utils.h"

#include <KContacts/Addressee>
using namespace Akonadi;

MessagingWidgetLister::MessagingWidgetLister(QWidget *parent)
    : KWidgetLister(1, 8, parent)
{
    setNumberOfShownWidgetsTo(widgetsMinimum());
    updateAddRemoveButton();
}

MessagingWidgetLister::~MessagingWidgetLister()
{

}

#if 0
void IMEditWidget::loadContact(const KContacts::Addressee &contact)
{
    mIMEdit->setText(contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-IMAddress")));

    const QStringList customs = contact.customs();

    foreach (const QString &custom, customs) {
        QString app, name, value;
        Akonadi::CustomFieldsListWidget::splitCustomField(custom, app, name, value);

        if (app.startsWith(QStringLiteral("messaging/"))) {
            if (name == QLatin1String("All")) {
                const QString protocol = app;
                const QStringList names = value.split(QChar(0xE000), QString::SkipEmptyParts);

                foreach (const QString &name, names) {
                    mIMAddresses << IMAddress(protocol, name, (name == mIMEdit->text()));
                }
            }
        }
    }
}

void IMEditWidget::storeContact(KContacts::Addressee &contact) const
{
    if (!mIMEdit->text().isEmpty()) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-IMAddress"), mIMEdit->text());
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-IMAddress"));
    }

    // create a map with protocol as key and list of names for that protocol as value
    QMap<QString, QStringList> protocolMap;

    // fill map with all known protocols
    foreach (const QString &protocol, IMProtocols::self()->protocols()) {
        protocolMap.insert(protocol, QStringList());
    }

    // add the configured addresses
    foreach (const IMAddress &address, mIMAddresses) {
        protocolMap[address.protocol()].append(address.name());
    }

    // iterate over this list and modify the contact according
    QMapIterator<QString, QStringList> it(protocolMap);
    while (it.hasNext()) {
        it.next();

        if (!it.value().isEmpty()) {
            contact.insertCustom(it.key(), QStringLiteral("All"), it.value().join(QString(0xE000)));
        } else {
            contact.removeCustom(it.key(), QStringLiteral("All"));
        }
    }
}

#endif

void MessagingWidgetLister::loadContact(const KContacts::Addressee &contact)
{
    IMAddress::List imaddresses;
    const QStringList customs = contact.customs();

    foreach (const QString &custom, customs) {
        QString app, name, value;
        Akonadi::Utils::splitCustomField(custom, app, name, value);

        if (app.startsWith(QStringLiteral("messaging/"))) {
            if (name == QLatin1String("All")) {
                const QString protocol = app;
                const QStringList names = value.split(QChar(0xE000), QString::SkipEmptyParts);

                foreach (const QString &name, names) {
                    //TODO prefered support ?
                    imaddresses << IMAddress(protocol, name, false);
                }
            }
        }
    }
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
    //TODO store really
    //TODO add real support for IM vcard4
}

void MessagingWidgetLister::storeContact(KContacts::Addressee &contact) const
{
    IMAddress::List imaddresses;
    const QList<QWidget *> widgetList = widgets();
    for (QWidget *widget : widgetList) {
        MessagingWidget *w = qobject_cast<MessagingWidget *>(widget);
        imaddresses << w->imAddress();
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
