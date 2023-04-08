/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldswidget.h"
#include "customfieldeditorwidget.h"
#include "customfieldslistwidget.h"

#include <QVBoxLayout>

using namespace ContactEditor;

CustomFieldsWidget::CustomFieldsWidget(QWidget *parent)
    : QWidget(parent)
    , mCustomFieldEditorWidget(new ContactEditor::CustomFieldEditorWidget(this))
    , mCustomFieldsListWidget(new ContactEditor::CustomFieldsListWidget(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    mCustomFieldEditorWidget->setObjectName(QStringLiteral("customfieldeditorwidget"));
    topLayout->addWidget(mCustomFieldEditorWidget);

    mCustomFieldsListWidget->setObjectName(QStringLiteral("customfieldslistwidget"));
    topLayout->addWidget(mCustomFieldsListWidget);

    connect(mCustomFieldEditorWidget, &CustomFieldEditorWidget::addNewField, mCustomFieldsListWidget, &CustomFieldsListWidget::slotAddNewField);
}

CustomFieldsWidget::~CustomFieldsWidget() = default;

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

#include "moc_customfieldswidget.cpp"
