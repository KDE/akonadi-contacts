/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-widgets_export.h"
#include "customfields_p.h"

/*!
 * \brief A class that manages the descriptions of all custom fields with global scope.
 */
class CustomFieldManager
{
public:
    AKONADI_CONTACT_WIDGETS_EXPORT static void setGlobalCustomFieldDescriptions(const CustomField::List &customFields);
    [[nodiscard]] AKONADI_CONTACT_WIDGETS_EXPORT static CustomField::List globalCustomFieldDescriptions();
};
