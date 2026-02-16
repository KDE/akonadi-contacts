/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include <QList>
#include <QString>
#include <QVariant>
template<typename T>
class QList;

/*!
 * \brief A class that represents non-standard contact fields.
 *
 * There exists three scopes of fields. To the local scope belong all
 * custom fields that are defined by the user and that exists only for one
 * contact. The description for these fields are stored inside ContactMetaData
 * as custom attribute of the Akonadi item that represents the contact.
 * To the global scope belong all custom fields that are defined by the user but
 * shall be available in all contacts of the address book. Their description
 * is stored by CustomFieldManager in $HOME/.kde/share/config/akonadi_contactrc.
 * All other custom fields belong to the external scope, they come with import
 * of contacts from other PIM applications (e.g. further X- entries in vCards).
 * Their description is created on the fly when editing the custom fields.
 *
 * The description of a custom field covers the key, title and type.
 */
class AKONADI_CONTACT_WIDGETS_EXPORT CustomField
{
public:
    using List = QList<CustomField>;

    enum Type {
        TextType,
        NumericType,
        BooleanType,
        DateType,
        TimeType,
        DateTimeType,
        UrlType
    };

    enum Scope {
        LocalScope, ///< Field has been defined by user for one contact
        GlobalScope, ///< Field has been defined by user for all contacts
        ExternalScope ///< Field has been defined by the external data source (e.g. vCard)
    };

    /*!
     * Creates a new custom field.
     */
    CustomField();

    /*!
     * Creates a new custom field with the given parameters.
     *
     * \a key The identifier of the field.
     * \a title The i18n'ed title of the field.
     * \a type The type of the field.
     * \a scope The scope of the field.
     */
    CustomField(const QString &key, const QString &title, Type type, Scope scope);

    /*!
     * Creates a custom field from a variant map representation.
     *
     * \a map The variant map containing field data.
     * \a scope The scope of the field.
     * \returns A CustomField created from the map.
     */
    static CustomField fromVariantMap(const QVariantMap &map, Scope scope);

    /*!
     * Sets the key (identifier) of the field.
     *
     * \a key The identifier to set.
     */
    void setKey(const QString &key);

    /*!
     * Returns the key (identifier) of the field.
     */
    QString key() const;

    /*!
     * Sets the title of the field.
     *
     * \a title The title to set.
     */
    void setTitle(const QString &title);

    /*!
     * Returns the title of the field.
     */
    QString title() const;

    /*!
     * Sets the type of the field.
     *
     * \a type The type to set.
     */
    void setType(Type type);

    /*!
     * Returns the type of the field.
     */
    Type type() const;

    /*!
     * Sets the scope of the field.
     *
     * \a scope The scope to set.
     */
    void setScope(Scope scope);

    /*!
     * Returns the scope of the field.
     */
    Scope scope() const;

    /*!
     * Sets the value of the field.
     *
     * \a value The value to set.
     */
    void setValue(const QString &value);

    /*!
     * Returns the value of the field.
     */
    QString value() const;

    /*!
     * Converts the field to a variant map representation.
     *
     * \returns A QVariantMap representing this field.
     */
    QVariantMap toVariantMap() const;

    /*!
     * Converts a type to its string representation.
     *
     * \a type The type to convert.
     * \returns The string representation of the type.
     */
    static QString typeToString(Type type);

    /*!
     * Converts a string to its corresponding type.
     *
     * \a type The string to convert.
     * \returns The corresponding Type value.
     */
    static Type stringToType(const QString &type);

private:
    QString mKey;
    QString mTitle;
    Type mType;
    Scope mScope;
    QString mValue;
};
