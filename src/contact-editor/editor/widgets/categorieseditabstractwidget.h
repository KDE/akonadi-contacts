/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "contacteditor_export.h"
#include <QWidget>

namespace KContacts
{
class Addressee;
}

namespace ContactEditor
{
class CONTACTEDITOR_EXPORT CategoriesEditAbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CategoriesEditAbstractWidget(QWidget *parent = nullptr);
    ~CategoriesEditAbstractWidget();

    virtual void loadContact(const KContacts::Addressee &contact);
    virtual void storeContact(KContacts::Addressee &contact) const;

    virtual void setReadOnly(bool readOnly);
};
}
