/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_private_export.h"
#include <QWidget>
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
    void setReadOnly(bool readOnly);
Q_SIGNALS:
    void addWidget(ContactEditor::PhoneWidget *);
    void removeWidget(ContactEditor::PhoneWidget *);
    void preferredChanged(ContactEditor::PhoneWidget *);

private:
    void slotAddPhone();
    void slotRemovePhone();
    void slotPreferredChanged();
    PreferredLineEditWidget *mPhoneNumberEdit = nullptr;
    QToolButton *mAddButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
    PhoneComboBoxType *mPhoneType = nullptr;
};
}
