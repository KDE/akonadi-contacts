/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace KContacts
{
class Addressee;
}
namespace AkonadiContactWidgets
{
class MailWidgetLister;
class MailListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailListWidget(QWidget *parent = nullptr);
    ~MailListWidget() override;
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    AkonadiContactWidgets::MailWidgetLister *mMailWidgetLister = nullptr;
};
}