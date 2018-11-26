/*
    This file is part of Contact Editor.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#include "contacteditorwidget.h"
#include "config-contact-editor.h"

#include "personaleditor/personaleditorwidget.h"
#include "contacteditorpageplugin.h"
#include "contactmetadatabase_p.h"

#include <kconfig.h>
#include <kconfiggroup.h>
#include <KLocalizedString>
#include <qtabwidget.h>
#include <ktextedit.h>

#include <QDirIterator>
#include <QPluginLoader>
#include <QVBoxLayout>
#include "addresseditor/addresseslocationwidget.h"
#include "customfieldeditor/customfieldswidget.h"
#include "businesseditor/businesseditorwidget.h"
#include "generalinfoeditor/generalinfowidget.h"

class Q_DECL_HIDDEN ContactEditorWidget::Private
{
public:
    Private(ContactEditorWidget::DisplayMode displayMode, ContactEditorWidget *parent)
        : mDisplayMode(displayMode)
        , mParent(parent)
        , mCustomFieldsWidget(nullptr)
    {
    }

    void initGui();
    void initGuiContactTab();
    void initGuiLocationTab();
    void initGuiBusinessTab();
    void initGuiPersonalTab();
    void initGuiNotesTab();
    void initGuiCustomFieldsTab();

    void loadCustomPages();

    QString loadCustom(const KContacts::Addressee &contact, const QString &key) const;
    void storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value) const;

    ContactEditorWidget::DisplayMode mDisplayMode;
    ContactEditorWidget *mParent = nullptr;
    QTabWidget *mTabWidget = nullptr;

    ContactEditor::GeneralInfoWidget *mGeneralInfoWidget = nullptr;

    // widgets from addresses group
    ContactEditor::AddressesLocationWidget *mAddressesLocationWidget = nullptr;

    ContactEditor::BusinessEditorWidget *mBusinessEditorWidget = nullptr;

    // widgets from notes group
    KTextEdit *mNotesWidget = nullptr;

    ContactEditor::PersonalEditorWidget *mPersonalEditorWidget = nullptr;

    // widgets from custom fields group
    ContactEditor::CustomFieldsWidget *mCustomFieldsWidget = nullptr;

    // custom editor pages
    QList<ContactEditor::ContactEditorPagePlugin *> mCustomPages;
};

void ContactEditorWidget::Private::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(mParent);
    layout->setMargin(0);

    mTabWidget = new QTabWidget(mParent);
    layout->addWidget(mTabWidget);

    initGuiContactTab();
    initGuiLocationTab();
    initGuiBusinessTab();
    initGuiPersonalTab();
    initGuiNotesTab();
    if (mDisplayMode == FullMode) {
        initGuiCustomFieldsTab();
        loadCustomPages();
    }
}

void ContactEditorWidget::Private::initGuiContactTab()
{
    mGeneralInfoWidget = new ContactEditor::GeneralInfoWidget;
    mTabWidget->addTab(mGeneralInfoWidget, i18nc("@title:tab", "Contact"));
}

void ContactEditorWidget::Private::initGuiLocationTab()
{
    mAddressesLocationWidget = new ContactEditor::AddressesLocationWidget;
    mTabWidget->addTab(mAddressesLocationWidget, i18nc("@title:tab", "Location"));
}

void ContactEditorWidget::Private::initGuiBusinessTab()
{
    mBusinessEditorWidget = new ContactEditor::BusinessEditorWidget();
    mTabWidget->addTab(mBusinessEditorWidget, i18nc("@title:tab", "Business"));
}

void ContactEditorWidget::Private::initGuiPersonalTab()
{
    mPersonalEditorWidget = new ContactEditor::PersonalEditorWidget;
    mTabWidget->addTab(mPersonalEditorWidget, i18nc("@title:tab Personal properties of a contact", "Personal"));
}

void ContactEditorWidget::Private::initGuiNotesTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    mTabWidget->addTab(widget, i18nc("@title:tab", "Notes"));

    mNotesWidget = new KTextEdit;
    mNotesWidget->setAcceptRichText(false);
    layout->addWidget(mNotesWidget);
}

void ContactEditorWidget::Private::initGuiCustomFieldsTab()
{
    mCustomFieldsWidget = new ContactEditor::CustomFieldsWidget(mParent);
    mTabWidget->addTab(mCustomFieldsWidget, i18nc("@title:tab", "Custom Fields"));
}

void ContactEditorWidget::Private::loadCustomPages()
{
    qDeleteAll(mCustomPages);
    mCustomPages.clear();

    const QString pluginDirectory = QStringLiteral("%1/contacteditor/editorpageplugins/").arg(QStringLiteral(EDITOR_CONTACT_LIB));
    QDirIterator it(pluginDirectory, QDir::Files);

    while (it.hasNext()) {
        QPluginLoader loader(it.next());
        if (!loader.load()) {
            continue;
        }

        ContactEditor::ContactEditorPagePlugin *plugin = qobject_cast<ContactEditor::ContactEditorPagePlugin *>(loader.instance());
        if (!plugin) {
            continue;
        }

        mCustomPages.append(plugin);
    }

    for (ContactEditor::ContactEditorPagePlugin *plugin : qAsConst(mCustomPages)) {
        mTabWidget->addTab(plugin, plugin->title());
    }
}

QString ContactEditorWidget::Private::loadCustom(const KContacts::Addressee &contact, const QString &key) const
{
    return contact.custom(QStringLiteral("KADDRESSBOOK"), key);
}

void ContactEditorWidget::Private::storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value) const
{
    if (value.isEmpty()) {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), key);
    } else {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), key, value);
    }
}

ContactEditorWidget::ContactEditorWidget(QWidget *parent)
    : d(new Private(FullMode, this))
{
    Q_UNUSED(parent)
    d->initGui();
}

ContactEditorWidget::ContactEditorWidget(ContactEditorWidget::DisplayMode displayMode, QWidget *parent)
    : d(new Private(displayMode, this))
{
    Q_UNUSED(parent)
    d->initGui();
}

ContactEditorWidget::~ContactEditorWidget()
{
    delete d;
}

void ContactEditorWidget::loadContact(const KContacts::Addressee &contact, const ContactEditor::ContactMetaDataBase &metaData)
{
    d->mGeneralInfoWidget->loadContact(contact);

    // address group
    d->mAddressesLocationWidget->loadContact(contact);

    // general group
    d->mBusinessEditorWidget->loadContact(contact);
    // notes group
    d->mNotesWidget->setPlainText(contact.note());

    d->mPersonalEditorWidget->loadContact(contact);
    d->mGeneralInfoWidget->setDisplayType((DisplayNameEditWidget::DisplayType)metaData.displayNameMode());
    if (d->mDisplayMode == FullMode) {
        // custom fields group
        d->mCustomFieldsWidget->setLocalCustomFieldDescriptions(metaData.customFieldDescriptions());
        d->mCustomFieldsWidget->loadContact(contact);

        // custom pages
        for (ContactEditor::ContactEditorPagePlugin *plugin : qAsConst(d->mCustomPages)) {
            plugin->loadContact(contact);
        }
    }
}

void ContactEditorWidget::storeContact(KContacts::Addressee &contact, ContactEditor::ContactMetaDataBase &metaData) const
{
    d->mGeneralInfoWidget->storeContact(contact);

    // address group
    d->mAddressesLocationWidget->storeContact(contact);

    // general group
    d->mBusinessEditorWidget->storeContact(contact);

    // notes group
    contact.setNote(d->mNotesWidget->toPlainText());
    d->mPersonalEditorWidget->storeContact(contact);

    if (d->mDisplayMode == FullMode) {
        // custom fields group
        d->mCustomFieldsWidget->storeContact(contact);
        metaData.setCustomFieldDescriptions(d->mCustomFieldsWidget->localCustomFieldDescriptions());

        metaData.setDisplayNameMode(d->mGeneralInfoWidget->displayType());

        // custom pages
        for (ContactEditor::ContactEditorPagePlugin *plugin : qAsConst(d->mCustomPages)) {
            plugin->storeContact(contact);
        }
    }
}

void ContactEditorWidget::setReadOnly(bool readOnly)
{
    d->mGeneralInfoWidget->setReadOnly(readOnly);
    // widgets from addresses group
    d->mAddressesLocationWidget->setReadOnly(readOnly);

    // widgets from general group
    d->mBusinessEditorWidget->setReadOnly(readOnly);

    // widgets from notes group
    d->mNotesWidget->setReadOnly(readOnly);

    d->mPersonalEditorWidget->setReadOnly(readOnly);
    if (d->mDisplayMode == FullMode) {
        // widgets from custom fields group
        d->mCustomFieldsWidget->setReadOnly(readOnly);

        // custom pages
        for (ContactEditor::ContactEditorPagePlugin *plugin : qAsConst(d->mCustomPages)) {
            plugin->setReadOnly(readOnly);
        }
    }
}
