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

#include "customfielslistwidget.h"
#include "customfieldmanager_p.h"
#include "customfieldslistdelegate.h"
#include <KLocalizedString>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <KContacts/Addressee>
#include <editor/customfieldsmodel.h>

using namespace Akonadi;

void splitCustomField(const QString &str, QString &app, QString &name, QString &value)
{
    const int colon = str.indexOf(QLatin1Char(':'));
    if (colon != -1) {
        const QString tmp = str.left(colon);
        value = str.mid(colon + 1);

        const int dash = tmp.indexOf(QLatin1Char('-'));
        if (dash != -1) {
            app = tmp.left(dash);
            name = tmp.mid(dash + 1);
        }
    }
}

CustomFielsListWidget::CustomFielsListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    mCustomFieldList = new QTreeView(this);
    mCustomFieldList->setObjectName(QStringLiteral("customfieldlist"));
    mCustomFieldList->setSortingEnabled(true);
    mCustomFieldList->setRootIsDecorated(false);
    mCustomFieldList->setItemDelegate(new Akonadi::CustomFieldsListDelegate(this));
    topLayout->addWidget(mCustomFieldList);

    mModel = new CustomFieldsModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(mModel);
    mCustomFieldList->setModel(proxyModel);
    mCustomFieldList->setColumnHidden(2, true);   // hide the 'key' column
}

CustomFielsListWidget::~CustomFielsListWidget()
{

}

//TODO add edit/remove

void CustomFielsListWidget::loadContact(const KContacts::Addressee &contact)
{
    CustomField::List externalCustomFields;

    CustomField::List globalCustomFields = CustomFieldManager::globalCustomFieldDescriptions();

    const QStringList customs = contact.customs();
    foreach (const QString &custom, customs) {

        QString app, name, value;
        splitCustomField(custom, app, name, value);

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

void CustomFielsListWidget::storeContact(KContacts::Addressee &contact) const
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

void CustomFielsListWidget::setReadOnly(bool readOnly)
{
    mCustomFieldList->setEnabled(!readOnly);
}
