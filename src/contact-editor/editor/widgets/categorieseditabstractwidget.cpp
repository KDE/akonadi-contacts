/*
    This file is part of Contact Editor.

    Copyright (c) 2017 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
    Q_UNUSED(contact);
}

void CategoriesEditAbstractWidget::storeContact(KContacts::Addressee &contact) const
{
    Q_UNUSED(contact);
}

void CategoriesEditAbstractWidget::setReadOnly(bool readOnly)
{
    Q_UNUSED(readOnly);
}