/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact_export.h"

#include <QVariantMap>

#include <memory>

namespace KContacts
{
class Addressee;
}

namespace Akonadi
{
class Item;
class AbstractContactFormatterPrivate;

/**
 * @short The interface for all contact formatters.
 *
 * This is the interface that can be used to format an Akonadi
 * item with a contact payload or a contact itself as HTML.
 *
 * @see StandardContactFormatter
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT AbstractContactFormatter
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
     * Creates a new abstract contact formatter.
     */
    AbstractContactFormatter();

    /**
     * Destroys the abstract contact formatter.
     */
    virtual ~AbstractContactFormatter();

    /**
     * Sets the @p contact that will be formatted.
     * @param contact contact to be formatted
     */
    void setContact(const KContacts::Addressee &contact);

    /**
     * Returns the contact that will be formatted.
     */
    Q_REQUIRED_RESULT KContacts::Addressee contact() const;

    /**
     * Sets the @p item who's payload will be formatted.
     *
     * @note The payload must be a valid KContacts::Addressee object.
     * @param item item, who's payload will be formatted.
     */
    void setItem(const Akonadi::Item &item);

    /**
     * Returns the item who's payload will be formatted.
     */
    Q_REQUIRED_RESULT Akonadi::Item item() const;

    /**
     * Sets the custom field @p descriptions that will be used.
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
     * @param descriptions list with field descriptions
     */
    void setCustomFieldDescriptions(const QList<QVariantMap> &descriptions);

    /**
     * Returns the custom field descriptions that will be used.
     */
    Q_REQUIRED_RESULT QList<QVariantMap> customFieldDescriptions() const;

    /**
     * This method must be reimplemented to return the contact formatted as HTML
     * according to the requested @p form.
     * @param form how to render the contact into HTML
     */
    virtual QString toHtml(HtmlForm form = SelfcontainedForm) const = 0;

private:
    //@cond PRIVATE
    Q_DISABLE_COPY(AbstractContactFormatter)

    std::unique_ptr<AbstractContactFormatterPrivate> const d;
    //@endcond
};
}
