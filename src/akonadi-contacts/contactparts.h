/*
    SPDX-FileCopyrightText: 2008 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"

namespace Akonadi
{
/**
 * @short Contains predefined part identifiers.
 *
 * This namespace contains identifiers of item parts that are used for
 * handling contact items.
 */
namespace ContactPart
{
/**
 * The part identifier for a small contact version,
 * that contains only name and email addresses.
 * @since 4.2
 */
AKONADI_CONTACT_CORE_EXPORT extern const char Lookup[];

/**
 * The part identifier for all the contact data except
 * images and sounds.
 *
 * @note Use Akonadi::Item::FullPayload to retrieve the
 *       full contact including images and sounds.
 * @since 4.2
 */
AKONADI_CONTACT_CORE_EXPORT extern const char Standard[];
}
}
