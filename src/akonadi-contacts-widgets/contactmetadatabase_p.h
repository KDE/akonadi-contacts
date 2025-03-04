/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <QVariant>

#include <memory>

namespace Akonadi
{
class ContactMetaDataBasePrivate;

/**
 * @short A helper class for storing contact specific settings.
 */
class AKONADI_CONTACT_WIDGETS_EXPORT ContactMetaDataBase
{
public:
    /**
     * Creates a contact meta data object.
     */
    ContactMetaDataBase();

    /**
     * Destroys the contact meta data object.
     */
    ~ContactMetaDataBase();

    /**
     * Loads the meta data for the given @p contact.
     */
    void loadMetaData(const QVariantMap &metaData);

    /**
     * Stores the meta data to the given @p contact.
     */
    [[nodiscard]] QVariantMap storeMetaData() const;

    /**
     * Sets the mode that is used for the display
     * name of that contact.
     */
    void setDisplayNameMode(int mode);

    /**
     * Returns the mode that is used for the display
     * name of that contact.
     */
    [[nodiscard]] int displayNameMode() const;

    /**
     * Sets the @p descriptions of the custom fields of that contact.
     * @param descriptions the descriptions to set
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
     */
    void setCustomFieldDescriptions(const QVariantList &descriptions);

    /**
     * Returns the descriptions of the custom fields of the contact.
     */
    [[nodiscard]] QVariantList customFieldDescriptions() const;

private:
    //@cond PRIVATE
    Q_DISABLE_COPY(ContactMetaDataBase)

    std::unique_ptr<ContactMetaDataBasePrivate> const d;
    //@endcond
};
}
