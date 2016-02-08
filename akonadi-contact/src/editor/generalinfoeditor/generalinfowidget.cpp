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

#include "generalinfowidget.h"
#include <QGridLayout>
#include <QLabel>
#include <KLocalizedString>
#include <QLineEdit>
#include <editor/generalinfoeditor/phone/phonelistwidget.h>
using namespace Akonadi;

GeneralInfoWidget::GeneralInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setMargin(0);

    QLabel *nickNameLabel = new QLabel(i18n("Nickname"), this);
    nickNameLabel->setObjectName(QStringLiteral("nicknamelabel"));
    grid->addWidget(nickNameLabel, 0, 2);

    mNickName = new QLineEdit(this);
    mNickName->setPlaceholderText(i18n("Add a Nickname"));
    mNickName->setObjectName(QStringLiteral("nickname"));
    grid->addWidget(mNickName, 1, 2);

    mPhoneListWidget = new PhoneListWidget(this);
    mPhoneListWidget->setObjectName(QStringLiteral("phonelistwidget"));
    grid->addWidget(mPhoneListWidget, 2, 1);
}

GeneralInfoWidget::~GeneralInfoWidget()
{

}
