/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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


#include "addresstypedialog.h"
#include "selectaddresstypecombobox.h"
#include <KLocalizedString>
#include <autoqpointer_p.h>

SelectAddressTypeComboBox::SelectAddressTypeComboBox(QWidget *parent)
    : KComboBox(parent)
    , mType(KContacts::Address::Home)
    , mLastSelected(0)
{
    const int count = KContacts::Address::typeList().count();
    mTypeList.reserve(count + 2);
    mTypeList.append(-2); // Add initial message
    for (int i = 0; i < count; ++i) {
        mTypeList.append(KContacts::Address::typeList().at(i));
    }
    mTypeList.append(-1);   // Others...

    update();

    connect(this, SIGNAL(activated(int)), this, SLOT(selected(int)));
}

SelectAddressTypeComboBox::~SelectAddressTypeComboBox()
{
}

void SelectAddressTypeComboBox::setType(KContacts::Address::Type type)
{
    if (!mTypeList.contains((int)type)) {
        // insert at the end, but before the 'Others...' entry
        mTypeList.insert(mTypeList.at(mTypeList.count() - 1), (int)type);
    }

    mType = type;
    update();
}

KContacts::Address::Type SelectAddressTypeComboBox::type() const
{
    return mType;
}

void SelectAddressTypeComboBox::update()
{
    bool blocked = signalsBlocked();
    blockSignals(true);

    clear();
    for (int i = 0; i < mTypeList.count(); ++i) {
        if (mTypeList.at(i) == -1) {     // "Other..." entry
            addItem(i18nc("@item:inlistbox Category of contact info field", "Other..."));
        } else if (mTypeList.at(i) == -2) {
            addItem(i18nc("@item:inlistbox Category of contact info field", "New Address Type"));
        } else {
            addItem(KContacts::Address::typeLabel(KContacts::Address::Type(mTypeList.at(i))));
        }
    }

    setCurrentIndex(mLastSelected = mTypeList.indexOf(mType));

    blockSignals(blocked);
}

void SelectAddressTypeComboBox::selected(int pos)
{
    if (mTypeList.at(pos) == -1) {
        otherSelected();
    } else if (mTypeList.at(pos) == -2) {
        return;
    } else {
        mType = KContacts::Address::Type(mTypeList.at(pos));
        mLastSelected = pos;
    }
}

void SelectAddressTypeComboBox::otherSelected()
{
    AutoQPointer<AddressTypeDialog> dlg = new AddressTypeDialog(mType, this);
    if (dlg->exec()) {
        mType = dlg->type();
        if (!mTypeList.contains(mType)) {
            mTypeList.insert(mTypeList.at(mTypeList.count() - 1), mType);
        }
    } else {
        setType(KContacts::Address::Type(mTypeList.at(mLastSelected)));
    }
    update();
}
