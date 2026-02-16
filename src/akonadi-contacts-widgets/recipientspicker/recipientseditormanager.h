/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <QObject>

namespace Akonadi
{
class EmailAddressSelectionModel;
/*!
 * \class Akonadi::RecipientsEditorManager
 * \brief Manager for recipients editor model.
 * \inmodule AkonadiContactWidgets
 * \inheaderfile Akonadi/RecipientsEditorManager
 */
class AKONADI_CONTACT_WIDGETS_EXPORT RecipientsEditorManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Creates a new recipients editor manager.
     *
     * \a parent The parent object.
     */
    explicit RecipientsEditorManager(QObject *parent = nullptr);

    /*!
     * Destroys the recipients editor manager.
     */
    ~RecipientsEditorManager() override;

    /*!
     * Returns the singleton instance of the recipients editor manager.
     */
    static RecipientsEditorManager *self();

    /*!
     * Returns the email address selection model.
     *
     * \returns The model for email address selection.
     */
    [[nodiscard]] Akonadi::EmailAddressSelectionModel *model();

private:
    Akonadi::EmailAddressSelectionModel *const mModel;
};
}
