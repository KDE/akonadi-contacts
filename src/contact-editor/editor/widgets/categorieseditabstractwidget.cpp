/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorieseditabstractwidget.h"

using namespace ContactEditor;
CategoriesEditAbstractWidget::CategoriesEditAbstractWidget(QWidget *parent)
    : QWidget(parent)
{
}

CategoriesEditAbstractWidget::~CategoriesEditAbstractWidget()
{
}

void CategoriesEditAbstractWidget::loadContact(const KContacts::Addressee &contact)
{
    Q_UNUSED(contact)
}

void CategoriesEditAbstractWidget::storeContact(KContacts::Addressee &contact) const
{
    Q_UNUSED(contact)
}

void CategoriesEditAbstractWidget::setReadOnly(bool readOnly)
{
    Q_UNUSED(readOnly)
}
