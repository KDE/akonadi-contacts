/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi_contact_widgets_private_export.h"
#include <KContacts/Email>
#include <QWidget>
class QToolButton;
namespace Akonadi
{
class PreferredLineEditWidget;
class MailTypeCombobox;
class AKONADI_CONTACT_WIDGETS_TESTS_EXPORT MailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailWidget(QWidget *parent = nullptr);
    ~MailWidget() override;

    void clearWidget();
    void updateAddRemoveButton(bool addButtonEnabled);
    void setMail(const KContacts::Email &email);
    KContacts::Email email();
    void setPreferred(bool b);
    void setReadOnly(bool readOnly);
Q_SIGNALS:
    void addWidget(Akonadi::MailWidget *);
    void removeWidget(Akonadi::MailWidget *);
    void preferredChanged(Akonadi::MailWidget *);

private:
    void slotAddMail();
    void slotRemoveMail();
    void slotPreferredChanged();
    KContacts::Email mEmail;
    QString mOldType;
    PreferredLineEditWidget *mMailEdit = nullptr;
    Akonadi::MailTypeCombobox *mMailType = nullptr;
    QToolButton *mAddButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
};
}
