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

#include "phonewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

using namespace Akonadi;
PhoneWidget::PhoneWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);


    mPhoneNumberEdit = new QLineEdit(this);
    mPhoneNumberEdit->setObjectName(QStringLiteral("phonenumber"));
    layout->addWidget(mPhoneNumberEdit);


    //TODO add icon
    mAddButton = new QToolButton(this);
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &PhoneWidget::slotAddPhone);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    connect(mRemoveButton, &QToolButton::clicked, this, &PhoneWidget::slotRemovePhone);
    //TODO add type.
}

PhoneWidget::~PhoneWidget()
{

}

void PhoneWidget::updateAddRemoveButton(bool addButtonEnabled, bool removeButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
    mRemoveButton->setEnabled(removeButtonEnabled);
}

void PhoneWidget::slotAddPhone()
{
    Q_EMIT addWidget(this);
}

void PhoneWidget::slotRemovePhone()
{
    Q_EMIT removeWidget(this);
}
