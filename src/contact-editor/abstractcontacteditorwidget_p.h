/*
    This file is part of Contact Editor.

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

#ifndef AKONADI_ABSTRACTCONTACTEDITORWIDGET_P_H
#define AKONADI_ABSTRACTCONTACTEDITORWIDGET_P_H

#include <QWidget>

namespace KContacts
{
class Addressee;
}

namespace ContactEditor
{

class ContactMetaDataBase;

class AbstractContactEditorWidget : public QWidget
{
public:
    /**
     * Creates a new abstract contact editor widget.
     *
     * @param parent The parent widget.
     */
    explicit AbstractContactEditorWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
    }

    /**
     * Destroys the abstract contact editor widget.
     */
    ~AbstractContactEditorWidget()
    {
    }

    /**
     * @param contact loads the given contact into the editor widget
     */
    virtual void loadContact(const KContacts::Addressee &contact, const ContactEditor::ContactMetaDataBase &metaData) = 0;

    /**
     * @param contact store the given contact into the editor widget
     */
    virtual void storeContact(KContacts::Addressee &contact, ContactEditor::ContactMetaDataBase &metaData) const = 0;

    /**
     * @param readOnly set read-only mode
     */
    virtual void setReadOnly(bool readOnly) = 0;
};

}

#endif
