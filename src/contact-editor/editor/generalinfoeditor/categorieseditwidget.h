/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <kcontacts/addressee.h>

#include <editor/widgets/categorieseditabstractwidget.h>

/**
 * @short A widget for editing the categories of a contact.
 */
class CategoriesEditWidget : public ContactEditor::CategoriesEditAbstractWidget
{
    Q_OBJECT

public:
    explicit CategoriesEditWidget(QWidget *parent = nullptr);
    ~CategoriesEditWidget() override;

    void loadContact(const KContacts::Addressee &contact) override;
    void storeContact(KContacts::Addressee &contact) const override;

    void setReadOnly(bool readOnly) override;
};

