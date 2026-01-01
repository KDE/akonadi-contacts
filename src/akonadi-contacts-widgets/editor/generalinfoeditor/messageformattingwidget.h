/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi_contact_widgets_private_export.h"
#include <KContacts/Addressee>
#include <QWidget>
class QComboBox;
class QCheckBox;
namespace Akonadi
{
class AKONADI_CONTACT_WIDGETS_TESTS_EXPORT MessageFormattingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageFormattingWidget(QWidget *parent = nullptr);
    ~MessageFormattingWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    QComboBox *mMailPreferFormatting = nullptr;
    QCheckBox *mAllowRemoteContent = nullptr;
};
}
