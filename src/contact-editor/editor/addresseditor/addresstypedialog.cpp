/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresstypedialog.h"
#include <KLocalizedString>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace ContactEditor;

AddressTypeDialog::AddressTypeDialog(KContacts::Address::Type type, QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("street/postal", "Edit Address Type"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto page = new QWidget(this);
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);
    auto layout = new QVBoxLayout(page);
    layout->setContentsMargins(0, 0, 0, 0);

    auto box = new QGroupBox(i18nc("street/postal", "Address Types"), page);
    mainLayout->addWidget(box);
    layout->addWidget(box);
    mGroup = new QButtonGroup(box);
    mGroup->setExclusive(false);

    auto buttonLayout = new QGridLayout(box);

    mTypeList = KContacts::Address::typeList();
    mTypeList.removeAll(KContacts::Address::Pref);

    KContacts::Address::TypeList::ConstIterator it;
    int i = 0;
    int row = 0;
    KContacts::Address::TypeList::ConstIterator end(mTypeList.constEnd());
    for (it = mTypeList.constBegin(); it != end; ++it, ++i) {
        auto cb = new QCheckBox(KContacts::Address::typeLabel(*it), box);
        cb->setChecked(type & mTypeList[i]);
        buttonLayout->addWidget(cb, row, i % 3);

        if (i % 3 == 2) {
            ++row;
        }
        mGroup->addButton(cb);
    }
}

AddressTypeDialog::~AddressTypeDialog()
{
}

KContacts::Address::Type AddressTypeDialog::type() const
{
    KContacts::Address::Type type;
    const int numberOfButtons(mGroup->buttons().count());
    for (int i = 0; i < numberOfButtons; ++i) {
        auto box = qobject_cast<QCheckBox *>(mGroup->buttons().at(i));
        if (box && box->isChecked()) {
            type |= mTypeList[i];
        }
    }

    return type;
}
