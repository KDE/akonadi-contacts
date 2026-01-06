/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

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

/*!
 * \brief The interface for all contact group formatters.
 *
 * This is the interface that can be used to format an Akonadi
 * item with a contact group payload or a contact group itself as HTML.
 *
 * \sa StandardContactGroupFormatter
 * @author Tobias Koenig <tokoe@kde.org>
 * \since 4.6
 */
class AKONADI_CONTACT_CORE_EXPORT AbstractContactGroupFormatter
{
public:
    /*!
     * Describes the form of the HTML that is created.
     */
    enum HtmlForm {
        SelfcontainedForm, ///< Creates a complete HTML document
        EmbeddableForm, ///< Creates a div HTML element that can be embedded.
        UserForm = SelfcontainedForm + 42 ///< Point for extension
    };

    /*!
     * Creates a new abstract contact group formatter.
     */
    AbstractContactGroupFormatter();

    /*!
     * Destroys the abstract contact group formatter.
     */
    virtual ~AbstractContactGroupFormatter();

    /*!
     * Sets the contact \a group that will be formatted.
     */
    void setContactGroup(const KContacts::ContactGroup &group);

    /*!
     * Returns the contact group that will be formatted.
     */
    [[nodiscard]] KContacts::ContactGroup contactGroup() const;

    /*!
     * Sets the \a item who's payload will be formatted.
     *
     * \note The payload must be a valid KContacts::ContactGroup object.
     *
     * \a item item, who's payload will be formatted.
     */
    void setItem(const Akonadi::Item &item);

    /*!
     * Returns the item who's payload will be formatted.
     */
    [[nodiscard]] Akonadi::Item item() const;

    /*!
     * Sets the additional \a fields that will be shown.
     *
     * The fields list contains a QVariantMap for each additional field
     * with the following keys:
     *   - key   (string) The identifier of the field
     *   - title (string) The i18n'ed title of the field
     *   - value (string) The value of the field
     *
     * \a fields additional fields that will be shown
     */
    void setAdditionalFields(const QList<QVariantMap> &fields);

    /*!
     * Returns the additional fields that will be shown.
     */
    [[nodiscard]] QList<QVariantMap> additionalFields() const;

    /*!
     * This method must be reimplemented to return the contact group formatted as HTML
     * according to the requested \a form.
     */
    virtual QString toHtml(HtmlForm form = SelfcontainedForm) const = 0;

private:
    Q_DISABLE_COPY(AbstractContactGroupFormatter)

    std::unique_ptr<AbstractContactGroupFormatterPrivate> const d;
};
}
