/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CUSTOMFIELDMANAGER_P_H
#define CUSTOMFIELDMANAGER_P_H

#include "contacteditor_export.h"
#include "customfields_p.h"

/**
 * @short A class that manages the descriptions of all custom fields with global scope.
 */
class CustomFieldManager
{
public:
    CONTACTEDITOR_EXPORT static void setGlobalCustomFieldDescriptions(const CustomField::List &customFields);
    Q_REQUIRED_RESULT CONTACTEDITOR_EXPORT static CustomField::List globalCustomFieldDescriptions();
};

#endif
