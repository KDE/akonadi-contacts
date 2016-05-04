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

#ifndef GENERALINFOWIDGET_H
#define GENERALINFOWIDGET_H

#include <QWidget>
class ImageWidget;
class CategoriesEditWidget;
namespace KContacts
{
class Addressee;
}

namespace Akonadi
{
class PhoneListWidget;
class WebListWidget;
class MessagingListWidget;
class MailListWidget;
class NameWidget;
class NicknameWidget;
class GeneralInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralInfoWidget(QWidget *parent = Q_NULLPTR);
    ~GeneralInfoWidget();

    void loadContact(const KContacts::Addressee &contact);

    void storeContact(KContacts::Addressee &contact) const;

    void setReadOnly(bool readOnly);
private:
    PhoneListWidget *mPhoneListWidget;
    WebListWidget *mWebListWidget;
    MessagingListWidget *mMessagingListWidget;
    MailListWidget *mMailListWidget;
    ImageWidget *mPhotoWidget;
    NameWidget *mNameWidget;
    NicknameWidget *mNickNameWidget;
    CategoriesEditWidget *mCategoriesWidget;
};
}
#endif // GENERALINFOWIDGET_H
