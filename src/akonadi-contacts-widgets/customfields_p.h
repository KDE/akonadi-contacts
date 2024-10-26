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

/**
 * @short A class that represents non-standard contact fields.
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

    CustomField();
    CustomField(const QString &key, const QString &title, Type type, Scope scope);

    static CustomField fromVariantMap(const QVariantMap &map, Scope scope);

    void setKey(const QString &key);
    QString key() const;

    void setTitle(const QString &title);
    QString title() const;

    void setType(Type type);
    Type type() const;

    void setScope(Scope scope);
    Scope scope() const;

    void setValue(const QString &value);
    QString value() const;

    QVariantMap toVariantMap() const;

    static QString typeToString(Type type);
    static Type stringToType(const QString &type);

private:
    QString mKey;
    QString mTitle;
    Type mType;
    Scope mScope;
    QString mValue;
};
