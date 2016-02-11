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

#ifndef PHONEWIDGET_H
#define PHONEWIDGET_H

#include <QWidget>
class QLineEdit;
class QToolButton;
namespace KContacts
{
class PhoneNumber;
}
namespace Akonadi
{
class PhoneComboBoxType;
class PhoneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneWidget(QWidget *parent = Q_NULLPTR);
    ~PhoneWidget();

    void updateAddRemoveButton(bool addButtonEnabled, bool removeButtonEnabled);
    void loadPhone(const KContacts::PhoneNumber &number);
Q_SIGNALS:
    void addWidget(QWidget *);
    void removeWidget(QWidget *);

private Q_SLOTS:
    void slotAddPhone();
    void slotRemovePhone();

private:
    QLineEdit *mPhoneNumberEdit;
    QToolButton *mAddButton;
    QToolButton *mRemoveButton;
    PhoneComboBoxType *mPhoneType;
};
}
#endif // PHONEWIDGET_H
