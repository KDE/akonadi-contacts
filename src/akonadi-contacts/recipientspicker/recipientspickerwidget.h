/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"
#include <QWidget>
class QAbstractItemModel;
class QTreeView;
namespace Akonadi
{
class EmailAddressSelectionWidget;
class AKONADI_CONTACT_EXPORT RecipientsPickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecipientsPickerWidget(bool onlyShowEmailWithAddress, QAbstractItemModel *model, QWidget *parent = nullptr);
    ~RecipientsPickerWidget() override;
    Q_REQUIRED_RESULT QTreeView *view() const;

    Q_REQUIRED_RESULT Akonadi::EmailAddressSelectionWidget *emailAddressSelectionWidget() const;

private:
    Akonadi::EmailAddressSelectionWidget *mView = nullptr;
};
}

