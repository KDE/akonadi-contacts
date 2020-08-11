/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldeditorwidget.h"
#include "customfieldsmodel.h"
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QUuid>
#include <KContacts/Addressee>
#include <QVBoxLayout>

using namespace ContactEditor;

CustomFieldEditorWidget::CustomFieldEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel(i18n("Custom Field Title"), this);
    label->setObjectName(QStringLiteral("labeltitle"));

    topLayout->addWidget(label);

    QHBoxLayout *fieldLayout = new QHBoxLayout;
    topLayout->addLayout(fieldLayout);
    mFieldName = new QLineEdit(this);
    mFieldName->setPlaceholderText(i18n("Add name"));
    mFieldName->setObjectName(QStringLiteral("fieldname"));
    fieldLayout->addWidget(mFieldName);

    mFieldType = new QComboBox(this);
    mFieldType->setObjectName(QStringLiteral("fieldtype"));
    fieldLayout->addWidget(mFieldType);
    fillTypes();

    mAddField = new QPushButton(i18n("Add Field"), this);
    mAddField->setObjectName(QStringLiteral("addfield"));
    fieldLayout->addWidget(mAddField);
    mAddField->setEnabled(false); //Disable at the beginning
    connect(mAddField, &QPushButton::clicked, this, &CustomFieldEditorWidget::slotAddField);
    connect(mFieldName, &QLineEdit::textChanged, this, &CustomFieldEditorWidget::slotFielNameChanged);

    mUseAllContacts = new QCheckBox(i18n("Use field for all contacts"));
    mUseAllContacts->setObjectName(QStringLiteral("useallcontact"));
    topLayout->addWidget(mUseAllContacts);
}

CustomFieldEditorWidget::~CustomFieldEditorWidget()
{
}

void CustomFieldEditorWidget::fillTypes()
{
    mFieldType->addItem(i18n("Text"), CustomField::TextType);
    mFieldType->addItem(i18n("Numeric"), CustomField::NumericType);
    mFieldType->addItem(i18n("Boolean"), CustomField::BooleanType);
    mFieldType->addItem(i18n("Date"), CustomField::DateType);
    mFieldType->addItem(i18n("Time"), CustomField::TimeType);
    mFieldType->addItem(i18n("DateTime"), CustomField::DateTimeType);
    mFieldType->addItem(i18n("Url"), CustomField::UrlType);
}

void CustomFieldEditorWidget::setReadOnly(bool readOnly)
{
    mFieldName->setReadOnly(readOnly);
    mAddField->setEnabled(!readOnly && !mFieldName->text().trimmed().isEmpty());
    mFieldType->setEnabled(!readOnly);
    mUseAllContacts->setEnabled(!readOnly);
}

void CustomFieldEditorWidget::slotFielNameChanged(const QString &text)
{
    mAddField->setEnabled(!text.trimmed().isEmpty());
}

void CustomFieldEditorWidget::slotAddField()
{
    if (mFieldName->text().trimmed().isEmpty()) {
        return;
    }
    CustomField field;
    // We use a Uuid as default key, so we won't have any duplicated keys,
    // the user can still change it to something else in the editor dialog.
    // Since the key only allows [A-Za-z0-9\-]*, we have to remove the curly
    // braces as well.
    QString key = QUuid::createUuid().toString();
    key.remove(QLatin1Char('{'));
    key.remove(QLatin1Char('}'));

    field.setKey(key);
    field.setTitle(mFieldName->text());
    field.setType(static_cast<CustomField::Type>(mFieldType->itemData(mFieldType->currentIndex()).toInt()));

    //TODO verify it
    if (field.scope() != CustomField::ExternalScope) {
        // do not change the scope for externally defined custom fields
        field.setScope(mUseAllContacts->isChecked() ? CustomField::GlobalScope : CustomField::LocalScope);
    }
    Q_EMIT addNewField(field);
    mFieldName->clear();
    mFieldType->setCurrentIndex(0);
}
