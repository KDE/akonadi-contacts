/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "phonetypedialog.h"
#include <KLocalizedString>

#include <QButtonGroup>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace ContactEditor;

PhoneTypeDialog::PhoneTypeDialog(KContacts::PhoneNumber::Type type, QWidget *parent)
    : QDialog(parent)
    , mType(type)
{
    setWindowTitle(i18nc("@title:window", "Edit Phone Number"));

    auto layout = new QVBoxLayout(this);

    auto buttonLayout = new QGridLayout;
    layout->addLayout(buttonLayout);

    // fill widgets
    mTypeList = KContacts::PhoneNumber::typeList();
    mTypeList.removeAll(KContacts::PhoneNumber::Pref);
    KContacts::PhoneNumber::TypeList::ConstIterator it;
    int row;
    int column;
    int counter;
    row = column = counter = 0;
    mGroup = new QButtonGroup(this);
    mGroup->setExclusive(false);
    for (it = mTypeList.constBegin(); it != mTypeList.constEnd(); ++it, ++counter) {
        auto cb = new QCheckBox(KContacts::PhoneNumber::typeLabel(*it), this);
        cb->setChecked(type & mTypeList[counter]);
        buttonLayout->addWidget(cb, row, column);
        mGroup->addButton(cb);

        column++;
        if (column == 5) {
            column = 0;
            ++row;
        }
    }

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PhoneTypeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PhoneTypeDialog::reject);
}

KContacts::PhoneNumber::Type PhoneTypeDialog::type() const
{
    KContacts::PhoneNumber::Type type = {};

    for (int i = 0; i < mGroup->buttons().count(); ++i) {
        auto box = qobject_cast<QCheckBox *>(mGroup->buttons().at(i));
        if (box && box->isChecked()) {
            type |= mTypeList[i];
        }
    }
    return type;
}
