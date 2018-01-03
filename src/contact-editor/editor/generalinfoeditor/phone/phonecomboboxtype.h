/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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

#ifndef PHONECOMBOBOXTYPE_H
#define PHONECOMBOBOXTYPE_H

#include <editor/widgets/contacteditorcombobox.h>
#include <kcontacts/addressee.h>
#include "contacteditor_private_export.h"
namespace ContactEditor {
/**
 * @short A combobox to select a phone number type.
 */
class CONTACTEDITOR_TESTS_EXPORT PhoneComboBoxType : public ContactEditor::ContactEditorComboBox
{
    Q_OBJECT

public:
    /**
     * Creates a phone type combo.
     *
     * @param parent The parent widget.
     */
    explicit PhoneComboBoxType(QWidget *parent = nullptr);

    /**
     * Destroys the phone type combo.
     */
    ~PhoneComboBoxType();

    /**
     * Sets the phone number @p type that shall be selected.
     */
    void setType(KContacts::PhoneNumber::Type type);

    /**
     * Returns the selected phone number type.
     */
    KContacts::PhoneNumber::Type type() const;

    void resetToDefault();
private:
    void selected(int);
    void otherSelected();
    void update();
    KContacts::PhoneNumber::Type mType;
    int mLastSelected;
    QList<int> mTypeList;
};
}
#endif
