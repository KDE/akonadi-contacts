/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_private_export.h"
#include <QWidget>
class KLineEdit;
namespace KContacts
{
class Addressee;
}
namespace ContactEditor
{
class CONTACTEDITOR_TESTS_EXPORT BlogfeedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlogfeedWidget(QWidget *parent = nullptr);
    ~BlogfeedWidget();
    void loadContact(const KContacts::Addressee &contact);
    void storeContact(KContacts::Addressee &contact) const;
    void setReadOnly(bool readOnly);

private:
    KLineEdit *mBlogFeed = nullptr;
};
}
