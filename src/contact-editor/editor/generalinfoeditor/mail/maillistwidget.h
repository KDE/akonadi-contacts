/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MAILLISTWIDGET_H
#define MAILLISTWIDGET_H

#include <QWidget>
namespace KContacts
{
class Addressee;
}
namespace ContactEditor
{
class MailWidgetLister;
class MailListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailListWidget(QWidget *parent = nullptr);
    ~MailListWidget();
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    ContactEditor::MailWidgetLister *mMailWidgetLister = nullptr;
};
}
#endif // MAILLISTWIDGET_H
