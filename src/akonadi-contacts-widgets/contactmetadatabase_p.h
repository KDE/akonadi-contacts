/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <QVariant>

#include <memory>

namespace Akonadi
{
class ContactMetaDataBasePrivate;

/*!
 * \brief A helper class for storing contact specific settings.
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactMetaDataBase
{
public:
    /*!
     * Creates a contact meta data object.
     */
    ContactMetaDataBase();

    /*!
     * Destroys the contact meta data object.
     */
    ~ContactMetaDataBase();

    /*!
     * Loads the meta data from the given \a metaData map.
     *
     * \a metaData The map containing the meta data to load.
     */
    void loadMetaData(const QVariantMap &metaData);

    /*!
     * Stores the meta data to a variant map.
     *
     * \returns A QVariantMap containing the stored meta data.
     */
    [[nodiscard]] QVariantMap storeMetaData() const;

    /*!
     * Sets the display name mode for the contact.
     *
     * \a mode The display name mode to set.
     */
    void setDisplayNameMode(int mode);

    /*!
     * Returns the display name mode for the contact.
     *
     * \returns The display name mode.
     */
    [[nodiscard]] int displayNameMode() const;

    /*!
     * Sets the descriptions of the custom fields for this contact.
     *
     * The description list contains a QVariantMap for each custom field
     * with the following keys:
     *   - key   (string) The identifier of the field
     *   - title (string) The i18n'ed title of the field
     *   - type  (string) The type description of the field
     *     Possible values for type description are
     *       - text
     *       - numeric
     *       - boolean
     *       - date
     *       - time
     *       - datetime
     *
     * \a descriptions The list of custom field descriptions to set.
     */
    void setCustomFieldDescriptions(const QVariantList &descriptions);

    /*!
     * Returns the descriptions of the custom fields for this contact.
     *
     * \returns A list of custom field descriptions.
     */
    [[nodiscard]] QVariantList customFieldDescriptions() const;

private:
    Q_DISABLE_COPY(ContactMetaDataBase)

    std::unique_ptr<ContactMetaDataBasePrivate> const d;
};
}
