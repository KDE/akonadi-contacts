/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "contacteditor_private_export.h"

class QToolButton;

namespace KContacts
{
class Impp;
}

namespace ContactEditor
{
class PreferredLineEditWidget;
class ContactEditorComboBox;
class CONTACTEDITOR_TESTS_EXPORT MessagingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessagingWidget(QWidget *parent = nullptr);
    ~MessagingWidget();

    void updateAddRemoveButton(bool addButtonEnabled);
    KContacts::Impp imAddress() const;
    void setIMAddress(const KContacts::Impp &address);
    void setPreferred(bool b);
    void clearWidget();
    void setReadOnly(bool readOnly);
Q_SIGNALS:
    void addWidget(ContactEditor::MessagingWidget *);
    void removeWidget(ContactEditor::MessagingWidget *);
    void preferredChanged(ContactEditor::MessagingWidget *);

private:
    void slotAddMessaging();
    void slotRemoveMessaging();
    void slotPreferredChanged();
    PreferredLineEditWidget *mMessagingEdit = nullptr;
    QToolButton *mAddButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
    ContactEditor::ContactEditorComboBox *mProtocolCombo = nullptr;
};
}
