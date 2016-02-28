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

#include "phonecomboboxtype.h"
#include "phonetypedialog.h"
#include <KLocalizedString>
#include <QDebug>
#include <autoqpointer_p.h>

using namespace Akonadi;

PhoneComboBoxType::PhoneComboBoxType(QWidget *parent)
    : Akonadi::AkonadiContactComboBox(parent)
    , mType(KContacts::PhoneNumber::Home)
    , mLastSelected(0)
{
    const int nbMax = KContacts::PhoneNumber::typeList().count();
    mTypeList.reserve(nbMax + 1);
    for (int i = 0; i < nbMax; ++i) {
        const KContacts::PhoneNumber::TypeFlag typeflag = KContacts::PhoneNumber::typeList().at(i);
        if (typeflag != KContacts::PhoneNumber::Pref) {
            mTypeList.append(typeflag);
        }
    }

    mTypeList.append(-1);   // Others...

    update();

    connect(this, static_cast<void (PhoneComboBoxType::*)(int)>(&PhoneComboBoxType::activated), this, &PhoneComboBoxType::selected);
}

PhoneComboBoxType::~PhoneComboBoxType()
{
}

void PhoneComboBoxType::setType(KContacts::PhoneNumber::Type type)
{
    if (!mTypeList.contains(type)) {
        mTypeList.insert(mTypeList.at(mTypeList.count() - 1), type);
    }

    mType = type;
    update();
}

KContacts::PhoneNumber::Type PhoneComboBoxType::type() const
{
    return mType;
}

void PhoneComboBoxType::resetToDefault()
{
    setCurrentIndex(0);
}

void PhoneComboBoxType::update()
{
    clear();

    const int typeListCount(mTypeList.count());
    for (int i = 0; i < typeListCount; ++i) {
        if (mTypeList.at(i) == -1) {     // "Other..." entry
            addItem(i18nc("@item:inlistbox Category of contact info field", "Other..."));
        } else {
            addItem(KContacts::PhoneNumber::typeLabel(KContacts::PhoneNumber::Type(mTypeList.at(i))));
        }
    }

    setCurrentIndex(mLastSelected = mTypeList.indexOf(mType));
}

void PhoneComboBoxType::selected(int pos)
{
    if (mTypeList.at(pos) == -1) {
        otherSelected();
    } else {
        mType = KContacts::PhoneNumber::Type(mTypeList.at(pos));
        mLastSelected = pos;
    }
}

void PhoneComboBoxType::otherSelected()
{
    AutoQPointer<Akonadi::PhoneTypeDialog> dlg = new Akonadi::PhoneTypeDialog(mType, this);
    if (dlg->exec()) {
        mType = dlg->type();
        if (!mTypeList.contains(mType)) {
            mTypeList.insert(mTypeList.at(mTypeList.count() - 1), mType);
        }
    } else {
        setType(KContacts::PhoneNumber::Type(mTypeList.at(mLastSelected)));
    }

    update();
}
