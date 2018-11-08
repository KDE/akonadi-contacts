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

#ifndef BLOGFEEDWIDGET_H
#define BLOGFEEDWIDGET_H

#include <QWidget>
#include "contacteditor_private_export.h"
class KLineEdit;
namespace KContacts {
class Addressee;
}
namespace ContactEditor {
class CONTACTEDITOR_TESTS_EXPORT BlogfeedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlogfeedWidget(QWidget *parent = nullptr);
    ~BlogfeedWidget();
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);
private:
    KLineEdit *mBlogFeed = nullptr;
};
}
#endif // BLOGFEEDWIDGET_H
