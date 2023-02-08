/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcmakonadicontactactions.h"

#include "contactactionssettings.h"

#include <KAboutData>
#include <KConfigDialogManager>
#include <KLocalizedString>
#include <KPluginFactory>

Q_DECLARE_METATYPE(ContactActionsSettings::EnumDialPhoneNumberAction)

K_PLUGIN_CLASS_WITH_JSON(KCMAkonadiContactActions, "akonadicontact_actions.json")

KCMAkonadiContactActions::KCMAkonadiContactActions(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
{
    auto about = new KAboutData(QStringLiteral("kcmakonadicontactactions"),
                                i18n("Contact Actions Settings"),
                                QString(),
                                QString(),
                                KAboutLicense::LGPL,
                                i18n("(c) 2009 Tobias Koenig"));

    about->addAuthor(i18n("Tobias Koenig"), QString(), QStringLiteral("tokoe@kde.org"));

    setAboutData(about);
    ui.setupUi(this);

    mConfigManager = addConfig(ContactActionsSettings::self(), this);

    ui.DialPhoneNumberAction->addItem(i18n("System Default"), ContactActionsSettings::UseSystemDefault);
    ui.DialPhoneNumberAction->addItem(i18n("Skype"), ContactActionsSettings::UseSkype);
    ui.DialPhoneNumberAction->addItem(i18n("Ekiga"), ContactActionsSettings::UseEkiga);
    ui.DialPhoneNumberAction->addItem(i18n("SflPhone"), ContactActionsSettings::UseSflPhone);
    ui.DialPhoneNumberAction->addItem(i18n("External Application"), ContactActionsSettings::UseExternalPhoneApplication);
    connect(ui.DialPhoneNumberAction, &QComboBox::currentIndexChanged, this, &KCMAkonadiContactActions::slotDialPhoneNumberActionChanged);
    ui.SendSmsAction->addItem(i18n("System Default"), ContactActionsSettings::UseSystemDefaultSms);
    ui.SendSmsAction->addItem(i18n("Skype"), ContactActionsSettings::UseSkypeSms);
    ui.SendSmsAction->addItem(i18n("SflPhone"), ContactActionsSettings::UseSflPhoneSms);
    ui.SendSmsAction->addItem(i18n("External Application"), ContactActionsSettings::UseExternalSmsApplication);
    connect(ui.SendSmsAction, &QComboBox::currentIndexChanged, this, &KCMAkonadiContactActions::slotSmsPhoneNumberActionChanged);

    load();
}

void KCMAkonadiContactActions::slotSmsPhoneNumberActionChanged(int value)
{
    ContactActionsSettings::EnumSendSmsAction enumValue = static_cast<ContactActionsSettings::EnumSendSmsAction>(ui.SendSmsAction->itemData(value).toInt());
    if (enumValue == ContactActionsSettings::UseExternalSmsApplication) {
        ui.smsDetailsStack->setCurrentIndex(1);
    } else {
        ui.smsDetailsStack->setCurrentIndex(0);
    }
    Q_EMIT changed(true);
}

void KCMAkonadiContactActions::slotDialPhoneNumberActionChanged(int value)
{
    ContactActionsSettings::EnumDialPhoneNumberAction enumValue =
        static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ui.DialPhoneNumberAction->itemData(value).toInt());
    if (enumValue == ContactActionsSettings::UseExternalPhoneApplication) {
        ui.phoneDetailsStack->setCurrentIndex(1);
    } else {
        ui.phoneDetailsStack->setCurrentIndex(0);
    }
    Q_EMIT changed(true);
}

void KCMAkonadiContactActions::load()
{
    mConfigManager->updateWidgets();

    auto enumValue = static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ContactActionsSettings::self()->dialPhoneNumberAction());
    const int index = ui.DialPhoneNumberAction->findData(enumValue);
    ui.DialPhoneNumberAction->setCurrentIndex(index);

    auto enumValueSms = static_cast<ContactActionsSettings::EnumSendSmsAction>(ContactActionsSettings::self()->sendSmsAction());
    const int indexSms = ui.SendSmsAction->findData(enumValueSms);
    ui.SendSmsAction->setCurrentIndex(indexSms);
}

void KCMAkonadiContactActions::save()
{
    mConfigManager->updateSettings();
    ContactActionsSettings::EnumDialPhoneNumberAction enumValue =
        static_cast<ContactActionsSettings::EnumDialPhoneNumberAction>(ui.DialPhoneNumberAction->itemData(ui.DialPhoneNumberAction->currentIndex()).toInt());
    ContactActionsSettings::self()->setDialPhoneNumberAction(enumValue);

    ContactActionsSettings::EnumSendSmsAction enumValueSms =
        static_cast<ContactActionsSettings::EnumSendSmsAction>(ui.SendSmsAction->itemData(ui.SendSmsAction->currentIndex()).toInt());
    ContactActionsSettings::self()->setSendSmsAction(enumValueSms);
    ContactActionsSettings::self()->save();
}

void KCMAkonadiContactActions::defaults()
{
    mConfigManager->updateWidgetsDefault();
    const bool bUseDefaults = ContactActionsSettings::self()->useDefaults(true);
    ui.DialPhoneNumberAction->setCurrentIndex(ContactActionsSettings::self()->dialPhoneNumberAction());
    ui.SendSmsAction->setCurrentIndex(ContactActionsSettings::self()->sendSmsAction());
    ContactActionsSettings::self()->useDefaults(bUseDefaults);
}

#include "kcmakonadicontactactions.moc"
