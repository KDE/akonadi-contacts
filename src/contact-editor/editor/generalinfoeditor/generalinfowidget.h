/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef GENERALINFOWIDGET_H
#define GENERALINFOWIDGET_H

#include "displaynameeditwidget.h"
#include <QWidget>
class ImageWidget;
namespace KContacts
{
class Addressee;
}

namespace ContactEditor
{
class CategoriesEditAbstractWidget;
class PhoneListWidget;
class WebListWidget;
class MessagingListWidget;
class MailListWidget;
class NameWidget;
class NicknameWidget;
class MessageFormattingWidget;
class BlogfeedWidget;
class GeneralInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralInfoWidget(QWidget *parent = nullptr);
    ~GeneralInfoWidget();

    void loadContact(const KContacts::Addressee &contact);

    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);
    void setDisplayType(DisplayNameEditWidget::DisplayType type);
    Q_REQUIRED_RESULT DisplayNameEditWidget::DisplayType displayType() const;

private:
    PhoneListWidget *mPhoneListWidget = nullptr;
    WebListWidget *mWebListWidget = nullptr;
    MessagingListWidget *mMessagingListWidget = nullptr;
    MailListWidget *mMailListWidget = nullptr;
    ImageWidget *mPhotoWidget = nullptr;
    NameWidget *mNameWidget = nullptr;
    NicknameWidget *mNickNameWidget = nullptr;
    BlogfeedWidget *mBlogFeedWidget = nullptr;
    ContactEditor::CategoriesEditAbstractWidget *mCategoriesWidget = nullptr;
    MessageFormattingWidget *mMessageFormattingWidget = nullptr;
};
}
#endif // GENERALINFOWIDGET_H
