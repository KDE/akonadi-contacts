/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#include "customfieldeditordialog.h"

#include <QDialog>

#include <QComboBox>
#include <QLineEdit>
#include <KLocalizedString>

#include <QCheckBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QRegExpValidator>
#include <QPushButton>

CustomFieldEditorDialog::CustomFieldEditorDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Edit Custom Field"));

    QVBoxLayout *vbox = new QVBoxLayout;
    setLayout(vbox);
    mLayout = new QFormLayout;
    vbox->addLayout(mLayout);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    mKey = new QLineEdit;
    mTitle = new QLineEdit;
    mType = new QComboBox;
    mScope = new QCheckBox(i18n("Use field for all contacts"));

    mLayout->addRow(i18nc("The title of a custom field", "Title"), mTitle);
    mLayout->addRow(i18nc("The type of a custom field", "Type"), mType);
    mLayout->addRow(QString(), mScope);
    mLayout->addRow(i18n("Key"), mKey);

    mType->addItem(i18n("Text"), CustomField::TextType);
    mType->addItem(i18n("Numeric"), CustomField::NumericType);
    mType->addItem(i18n("Boolean"), CustomField::BooleanType);
    mType->addItem(i18n("Date"), CustomField::DateType);
    mType->addItem(i18n("Time"), CustomField::TimeType);
    mType->addItem(i18n("DateTime"), CustomField::DateTimeType);
    mType->addItem(i18n("Url"), CustomField::UrlType);

    mKey->setValidator(new QRegExpValidator(QRegExp(QStringLiteral("[a-zA-Z0-9\\-]+")), this));
    mTitle->setFocus();

    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok |
            QDialogButtonBox::Cancel, this);
    btnBox->button(QDialogButtonBox::Ok)->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(btnBox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);

    vbox->addWidget(btnBox);
    mAdvancedButton = btnBox->addButton(i18n("Advanced"), QDialogButtonBox::ActionRole);
    mAdvancedButton->setIcon(QIcon::fromTheme(QStringLiteral("help-about")));
    mAdvancedButton->setCheckable(true);
    mAdvancedButton->setChecked(false);
    connect(mAdvancedButton, &QPushButton::clicked,
            this, &CustomFieldEditorDialog::toggleKeyRow);

    toggleKeyRow(false);
}

void CustomFieldEditorDialog::setCustomField(const CustomField &field)
{
    mCustomField = field;

    mKey->setText(mCustomField.key());
    mTitle->setText(mCustomField.title());
    mType->setCurrentIndex(mType->findData(mCustomField.type()));
    mScope->setChecked((mCustomField.scope() == CustomField::GlobalScope));
}

CustomField CustomFieldEditorDialog::customField() const
{
    CustomField customField(mCustomField);

    customField.setKey(mKey->text());
    customField.setTitle(mTitle->text());
    customField.setType(static_cast<CustomField::Type>(mType->itemData(mType->currentIndex()).toInt()));

    if (customField.scope() != CustomField::ExternalScope) {
        // do not change the scope for externally defined custom fields
        customField.setScope(mScope->isChecked() ? CustomField::GlobalScope : CustomField::LocalScope);
    }

    return customField;
}

void CustomFieldEditorDialog::toggleKeyRow(bool checked)
{
    mLayout->itemAt(3, QFormLayout::LabelRole)->widget()->setVisible(checked);
    mLayout->itemAt(3, QFormLayout::FieldRole)->widget()->setVisible(checked);

    mAdvancedButton->setText(i18n("Advanced") % (checked ? QStringLiteral(" <<") : QStringLiteral(" >>")));

    adjustSize();
}
