/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
