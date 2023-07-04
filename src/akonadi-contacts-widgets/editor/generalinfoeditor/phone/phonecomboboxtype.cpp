/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonecomboboxtype.h"
#include "phonetypedialog.h"
#include <KLocalizedString>
#include <QPointer>

using namespace Akonadi;

PhoneComboBoxType::PhoneComboBoxType(QWidget *parent)
    : Akonadi::ContactEditorComboBox(parent)
{
    const int nbMax = KContacts::PhoneNumber::typeList().count();
    mTypeList.reserve(nbMax + 1);
    for (int i = 0; i < nbMax; ++i) {
        const KContacts::PhoneNumber::TypeFlag typeflag = KContacts::PhoneNumber::typeList().at(i);
        if (typeflag != KContacts::PhoneNumber::Pref) {
            mTypeList.append(typeflag);
        }
    }

    mTypeList.append(-1); // Others...

    update();

    connect(this, &PhoneComboBoxType::activated, this, &PhoneComboBoxType::selected);
}

PhoneComboBoxType::~PhoneComboBoxType() = default;

void PhoneComboBoxType::setType(KContacts::PhoneNumber::Type type)
{
    if (static_cast<int>(type) != 0) {
        if (!mTypeList.contains(type)) {
            mTypeList.insert(mTypeList.at(mTypeList.count() - 1), type);
        }
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
        if (mTypeList.at(i) == -1) { // "Other..." entry
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
    QPointer<Akonadi::PhoneTypeDialog> dlg = new Akonadi::PhoneTypeDialog(mType, this);
    if (dlg->exec()) {
        mType = dlg->type();
        if (!mTypeList.contains(mType)) {
            if (static_cast<int>(mType) != 0) {
                mTypeList.insert(mTypeList.at(mTypeList.count() - 1), mType);
            }
        }
    } else {
        setType(KContacts::PhoneNumber::Type(mTypeList.at(mLastSelected)));
    }
    delete dlg;
    update();
}

#include "moc_phonecomboboxtype.cpp"
