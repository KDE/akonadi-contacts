/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "generalinfowidget.h"
#include "../widgets/imagewidget.h"
#include "blogfeedwidget.h"
#include "categorieseditwidget.h"
#include "mail/maillistwidget.h"
#include "messageformattingwidget.h"
#include "messaging/messaginglistwidget.h"
#include "namewidget.h"
#include "nicknamewidget.h"
#include "phone/phonelistwidget.h"
#include "web/weblistwidget.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QHBoxLayout>
#include <QVBoxLayout>
using namespace Akonadi;

GeneralInfoWidget::GeneralInfoWidget(QWidget *parent)
    : QWidget(parent)
    , mPhoneListWidget(new PhoneListWidget(this))
    , mWebListWidget(new WebListWidget(this))
    , mMessagingListWidget(new MessagingListWidget(this))
    , mMailListWidget(new MailListWidget(this))
    , mPhotoWidget(new ImageWidget(ImageWidget::Photo, this))
    , mNameWidget(new NameWidget(this))
    , mNickNameWidget(new NicknameWidget(this))
    , mBlogFeedWidget(new BlogfeedWidget(this))
    , mMessageFormattingWidget(new MessageFormattingWidget(this))
{
    auto topLayout = new QHBoxLayout(this);

    auto photoLayout = new QVBoxLayout;
    topLayout->addLayout(photoLayout);
    mPhotoWidget->setObjectName(QLatin1StringView("photowidget"));
    photoLayout->addWidget(mPhotoWidget);
    photoLayout->addStretch(1);

    auto leftLayout = new QVBoxLayout;
    topLayout->addLayout(leftLayout);

    auto rightLayout = new QVBoxLayout;
    topLayout->addLayout(rightLayout);

    mNameWidget->setObjectName(QLatin1StringView("namewidget"));
    leftLayout->addWidget(mNameWidget);

    mNickNameWidget->setObjectName(QLatin1StringView("nicknamewidget"));
    rightLayout->addWidget(mNickNameWidget);

    mPhoneListWidget->setObjectName(QLatin1StringView("phonelistwidget"));
    leftLayout->addWidget(mPhoneListWidget);

    mWebListWidget->setObjectName(QLatin1StringView("weblistwidget"));
    leftLayout->addWidget(mWebListWidget);

    mMessagingListWidget->setObjectName(QLatin1StringView("messaginglistwidget"));
    rightLayout->addWidget(mMessagingListWidget);

    mMailListWidget->setObjectName(QLatin1StringView("maillistwidget"));
    rightLayout->addWidget(mMailListWidget);

    auto categoryWidget = new QWidget(this);
    auto categoryWidgetLayout = new QVBoxLayout(categoryWidget);
    categoryWidgetLayout->setContentsMargins({});
    mCategoriesWidget = new CategoriesEditWidget(parent);

    mCategoriesWidget->setObjectName(QLatin1StringView("categories"));
    categoryWidgetLayout->addWidget(mCategoriesWidget);
    leftLayout->addWidget(categoryWidget);

    mBlogFeedWidget->setObjectName(QLatin1StringView("blogfeed"));
    rightLayout->addWidget(mBlogFeedWidget);

    mMessageFormattingWidget->setObjectName(QLatin1StringView("mMessageFormattingWidget"));
    leftLayout->addWidget(mMessageFormattingWidget);

    leftLayout->addStretch(1);
    rightLayout->addStretch(1);
}

GeneralInfoWidget::~GeneralInfoWidget() = default;

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

#include "moc_generalinfowidget.cpp"
