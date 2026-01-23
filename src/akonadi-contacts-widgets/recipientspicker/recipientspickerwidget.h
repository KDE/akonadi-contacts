/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <QWidget>
class QAbstractItemModel;
class QTreeView;
namespace Akonadi
{
class EmailAddressSelectionWidget;
/*!
 * \class Akonadi::RecipientsPickerWidget
 * \brief A widget for picking email recipients from contacts.
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/RecipientsPickerWidget
 */
class AKONADI_CONTACT_WIDGETS_EXPORT RecipientsPickerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecipientsPickerWidget(bool onlyShowEmailWithAddress, QAbstractItemModel *model, QWidget *parent = nullptr);
    ~RecipientsPickerWidget() override;
    [[nodiscard]] QTreeView *view() const;

    [[nodiscard]] Akonadi::EmailAddressSelectionWidget *emailAddressSelectionWidget() const;

private:
    Akonadi::EmailAddressSelectionWidget *mView = nullptr;
};
}
