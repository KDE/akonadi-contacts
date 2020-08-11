/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CONTACTMETADATAAKONADI_P_H
#define CONTACTMETADATAAKONADI_P_H

#include "contactmetadatabase_p.h"
namespace Akonadi {
class Item;

/**
 * @short A helper class for storing contact specific settings.
 */
class ContactMetaDataAkonadi : public ContactEditor::ContactMetaDataBase
{
public:
    /**
     * Creates a contact meta data object.
     */
    ContactMetaDataAkonadi();

    /**
     * Destroys the contact meta data object.
     */
    ~ContactMetaDataAkonadi();

    /**
     * Loads the meta data for the given @p contact.
     */
    void load(const Akonadi::Item &contact);

    /**
     * Stores the meta data to the given @p contact.
     */
    void store(Akonadi::Item &contact);
};
}

#endif
