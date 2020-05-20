/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2020 Laurent Montel <montel.org>

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

#ifndef MESSAGINGWIDGET_H
#define MESSAGINGWIDGET_H

#include <QWidget>

#include "contacteditor_private_export.h"

class QToolButton;

namespace KContacts {
class Impp;
}

namespace ContactEditor {
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
#endif // MESSAGINGWIDGET_H
