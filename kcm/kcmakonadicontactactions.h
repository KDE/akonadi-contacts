/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KCMAKONADICONTACTACTIONS_H
#define KCMAKONADICONTACTACTIONS_H

#include "ui_akonadicontactactions.h"
#include <KCModule>

class KConfigDialogManager;

class KCMAkonadiContactActions : public KCModule
{
    Q_OBJECT

public:
    KCMAkonadiContactActions(QWidget *parent, const QVariantList &args);

    void load() override;
    void save() override;
    void defaults() override;

private Q_SLOTS:
    void slotDialPhoneNumberActionChanged(int);
    void slotSmsPhoneNumberActionChanged(int value);
    void slotShowAddressActionChanged(int value);

private:
    KConfigDialogManager *mConfigManager = nullptr;
    Ui_AkonadiContactActions ui;
};

#endif
