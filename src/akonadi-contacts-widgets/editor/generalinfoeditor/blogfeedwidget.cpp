/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "blogfeedwidget.h"
#include <KContacts/Addressee>
#include <KLineEdit>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace Akonadi;

BlogfeedWidget::BlogfeedWidget(QWidget *parent)
    : QWidget(parent)
    , mBlogFeed(new KLineEdit(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setObjectName(QLatin1StringView("mainlayout"));
    auto blogFeedLabel = new QLabel(i18nc("@label:textbox", "Blog Feed"), this);
    blogFeedLabel->setObjectName(QLatin1StringView("blogFeedLabel"));
    topLayout->addWidget(blogFeedLabel);

    mBlogFeed->setTrapReturnKey(true);
    mBlogFeed->setPlaceholderText(i18nc("@info:placeholder", "Add a Blog Feed"));
    mBlogFeed->setObjectName(QLatin1StringView("blogfeed"));
    topLayout->addWidget(mBlogFeed);
}

BlogfeedWidget::~BlogfeedWidget() = default;

void BlogfeedWidget::loadContact(const KContacts::Addressee &contact)
{
    mBlogFeed->setText(contact.blogFeed().url());
}

void BlogfeedWidget::storeContact(KContacts::Addressee &contact) const
{
    contact.setBlogFeed(QUrl(mBlogFeed->text().trimmed()));
}

void BlogfeedWidget::setReadOnly(bool readOnly)
{
    mBlogFeed->setReadOnly(readOnly);
}

#include "moc_blogfeedwidget.cpp"
