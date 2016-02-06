/*
    This file is part of Akonadi Contact.

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

#include "addresstypedialog.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QButtonGroup>
using namespace Akonadi;
AddressTypeDialog::AddressTypeDialog(KContacts::Address::Type type, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    setWindowTitle(i18nc("street/postal", "Edit Address Type"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    okButton->setDefault(true);

    QWidget *page = new QWidget(this);
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setMargin(0);

    QGroupBox *box  = new QGroupBox(i18nc("street/postal", "Address Types"), page);
    mainLayout->addWidget(box);
    layout->addWidget(box);
    mGroup = new QButtonGroup(box);
    mGroup->setExclusive(false);

    QGridLayout *buttonLayout = new QGridLayout(box);

    mTypeList = KContacts::Address::typeList();
    mTypeList.removeAll(KContacts::Address::Pref);

    KContacts::Address::TypeList::ConstIterator it;
    int i = 0;
    int row = 0;
    for (it = mTypeList.constBegin(); it != mTypeList.constEnd(); ++it, ++i) {
        QCheckBox *cb = new QCheckBox(KContacts::Address::typeLabel(*it), box);
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
    for (int i = 0; i < mGroup->buttons().count(); ++i) {
        QCheckBox *box = qobject_cast<QCheckBox *>(mGroup->buttons().at(i));
        if (box && box->isChecked()) {
            type |= mTypeList[i];
        }
    }

    return type;
}
