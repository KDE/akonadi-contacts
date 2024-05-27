/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldeditorwidget.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QUuid>
#include <QVBoxLayout>

using namespace Akonadi;

CustomFieldEditorWidget::CustomFieldEditorWidget(QWidget *parent)
    : QWidget(parent)
    , mFieldName(new KLineEdit(this))
    , mAddField(new QPushButton(i18n("Add Field"), this))
    , mUseAllContacts(new QCheckBox(i18n("Use field for all contacts")))
    , mFieldType(new QComboBox(this))
{
    auto topLayout = new QVBoxLayout(this);
    auto label = new QLabel(i18nc("@label:textbox", "Custom Field Title"), this);
    label->setObjectName(QLatin1StringView("labeltitle"));

    topLayout->addWidget(label);

    auto fieldLayout = new QHBoxLayout;
    topLayout->addLayout(fieldLayout);
    mFieldName->setPlaceholderText(i18n("Add name"));
    mFieldName->setObjectName(QLatin1StringView("fieldname"));
    mFieldName->setTrapReturnKey(true);
    fieldLayout->addWidget(mFieldName);

    mFieldType->setObjectName(QLatin1StringView("fieldtype"));
    fieldLayout->addWidget(mFieldType);
    fillTypes();

    mAddField->setObjectName(QLatin1StringView("addfield"));
    fieldLayout->addWidget(mAddField);
    mAddField->setEnabled(false); // Disable at the beginning
    connect(mAddField, &QPushButton::clicked, this, &CustomFieldEditorWidget::slotAddField);
    connect(mFieldName, &KLineEdit::textChanged, this, &CustomFieldEditorWidget::slotFielNameChanged);

    mUseAllContacts->setObjectName(QLatin1StringView("useallcontact"));
    topLayout->addWidget(mUseAllContacts);
}

CustomFieldEditorWidget::~CustomFieldEditorWidget() = default;

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

    // TODO verify it
    if (field.scope() != CustomField::ExternalScope) {
        // do not change the scope for externally defined custom fields
        field.setScope(mUseAllContacts->isChecked() ? CustomField::GlobalScope : CustomField::LocalScope);
    }
    Q_EMIT addNewField(field);
    mFieldName->clear();
    mFieldType->setCurrentIndex(0);
}

#include "moc_customfieldeditorwidget.cpp"
