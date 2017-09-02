/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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

#include "customfieldswidget.h"
#include "customfieldeditorwidget.h"
#include "customfieldslistwidget.h"

#include <QVBoxLayout>

using namespace ContactEditor;

CustomFieldsWidget::CustomFieldsWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setMargin(0);
    mCustomFieldEditorWidget = new ContactEditor::CustomFieldEditorWidget(this);
    mCustomFieldEditorWidget->setObjectName(QStringLiteral("customfieldeditorwidget"));
    topLayout->addWidget(mCustomFieldEditorWidget);

    mCustomFieldsListWidget = new ContactEditor::CustomFieldsListWidget(this);
    mCustomFieldsListWidget->setObjectName(QStringLiteral("customfieldslistwidget"));
    topLayout->addWidget(mCustomFieldsListWidget);

    connect(mCustomFieldEditorWidget, &CustomFieldEditorWidget::addNewField, mCustomFieldsListWidget, &CustomFieldsListWidget::slotAddNewField);
}

CustomFieldsWidget::~CustomFieldsWidget()
{
}

void CustomFieldsWidget::loadContact(const KContacts::Addressee &contact)
{
    mCustomFieldsListWidget->loadContact(contact);
}

void CustomFieldsWidget::storeContact(KContacts::Addressee &contact) const
{
    mCustomFieldsListWidget->storeContact(contact);
}

void CustomFieldsWidget::setReadOnly(bool readOnly)
{
    mCustomFieldEditorWidget->setReadOnly(readOnly);
    mCustomFieldsListWidget->setReadOnly(readOnly);
}

void CustomFieldsWidget::setLocalCustomFieldDescriptions(const QVariantList &descriptions)
{
    mCustomFieldsListWidget->setLocalCustomFieldDescriptions(descriptions);
}

QVariantList CustomFieldsWidget::localCustomFieldDescriptions() const
{
    return mCustomFieldsListWidget->localCustomFieldDescriptions();
}
