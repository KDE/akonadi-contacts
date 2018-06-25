/*
    This file is part of Contact Editor.

    Copyright (C) 2017-2018 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef CONTACTEDITOR_CONTACTMETADATABASE_P_H
#define CONTACTEDITOR_CONTACTMETADATABASE_P_H

#include "contacteditor_export.h"
#include <QVariant>

namespace ContactEditor {
/**
 * @short A helper class for storing contact specific settings.
 */
class CONTACTEDITOR_EXPORT ContactMetaDataBase
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
    Q_REQUIRED_RESULT QVariantMap storeMetaData() const;

    /**
     * Sets the mode that is used for the display
     * name of that contact.
     */
    void setDisplayNameMode(int mode);

    /**
     * Returns the mode that is used for the display
     * name of that contact.
     */
    Q_REQUIRED_RESULT int displayNameMode() const;

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
    Q_REQUIRED_RESULT QVariantList customFieldDescriptions() const;

private:
    //@cond PRIVATE
    Q_DISABLE_COPY(ContactMetaDataBase)

    class Private;
    Private *const d;
    //@endcond
};
}

#endif
