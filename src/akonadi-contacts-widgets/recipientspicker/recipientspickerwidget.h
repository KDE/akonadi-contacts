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
    /*!
     * Creates a new recipients picker widget.
     *
     * \a onlyShowEmailWithAddress Whether to show only contacts with email addresses.
     * \a model A custom model for the widget, or nullptr to use the default.
     * \a parent The parent widget.
     */
    explicit RecipientsPickerWidget(bool onlyShowEmailWithAddress, QAbstractItemModel *model, QWidget *parent = nullptr);

    /*!
     * Destroys the recipients picker widget.
     */
    ~RecipientsPickerWidget() override;

    /*!
     * Returns the tree view used by this widget.
     */
    [[nodiscard]] QTreeView *view() const;

    /*!
     * Returns the email address selection widget used by this widget.
     */
    [[nodiscard]] Akonadi::EmailAddressSelectionWidget *emailAddressSelectionWidget() const;

private:
    Akonadi::EmailAddressSelectionWidget *mView = nullptr;
};
}
