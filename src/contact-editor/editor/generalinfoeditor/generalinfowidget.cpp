/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2020 Laurent Montel <montel.org>

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
#include "blogfeedwidget.h"
#include <QLabel>
#include <KLocalizedString>
#include "phone/phonelistwidget.h"
#include "messaging/messaginglistwidget.h"
#include "mail/maillistwidget.h"
#include "web/weblistwidget.h"
#include "categorieseditwidget.h"
#include "../widgets/imagewidget.h"
#include "messageformattingwidget.h"
#include <KPluginLoader>
#include <KPluginFactory>
#include <QVBoxLayout>
#include <QHBoxLayout>
using namespace ContactEditor;

GeneralInfoWidget::GeneralInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *topLayout = new QHBoxLayout(this);

    QVBoxLayout *photoLayout = new QVBoxLayout;
    topLayout->addLayout(photoLayout);
    mPhotoWidget = new ImageWidget(ImageWidget::Photo);
    mPhotoWidget->setObjectName(QStringLiteral("photowidget"));
    photoLayout->addWidget(mPhotoWidget);
    photoLayout->addStretch(1);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    topLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    topLayout->addLayout(rightLayout);

    mNameWidget = new NameWidget(this);
    mNameWidget->setObjectName(QStringLiteral("namewidget"));
    leftLayout->addWidget(mNameWidget);

    mNickNameWidget = new NicknameWidget(this);
    mNickNameWidget->setObjectName(QStringLiteral("nicknamewidget"));
    rightLayout->addWidget(mNickNameWidget);

    mPhoneListWidget = new PhoneListWidget(this);
    mPhoneListWidget->setObjectName(QStringLiteral("phonelistwidget"));
    leftLayout->addWidget(mPhoneListWidget);

    mWebListWidget = new WebListWidget(this);
    mWebListWidget->setObjectName(QStringLiteral("weblistwidget"));
    leftLayout->addWidget(mWebListWidget);

    mMessagingListWidget = new MessagingListWidget(this);
    mMessagingListWidget->setObjectName(QStringLiteral("messaginglistwidget"));
    rightLayout->addWidget(mMessagingListWidget);

    mMailListWidget = new MailListWidget(this);
    mMailListWidget->setObjectName(QStringLiteral("maillistwidget"));
    rightLayout->addWidget(mMailListWidget);

    QWidget *categoryWidget = new QWidget(this);
    QVBoxLayout *categoryWidgetLayout = new QVBoxLayout(categoryWidget);
    categoryWidgetLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel(i18n("Tags"), this);
    label->setObjectName(QStringLiteral("categorylabel"));
    categoryWidgetLayout->addWidget(label);

    KPluginLoader loader(QStringLiteral("akonadi/contacts/plugins/categorieseditwidgetplugin"));
    KPluginFactory *factory = loader.factory();
    if (factory) {
        mCategoriesWidget = factory->create<ContactEditor::CategoriesEditAbstractWidget>(parent);
    } else {
        mCategoriesWidget = new CategoriesEditWidget(parent);
        label->setVisible(false);
    }
    mCategoriesWidget->setObjectName(QStringLiteral("categories"));
    categoryWidgetLayout->addWidget(mCategoriesWidget);
    leftLayout->addWidget(categoryWidget);

    mBlogFeedWidget = new BlogfeedWidget(this);
    mBlogFeedWidget->setObjectName(QStringLiteral("blogfeed"));
    rightLayout->addWidget(mBlogFeedWidget);

    mMessageFormattingWidget = new MessageFormattingWidget(this);
    mMessageFormattingWidget->setObjectName(QStringLiteral("mMessageFormattingWidget"));
    leftLayout->addWidget(mMessageFormattingWidget);

    leftLayout->addStretch(1);
    rightLayout->addStretch(1);
}

GeneralInfoWidget::~GeneralInfoWidget()
{
}

void GeneralInfoWidget::setDisplayType(DisplayNameEditWidget::DisplayType type)
{
    mNameWidget->setDisplayType(type);
}

DisplayNameEditWidget::DisplayType GeneralInfoWidget::displayType() const
{
    return mNameWidget->displayType();
}

void GeneralInfoWidget::loadContact(const KContacts::Addressee &contact)
{
    mPhoneListWidget->loadContact(contact);
    mWebListWidget->loadContact(contact);
    mMessagingListWidget->loadContact(contact);
    mMailListWidget->loadContact(contact);
    mNameWidget->loadContact(contact);
    mNickNameWidget->loadContact(contact);
    mBlogFeedWidget->loadContact(contact);
    mPhotoWidget->loadContact(contact);
    mCategoriesWidget->loadContact(contact);
    mMessageFormattingWidget->loadContact(contact);
}

void GeneralInfoWidget::storeContact(KContacts::Addressee &contact) const
{
    mPhoneListWidget->storeContact(contact);
    mWebListWidget->storeContact(contact);
    mMessagingListWidget->storeContact(contact);
    mMailListWidget->storeContact(contact);
    mNameWidget->storeContact(contact);
    mNickNameWidget->storeContact(contact);
    mBlogFeedWidget->storeContact(contact);
    mPhotoWidget->storeContact(contact);
    mCategoriesWidget->storeContact(contact);
    mMessageFormattingWidget->storeContact(contact);
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
    mMessageFormattingWidget->setReadOnly(readOnly);
    mBlogFeedWidget->setReadOnly(readOnly);
}
