/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "categorieseditwidget.h"

#include <QHBoxLayout>

CategoriesEditWidget::CategoriesEditWidget(QWidget *parent)
    : ContactEditor::CategoriesEditAbstractWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
}

CategoriesEditWidget::~CategoriesEditWidget()
{
}

void CategoriesEditWidget::setReadOnly(bool readOnly)
{
    Q_UNUSED(readOnly)
}

void CategoriesEditWidget::loadContact(const KContacts::Addressee &contact)
{
    Q_UNUSED(contact)
}

void CategoriesEditWidget::storeContact(KContacts::Addressee &contact) const
{
    Q_UNUSED(contact)
}
