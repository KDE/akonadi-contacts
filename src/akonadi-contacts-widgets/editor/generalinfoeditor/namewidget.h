/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "displaynameeditwidget.h"
#include <QWidget>

#include <KContacts/Addressee>
class KLineEdit;
class QToolButton;
namespace AkonadiContactWidgets
{
class NameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NameWidget(QWidget *parent = nullptr);
    ~NameWidget() override;

    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

    void setDisplayType(DisplayNameEditWidget::DisplayType type);
    Q_REQUIRED_RESULT DisplayNameEditWidget::DisplayType displayType() const;

Q_SIGNALS:
    void nameChanged(const KContacts::Addressee &contact);

private:
    void slotTextChanged(const QString &text);
    void slotOpenNameEditDialog();
    DisplayNameEditWidget::DisplayType mDisplayType;
    KContacts::Addressee mContact;
    KLineEdit *mNameEdit = nullptr;
    QToolButton *mButtonEdit = nullptr;
};
}
