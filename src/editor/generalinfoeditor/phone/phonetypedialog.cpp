/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

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

#include "phonetypedialog.h"
#include <KLocalizedString>

#include <QButtonGroup>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Akonadi;

PhoneTypeDialog::PhoneTypeDialog(KContacts::PhoneNumber::Type type, QWidget *parent)
    : QDialog(parent)
    , mType(type)
{
    setWindowTitle(i18n("Edit Phone Number"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    QGridLayout *buttonLayout = new QGridLayout;
    layout->addLayout(buttonLayout);

    // fill widgets
    mTypeList = KContacts::PhoneNumber::typeList();
    mTypeList.removeAll(KContacts::PhoneNumber::Pref);
    KContacts::PhoneNumber::TypeList::ConstIterator it;
    int row, column, counter;
    row = column = counter = 0;
    mGroup = new QButtonGroup(this);
    mGroup->setExclusive(false);
    for (it = mTypeList.constBegin(); it != mTypeList.constEnd(); ++it, ++counter) {
        QCheckBox *cb = new QCheckBox(KContacts::PhoneNumber::typeLabel(*it), this);
        cb->setChecked(type & mTypeList[counter]);
        buttonLayout->addWidget(cb, row, column);
        mGroup->addButton(cb);

        column++;
        if (column == 5) {
            column = 0;
            ++row;
        }
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PhoneTypeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PhoneTypeDialog::reject);
}

KContacts::PhoneNumber::Type PhoneTypeDialog::type() const
{
    KContacts::PhoneNumber::Type type = 0;

    for (int i = 0; i < mGroup->buttons().count(); ++i) {
        QCheckBox *box = qobject_cast<QCheckBox *>(mGroup->buttons().at(i));
        if (box && box->isChecked()) {
            type |= mTypeList[i];
        }
    }
    return type;
}
