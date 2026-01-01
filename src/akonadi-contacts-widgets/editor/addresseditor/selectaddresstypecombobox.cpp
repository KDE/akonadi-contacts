/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "selectaddresstypecombobox.h"
#include "addresstypedialog.h"
#include <QPointer>

#include <KLocalizedString>

using namespace Akonadi;

SelectAddressTypeComboBox::SelectAddressTypeComboBox(QWidget *parent)
    : QComboBox(parent)
{
    const int count = KContacts::Address::typeList().count();
    mTypeList.reserve(count + 2);
    mTypeList.append(-2); // Add initial message
    for (int i = 0; i < count; ++i) {
        mTypeList.append(KContacts::Address::typeList().at(i));
    }
    mTypeList.append(-1); // Others...

    update();

    connect(this, &QComboBox::activated, this, &SelectAddressTypeComboBox::selected);
}

SelectAddressTypeComboBox::~SelectAddressTypeComboBox() = default;

void SelectAddressTypeComboBox::setType(KContacts::Address::Type type)
{
    if (!mTypeList.contains(static_cast<int>(type))) {
        // insert at the end, but before the 'Others...' entry
        mTypeList.insert(mTypeList.count() - 1, static_cast<int>(type));
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
    const int numberOfType(mTypeList.count());
    for (int i = 0; i < numberOfType; ++i) {
        if (mTypeList.at(i) == -1) { // "Other..." entry
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
    QPointer<AddressTypeDialog> dlg = new AddressTypeDialog(mType, this);
    if (dlg->exec()) {
        mType = dlg->type();
        if (!mTypeList.contains(mType)) {
            mTypeList.insert(mTypeList.count() - 1, mType);
        }
    } else {
        setType(KContacts::Address::Type(mTypeList.at(mLastSelected)));
    }
    delete dlg;
    update();
}

#include "moc_selectaddresstypecombobox.cpp"
