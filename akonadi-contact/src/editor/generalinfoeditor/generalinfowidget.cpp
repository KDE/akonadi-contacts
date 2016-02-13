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
#include "namewidget.h"
#include "nicknamewidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <KLocalizedString>
#include <QLineEdit>
#include <editor/generalinfoeditor/phone/phonelistwidget.h>
#include <editor/generalinfoeditor/messaging/messaginglistwidget.h>
#include <editor/generalinfoeditor/mail/maillistwidget.h>
#include <editor/generalinfoeditor/web/weblistwidget.h>
#include "categorieseditwidget.h"
#include <editor/imagewidget.h>

using namespace Akonadi;

GeneralInfoWidget::GeneralInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);

    mPhotoWidget = new ImageWidget(ImageWidget::Photo);
    mPhotoWidget->setObjectName(QStringLiteral("photowidget"));
    grid->addWidget(mPhotoWidget, 0, 0, 4, 1);

    mNameWidget = new NameWidget(this);
    mNameWidget->setObjectName(QStringLiteral("namewidget"));
    grid->addWidget(mNameWidget, 0, 1);

    mNickNameWidget = new NicknameWidget(this);
    mNickNameWidget->setObjectName(QStringLiteral("nicknamewidget"));
    grid->addWidget(mNickNameWidget, 0, 2);

    mPhoneListWidget = new PhoneListWidget(this);
    mPhoneListWidget->setObjectName(QStringLiteral("phonelistwidget"));
    grid->addWidget(mPhoneListWidget, 1, 1);

    mWebListWidget = new WebListWidget(this);
    mWebListWidget->setObjectName(QStringLiteral("weblistwidget"));
    grid->addWidget(mWebListWidget, 2, 1);

    mMessagingListWidget = new MessagingListWidget(this);
    mMessagingListWidget->setObjectName(QStringLiteral("messaginglistwidget"));
    grid->addWidget(mMessagingListWidget, 2, 2);


    mMailListWidget = new MailListWidget(this);
    mMailListWidget->setObjectName(QStringLiteral("maillistwidget"));
    grid->addWidget(mMailListWidget, 1, 2);

    QWidget *categoryWidget = new QWidget(this);
    QVBoxLayout *categoryWidgetLayout = new QVBoxLayout(categoryWidget);
    categoryWidgetLayout->setMargin(0);
    QLabel *label = new QLabel(i18n("Tags"), this);
    label->setObjectName(QStringLiteral("categorylabel"));
    categoryWidgetLayout->addWidget(label);

    mCategoriesWidget = new CategoriesEditWidget(this);
    mCategoriesWidget->setObjectName(QStringLiteral("categories"));
    categoryWidgetLayout->addWidget(mCategoriesWidget);
    grid->addWidget(categoryWidget, 3, 1);

    grid->setRowStretch(4, 1);
}

GeneralInfoWidget::~GeneralInfoWidget()
{

}

void GeneralInfoWidget::loadContact(const KContacts::Addressee &contact)
{
    mPhoneListWidget->loadContact(contact);
    mWebListWidget->loadContact(contact);
    mMessagingListWidget->loadContact(contact);
    mMailListWidget->loadContact(contact);
    mNameWidget->loadContact(contact);
    mNickNameWidget->loadContact(contact);
    mPhotoWidget->loadContact(contact);
    mCategoriesWidget->loadContact(contact);
}

void GeneralInfoWidget::storeContact(KContacts::Addressee &contact) const
{
    qDebug()<<" void GeneralInfoWidget::storeContact(KContacts::Addressee &contact) const";
    mPhoneListWidget->storeContact(contact);
    mWebListWidget->storeContact(contact);
    mMessagingListWidget->storeContact(contact);
    mMailListWidget->storeContact(contact);
    mNameWidget->storeContact(contact);
    mNickNameWidget->storeContact(contact);
    mPhotoWidget->storeContact(contact);
    mCategoriesWidget->storeContact(contact);
}

void GeneralInfoWidget::setReadOnly(bool readOnly)
{
    mPhoneListWidget->setReadOnly(readOnly);
    mWebListWidget->setReadOnly(readOnly);
    mMessagingListWidget->setReadOnly(readOnly);
    mMailListWidget->setReadOnly(readOnly);
    mNameWidget->setReadOnly(readOnly);
    mNickNameWidget->setReadOnly(readOnly);
    mPhotoWidget->setReadOnly(readOnly);
    mCategoriesWidget->setReadOnly(readOnly);
}
