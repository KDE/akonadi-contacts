/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <QVariant>

#include <memory>

namespace KContacts
{
class ContactGroup;
}

namespace Akonadi
{
class Item;
class AbstractContactGroupFormatterPrivate;

/**
 * @short The interface for all contact group formatters.
 *
 * This is the interface that can be used to format an Akonadi
 * item with a contact group payload or a contact group itself as HTML.
 *
 * @see StandardContactGroupFormatter
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.6
 */
class AKONADI_CONTACT_EXPORT AbstractContactGroupFormatter
{
public:
    /**
     * Describes the form of the HTML that is created.
     */
    enum HtmlForm {
        SelfcontainedForm, ///< Creates a complete HTML document
        EmbeddableForm, ///< Creates a div HTML element that can be embedded.
        UserForm = SelfcontainedForm + 42 ///< Point for extension
    };

    /**
     * Creates a new abstract contact group formatter.
     */
    AbstractContactGroupFormatter();

    /**
     * Destroys the abstract contact group formatter.
     */
    virtual ~AbstractContactGroupFormatter();

    /**
     * Sets the contact @p group that will be formatted.
     */
    void setContactGroup(const KContacts::ContactGroup &group);

    /**
     * Returns the contact group that will be formatted.
     */
    Q_REQUIRED_RESULT KContacts::ContactGroup contactGroup() const;

    /**
     * Sets the @p item who's payload will be formatted.
     *
     * @note The payload must be a valid KContacts::ContactGroup object.
     *
     * @param item item, who's payload will be formatted.
     */
    void setItem(const Akonadi::Item &item);

    /**
     * Returns the item who's payload will be formatted.
     */
    Q_REQUIRED_RESULT Akonadi::Item item() const;

    /**
     * Sets the additional @p fields that will be shown.
     *
     * The fields list contains a QVariantMap for each additional field
     * with the following keys:
     *   - key   (string) The identifier of the field
     *   - title (string) The i18n'ed title of the field
     *   - value (string) The value of the field
     *
     * @param fields additional fields that will be shown
     */
    void setAdditionalFields(const QList<QVariantMap> &fields);

    /**
     * Returns the additional fields that will be shown.
     */
    Q_REQUIRED_RESULT QList<QVariantMap> additionalFields() const;

    /**
     * This method must be reimplemented to return the contact group formatted as HTML
     * according to the requested @p form.
     */
    virtual QString toHtml(HtmlForm form = SelfcontainedForm) const = 0;

private:
    //@cond PRIVATE
    Q_DISABLE_COPY(AbstractContactGroupFormatter)

    std::unique_ptr<AbstractContactGroupFormatterPrivate> const d;
    //@endcond
};
}
