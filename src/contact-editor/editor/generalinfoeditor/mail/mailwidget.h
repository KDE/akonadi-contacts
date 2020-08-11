/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MAILWIDGET_H
#define MAILWIDGET_H

#include <QWidget>
#include <KContacts/Email>
#include "contacteditor_private_export.h"
class QToolButton;
namespace ContactEditor {
class PreferredLineEditWidget;
class MailTypeCombobox;
class CONTACTEDITOR_TESTS_EXPORT MailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailWidget(QWidget *parent = nullptr);
    ~MailWidget();

    void clearWidget();
    void updateAddRemoveButton(bool addButtonEnabled);
    void setMail(const KContacts::Email &email);
    KContacts::Email email();
    void setPreferred(bool b);
    void setReadOnly(bool readOnly);
Q_SIGNALS:
    void addWidget(ContactEditor::MailWidget *);
    void removeWidget(ContactEditor::MailWidget *);
    void preferredChanged(ContactEditor::MailWidget *);

private:
    void slotAddMail();
    void slotRemoveMail();
    void slotPreferredChanged();
    KContacts::Email mEmail;
    QString mOldType;
    PreferredLineEditWidget *mMailEdit = nullptr;
    ContactEditor::MailTypeCombobox *mMailType = nullptr;
    QToolButton *mAddButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
};
}
#endif // MAILWIDGET_H
