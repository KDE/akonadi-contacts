/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#include "customfieldeditorwidget.h"
#include "../customfieldsmodel.h"
#include <QGridLayout>
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QUuid>
#include <KContacts/Addressee>

using namespace Akonadi;

CustomFieldEditorWidget::CustomFieldEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel(i18n("Title Custom Type"), this);
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
    mAddField->setEnabled(!readOnly);
    mFieldType->setEnabled(!readOnly);
    mUseAllContacts->setEnabled(!readOnly);
}

void CustomFieldEditorWidget::slotFielNameChanged(const QString &text)
{
    mAddField->setEnabled(!text.trimmed().isEmpty());
}

void CustomFieldEditorWidget::slotAddField()
{
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
}
