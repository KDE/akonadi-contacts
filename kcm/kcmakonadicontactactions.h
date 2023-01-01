/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "ui_akonadicontactactions.h"
#include <KCModule>

class KConfigDialogManager;

class KCMAkonadiContactActions : public KCModule
{
    Q_OBJECT

public:
    explicit KCMAkonadiContactActions(QWidget *parent, const QVariantList &args);

    void load() override;
    void save() override;
    void defaults() override;

private Q_SLOTS:
    void slotDialPhoneNumberActionChanged(int);
    void slotSmsPhoneNumberActionChanged(int value);

private:
    KConfigDialogManager *mConfigManager = nullptr;
    Ui_AkonadiContactActions ui;
};
