/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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
#include "contacteditor_private_export.h"
class QToolButton;
namespace KContacts
{
class PhoneNumber;
}
namespace ContactEditor
{
class PreferredLineEditWidget;
class PhoneComboBoxType;
class CONTACTEDITOR_TESTS_EXPORT PhoneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneWidget(QWidget *parent = nullptr);
    ~PhoneWidget();

    void updateAddRemoveButton(bool addButtonEnabled);
    void loadPhone(const KContacts::PhoneNumber &number);
    KContacts::PhoneNumber storePhone();
    void clearWidget();
    void setPreferred(bool b);
Q_SIGNALS:
    void addWidget(PhoneWidget *);
    void removeWidget(PhoneWidget *);
    void preferredChanged(PhoneWidget *);

private Q_SLOTS:
    void slotAddPhone();
    void slotRemovePhone();
    void slotPreferredChanged();

private:
    PreferredLineEditWidget *mPhoneNumberEdit;
    QToolButton *mAddButton;
    QToolButton *mRemoveButton;
    PhoneComboBoxType *mPhoneType;
};
}
#endif // PHONEWIDGET_H
