/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "blogfeedwidget.h"
#include "../utils/utils.h"
#include <KContacts/Addressee>
#include <KLineEdit>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace ContactEditor;

BlogfeedWidget::BlogfeedWidget(QWidget *parent)
    : QWidget(parent)
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setObjectName(QStringLiteral("mainlayout"));
    auto blogFeedLabel = new QLabel(i18n("Blog Feed"), this);
    blogFeedLabel->setObjectName(QStringLiteral("blogFeedLabel"));
    topLayout->addWidget(blogFeedLabel);

    mBlogFeed = new KLineEdit(this);
    mBlogFeed->setTrapReturnKey(true);
    mBlogFeed->setPlaceholderText(i18n("Add a Blog Feed"));
    mBlogFeed->setObjectName(QStringLiteral("blogfeed"));
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
