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

#include "customfieldslistwidget.h"
#include "../utils/utils.h"
#include "customfieldmanager_p.h"
#include "customfieldslistdelegate.h"
#include <KLocalizedString>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <KContacts/Addressee>
#include "customfieldsmodel.h"

using namespace Akonadi;

CustomFieldsListWidget::CustomFieldsListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    mCustomFieldList = new QTreeView(this);
    mCustomFieldList->setObjectName(QStringLiteral("customfieldlist"));
    mCustomFieldList->setSortingEnabled(true);
    mCustomFieldList->setRootIsDecorated(false);
    Akonadi::CustomFieldsListDelegate *customFieldDelegate = new Akonadi::CustomFieldsListDelegate(mCustomFieldList, this);
    mCustomFieldList->setItemDelegate(customFieldDelegate);
    topLayout->addWidget(mCustomFieldList);

    mModel = new CustomFieldsModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(mModel);
    mCustomFieldList->setModel(proxyModel);
    mCustomFieldList->setColumnHidden(2, true);   // hide the 'key' column
}

CustomFieldsListWidget::~CustomFieldsListWidget()
{

}

void CustomFieldsListWidget::loadContact(const KContacts::Addressee &contact)
{
    CustomField::List externalCustomFields;

    CustomField::List globalCustomFields = CustomFieldManager::globalCustomFieldDescriptions();

    const QStringList customs = contact.customs();
    foreach (const QString &custom, customs) {

        QString app, name, value;
        Akonadi::Utils::splitCustomField(custom, app, name, value);

        // skip all well-known fields that have separated editor widgets
        if (custom.startsWith(QStringLiteral("messaging/"))) {       // IM addresses
            continue;
        }

        if (app == QLatin1String("KADDRESSBOOK")) {
            static QSet<QString> blacklist;
            if (blacklist.isEmpty()) {
                blacklist << QStringLiteral("BlogFeed")
                          << QStringLiteral("X-IMAddress")
                          << QStringLiteral("X-Profession")
                          << QStringLiteral("X-Office")
                          << QStringLiteral("X-ManagersName")
                          << QStringLiteral("X-AssistantsName")
                          << QStringLiteral("X-Anniversary")
                          << QStringLiteral("X-ANNIVERSARY")
                          << QStringLiteral("X-SpousesName")
                          << QStringLiteral("X-Profession")
                          << QStringLiteral("MailPreferedFormatting")
                          << QStringLiteral("MailAllowToRemoteContent")
                          << QStringLiteral("CRYPTOPROTOPREF")
                          << QStringLiteral("OPENPGPFP")
                          << QStringLiteral("SMIMEFP")
                          << QStringLiteral("CRYPTOSIGNPREF")
                          << QStringLiteral("CRYPTOENCRYPTPREF");
            }

            if (blacklist.contains(name)) {     // several KAddressBook specific fields
                continue;
            }
        }

        // check whether it correspond to a local custom field
        bool isLocalCustomField = false;
        for (int i = 0; i < mLocalCustomFields.count(); ++i) {
            if (mLocalCustomFields[i].key() == name) {
                mLocalCustomFields[i].setValue(value);
                isLocalCustomField = true;
                break;
            }
        }

        // check whether it correspond to a global custom field
        bool isGlobalCustomField = false;
        for (int i = 0; i < globalCustomFields.count(); ++i) {
            if (globalCustomFields[i].key() == name) {
                globalCustomFields[i].setValue(value);
                isGlobalCustomField = true;
                break;
            }
        }

        // if not local and not global it must be external
        if (!isLocalCustomField && !isGlobalCustomField) {
            if (app == QLatin1String("KADDRESSBOOK")) {
                // however if it starts with our prefix it might be that this is an outdated
                // global custom field, in this case treat it as local field of type text
                CustomField customField(name, name, CustomField::TextType, CustomField::LocalScope);
                customField.setValue(value);

                mLocalCustomFields << customField;
            } else {
                // it is really an external custom field
                const QString key = app + QLatin1Char('-') + name;
                CustomField customField(key, key, CustomField::TextType, CustomField::ExternalScope);
                customField.setValue(value);

                externalCustomFields << customField;
            }
        }
    }

    mModel->setCustomFields(CustomField::List() << mLocalCustomFields << globalCustomFields << externalCustomFields);
}

void CustomFieldsListWidget::storeContact(KContacts::Addressee &contact) const
{
    const CustomField::List customFields = mModel->customFields();
    foreach (const CustomField &customField, customFields) {
        // write back values for local and global scope, leave external untouched
        if (customField.scope() != CustomField::ExternalScope) {
            if (!customField.value().isEmpty()) {
                contact.insertCustom(QStringLiteral("KADDRESSBOOK"), customField.key(), customField.value());
            } else {
                contact.removeCustom(QStringLiteral("KADDRESSBOOK"), customField.key());
            }
        }
    }

    // Now remove all fields that were available in loadContact (these are stored in mLocalCustomFields)
    // but are not part of customFields now, which means they have been removed or renamed by the user
    // in the editor dialog.
    foreach (const CustomField &oldCustomField, mLocalCustomFields) {
        if (oldCustomField.scope() != CustomField::ExternalScope) {

            bool fieldStillExists = false;
            foreach (const CustomField &newCustomField, customFields) {
                if (newCustomField.scope() != CustomField::ExternalScope) {
                    if (newCustomField.key() == oldCustomField.key()) {
                        fieldStillExists = true;
                        break;
                    }
                }
            }

            if (!fieldStillExists) {
                contact.removeCustom(QStringLiteral("KADDRESSBOOK"), oldCustomField.key());
            }
        }
    }

    // And store the global custom fields descriptions as well
    CustomField::List globalCustomFields;
    foreach (const CustomField &customField, customFields) {
        if (customField.scope() == CustomField::GlobalScope) {
            globalCustomFields << customField;
        }
    }

    CustomFieldManager::setGlobalCustomFieldDescriptions(globalCustomFields);
}

void CustomFieldsListWidget::setReadOnly(bool readOnly)
{
    mCustomFieldList->setEnabled(!readOnly);
}

void CustomFieldsListWidget::slotAddNewField(const CustomField &field)
{
    const int lastRow = mModel->rowCount();
    mModel->insertRow(lastRow);
    mModel->setData(mModel->index(lastRow, 2), field.key(), Qt::EditRole);
    mModel->setData(mModel->index(lastRow, 0), field.title(), Qt::EditRole);
    mModel->setData(mModel->index(lastRow, 0), field.type(), CustomFieldsModel::TypeRole);
    mModel->setData(mModel->index(lastRow, 0), field.scope(), CustomFieldsModel::ScopeRole);

}

void CustomFieldsListWidget::setLocalCustomFieldDescriptions(const QVariantList &descriptions)
{
    mLocalCustomFields.clear();
    mLocalCustomFields.reserve(descriptions.count());
    foreach (const QVariant &description, descriptions) {
        mLocalCustomFields.append(CustomField::fromVariantMap(description.toMap(), CustomField::LocalScope));
    }
}

QVariantList CustomFieldsListWidget::localCustomFieldDescriptions() const
{
    const CustomField::List customFields = mModel->customFields();

    QVariantList descriptions;
    foreach (const CustomField &field, customFields) {
        if (field.scope() == CustomField::LocalScope) {
            descriptions.append(field.toVariantMap());
        }
    }

    return descriptions;
}
