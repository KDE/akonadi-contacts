/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_CONTACTMETADATAATTRIBUTE_P_H
#define AKONADI_CONTACTMETADATAATTRIBUTE_P_H

#include "akonadi-contact_export.h"

#include <attribute.h>

#include <QVariant>

namespace Akonadi {
/**
 * @short Attribute to store contact specific meta data.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_EXPORT ContactMetaDataAttribute : public Akonadi::Attribute
{
public:
    /**
     * Creates a new contact meta data attribute.
     */
    ContactMetaDataAttribute();

    /**
     * Destroys the contact meta data attribute.
     */
    ~ContactMetaDataAttribute() override;

    /**
     * Sets the meta @p data.
     */
    void setMetaData(const QVariantMap &data);

    /**
     * Returns the meta data.
     */
    QVariantMap metaData() const;

    QByteArray type() const override;
    Attribute *clone() const override;
    QByteArray serialized() const override;
    void deserialize(const QByteArray &data) override;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
