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

#ifndef ADDRESSTYPEDIALOG_H
#define ADDRESSTYPEDIALOG_H

#include <QDialog>
#include <KContacts/Address>

class QButtonGroup;

namespace ContactEditor {
/**
 * Dialog for creating a new address types.
 *
 * @note This dialog is only used by AddressTypeCombo.
 */
class AddressTypeDialog : public QDialog
{
    Q_OBJECT
public:
    AddressTypeDialog(KContacts::Address::Type type, QWidget *parent);
    ~AddressTypeDialog();

    KContacts::Address::Type type() const;

private:
    QButtonGroup *mGroup = nullptr;

    KContacts::Address::TypeList mTypeList;
};
}

#endif // ADDRESSTYPEDIALOG_H