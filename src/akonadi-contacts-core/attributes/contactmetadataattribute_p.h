/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

#include <Akonadi/Attribute>

#include <QVariant>

#include <memory>

namespace Akonadi
{
class ContactMetaDataAttributePrivate;

/**
 * \brief Attribute to store contact specific meta data.
 *
 * \author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_CORE_EXPORT ContactMetaDataAttribute : public Akonadi::Attribute
{
public:
    /*!
     * Creates a new contact meta data attribute.
     */
    ContactMetaDataAttribute();

    /*!
     * Destroys the contact meta data attribute.
     */
    ~ContactMetaDataAttribute() override;

    /*!
     * Sets the meta \a data.
     */
    void setMetaData(const QVariantMap &data);

    /*!
     * Returns the meta data.
     */
    [[nodiscard]] QVariantMap metaData() const;

    /*!
     * Returns the type of this attribute.
     *
     * \returns The type identifier for this attribute.
     */
    [[nodiscard]] QByteArray type() const override;

    /*!
     * Creates a clone of this attribute.
     *
     * \returns A new instance of ContactMetaDataAttribute with the same data.
     */
    Attribute *clone() const override;

    /*!
     * Returns the serialized representation of this attribute.
     *
     * \returns The serialized data.
     */
    [[nodiscard]] QByteArray serialized() const override;

    /*!
     * Restores the attribute from its serialized \a data representation.
     *
     * \a data The serialized data to restore from.
     */
    void deserialize(const QByteArray &data) override;

private:
    std::unique_ptr<ContactMetaDataAttributePrivate> const d;
};
}
