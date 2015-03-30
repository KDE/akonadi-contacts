/*
    This file is part of Akonadi Contact.

    Copyright (c) 2013 Laurent Montel <montel@kde.org>
    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#include "kcmakonadicontactactions.h"

#include "contactactionssettings.h"

#include <QVBoxLayout>

#include <kaboutdata.h>
#include <kconfigdialogmanager.h>
#include <kpluginfactory.h>
#include <klocalizedstring.h>

Q_DECLARE_METATYPE(ContactActionsSettings::EnumDialPhoneNumberAction)

K_PLUGIN_FACTORY(KCMAkonadiContactActionsFactory, registerPlugin<KCMAkonadiContactActions>();)

KCMAkonadiContactActions::KCMAkonadiContactActions(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
{
    KAboutData *about = new KAboutData(QStringLiteral("kcmakonadicontactactions"),
                                       i18n("Contact Actions Settings"),
                                       QString(), QString(), KAboutLicense::LGPL,
                                       i18n("(c) 2009 Tobias Koenig"));

    about->addAuthor(i18n("Tobias Koenig"), QString(), QStringLiteral("tokoe@kde.org"));

    setAboutData(about);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QWidget *wdg = new QWidget;
    layout->addWidget(wdg);

    ui.setupUi(wdg);

    mConfigManager = addConfig(ContactActionsSettings::self(), wdg);

    ui.DialPhoneNumberAction->addItem(i18n("Skype"), ContactActionsSettings::UseSkype);
    ui.DialPhoneNumberAction->addItem(i18n("Ekiga"), ContactActionsSettings::UseEkiga);
    ui.DialPhoneNumberAction->addItem(i18n("SflPhone"), ContactActionsSettings::UseSflPhone);
    ui.DialPhoneNumberAction->addItem(i18n("External Application"), ContactActionsSettings::UseExternalPhoneApplication);

    connect(ui.DialPhoneNumberAction, SIGNAL(currentIndexChanged(int)), SLOT(slotDialPhoneNumberActionChanged(int)));

    ui.SendSmsAction->addItem(i18n("Skype"), ContactActionsSettings::UseSkypeSms);
    ui.SendSmsAction->addItem(i18n("SflPhone"), ContactActionsSettings::UseSflPhoneSms);
    ui.SendSmsAction->addItem(i18n("External Application"), ContactActionsSettings::UseExternalSmsApplication);
    connect(ui.SendSmsAction, SIGNAL(currentIndexChanged(int)), SLOT(slotSmsPhoneNumberActionChanged(int)));

    ui.ShowAddressAction->addItem(i18n("Web Browser"), ContactActionsSettings::UseBrowser);
    ui.ShowAddressAction->addItem(i18n("External Application"), ContactActionsSettings::UseExternalAddressApplication);
    ui.ShowAddressAction->addItem(i18n("Google map"), ContactActionsSettings::UseGooglemap);
    ui.ShowAddressAction->addItem(i18n("Map quest"), ContactActionsSettings::UseMapquest);

    connect(ui.ShowAddressAction, SIGNAL(currentIndexChanged(int)), SLOT(slotShowAddressActionChanged(int)));

    load();
}

void KCMAkonadiContactActions::slotShowAddressActionChanged(int value)
{
    ContactActionsSettings::EnumShowAddressAction enumValue = static_cast<ContactActionsSettings::EnumShowAddressAction>(ui.ShowAddressAction->itemData(value).toInt());
    if (enumValue == ContactActionsSettings::UseBrowser) {
        ui.stackedWidget->setCurrentIndex(0);
    } else if (enumValue == ContactActionsSettings::UseExternalAddressApplication) {
        ui.stackedWidget->setCurrentIndex(1);
    } else {
        ui.stackedWidget->setCurrentIndex(2);
    }
    emit changed(true);
}

void KCMAkonadiContactActions::slotSmsPhoneNumberActionChanged(int value)
{
    ContactActionsSettings::EnumSendSmsAction enumValue = static_cast<ContactActionsSettings::EnumSendSmsAction>(ui.SendSmsAction->itemData(value).toInt());
    if (enumValue == ContactActionsSettings::UseExternalSmsApplication) {
        ui.stackedWidget_3->setCurrentIndex(1);
    } else {
        ui.stackedWidget_3->setCurrentIndex(0);
    }
    emit changed(true);
}

void KCMAkonadiContactActions::slotDialPhoneNumberActionChanged(int value)
{
    ContactActionsSettings::EnumDialPhoneNumberAction enumValue = static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ui.DialPhoneNumberAction->itemData(value).toInt());
    if (enumValue == ContactActionsSettings::UseExternalPhoneApplication) {
        ui.stackedWidget_2->setCurrentIndex(1);
    } else {
        ui.stackedWidget_2->setCurrentIndex(0);
    }
    emit changed(true);
}

void KCMAkonadiContactActions::load()
{
    mConfigManager->updateWidgets();

    ContactActionsSettings::EnumShowAddressAction enumValueAddress = static_cast<ContactActionsSettings::EnumShowAddressAction>(ContactActionsSettings::self()->showAddressAction());
    const int indexAddress = ui.ShowAddressAction->findData(enumValueAddress);
    ui.ShowAddressAction->setCurrentIndex(indexAddress);

    ContactActionsSettings::EnumDialPhoneNumberAction enumValue = static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ContactActionsSettings::self()->dialPhoneNumberAction());
    const int index = ui.DialPhoneNumberAction->findData(enumValue);
    ui.DialPhoneNumberAction->setCurrentIndex(index);

    ContactActionsSettings::EnumSendSmsAction enumValueSms = static_cast<ContactActionsSettings::EnumSendSmsAction>(ContactActionsSettings::self()->sendSmsAction());
    const int indexSms = ui.SendSmsAction->findData(enumValueSms);
    ui.SendSmsAction->setCurrentIndex(indexSms);

}

void KCMAkonadiContactActions::save()
{
    mConfigManager->updateSettings();
    ContactActionsSettings::EnumShowAddressAction enumValueAddress = static_cast<ContactActionsSettings::EnumShowAddressAction>(ui.ShowAddressAction->itemData(ui.ShowAddressAction->currentIndex()).toInt());
    ContactActionsSettings::self()->setShowAddressAction(enumValueAddress);

    ContactActionsSettings::EnumDialPhoneNumberAction enumValue = static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ui.DialPhoneNumberAction->itemData(ui.DialPhoneNumberAction->currentIndex()).toInt());
    ContactActionsSettings::self()->setDialPhoneNumberAction(enumValue);

    ContactActionsSettings::EnumSendSmsAction enumValueSms = static_cast<ContactActionsSettings::EnumSendSmsAction>(ui.SendSmsAction->itemData(ui.SendSmsAction->currentIndex()).toInt());
    ContactActionsSettings::self()->setSendSmsAction(enumValueSms);
    ContactActionsSettings::self()->save();
}

void KCMAkonadiContactActions::defaults()
{
    mConfigManager->updateWidgetsDefault();
    const bool bUseDefaults = ContactActionsSettings::self()->useDefaults(true);
    ui.DialPhoneNumberAction->setCurrentIndex(ContactActionsSettings::self()->dialPhoneNumberAction());
    ui.SendSmsAction->setCurrentIndex(ContactActionsSettings::self()->sendSmsAction());
    ui.ShowAddressAction->setCurrentIndex(ContactActionsSettings::self()->showAddressAction());
    ContactActionsSettings::self()->useDefaults(bUseDefaults);
}
#include "kcmakonadicontactactions.moc"
