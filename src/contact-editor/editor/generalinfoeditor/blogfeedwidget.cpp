/*
    This file is part of Contact Editor.

    Copyright (C) 2018 Laurent Montel <laurent.montel@kdab.com>

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

#include "blogfeedwidget.h"
#include "../utils/utils.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
#include <KLineEdit>
#include <KContacts/Addressee>
using namespace ContactEditor;

BlogfeedWidget::BlogfeedWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setObjectName(QStringLiteral("mainlayout"));
    QLabel *blogFeedLabel = new QLabel(i18n("Blog Feed"), this);
    blogFeedLabel->setObjectName(QStringLiteral("blogFeedLabel"));
    topLayout->addWidget(blogFeedLabel);

    mBlogFeed = new KLineEdit(this);
    mBlogFeed->setTrapReturnKey(true);
    mBlogFeed->setPlaceholderText(i18n("Add a Blog Feed"));
    mBlogFeed->setObjectName(QStringLiteral("blogfeed"));
    topLayout->addWidget(mBlogFeed);
}

BlogfeedWidget::~BlogfeedWidget()
{
}

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
