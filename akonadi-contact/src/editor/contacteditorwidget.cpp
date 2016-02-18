/*
    This file is part of Akonadi Contact.

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
#include "config-akonadi-contact.h"

#include "personaleditor/personaleditorwidget.h"
#include "contacteditorpageplugin.h"
#include "contactmetadata_p.h"

#include <kconfig.h>
#include <kconfiggroup.h>
#include <KLocalizedString>
#include <qtabwidget.h>
#include <ktextedit.h>
#include <QUrl>

#include <QtCore/QDirIterator>
#include <QtCore/QPluginLoader>
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
        , mCustomFieldsWidget(Q_NULLPTR)
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
    ContactEditorWidget *mParent;
    QTabWidget *mTabWidget;

    Akonadi::GeneralInfoWidget *mGeneralInfoWidget;


    // widgets from addresses group
    Akonadi::AddressesLocationWidget *mAddressesLocationWidget;

    Akonadi::BusinessEditorWidget *mBusinessEditorWidget;

    // widgets from notes group
    KTextEdit *mNotesWidget;

    Akonadi::PersonalEditorWidget *mPersonalEditorWidget;

    // widgets from custom fields group
    Akonadi::CustomFieldsWidget *mCustomFieldsWidget;

    // custom editor pages
    QList<Akonadi::ContactEditorPagePlugin *> mCustomPages;
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
    mGeneralInfoWidget = new Akonadi::GeneralInfoWidget;
    mTabWidget->addTab(mGeneralInfoWidget, i18nc("@title:tab", "Contact"));
}

void ContactEditorWidget::Private::initGuiLocationTab()
{
    mAddressesLocationWidget = new Akonadi::AddressesLocationWidget;
    mTabWidget->addTab(mAddressesLocationWidget, i18nc("@title:tab", "Location"));
}

void ContactEditorWidget::Private::initGuiBusinessTab()
{
    mBusinessEditorWidget = new Akonadi::BusinessEditorWidget();
    mTabWidget->addTab( mBusinessEditorWidget, i18nc( "@title:tab", "Business" ) );
}

void ContactEditorWidget::Private::initGuiPersonalTab()
{
    mPersonalEditorWidget = new Akonadi::PersonalEditorWidget;
    mTabWidget->addTab( mPersonalEditorWidget, i18nc( "@title:tab Personal properties of a contact", "Personal" ) );
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
    mCustomFieldsWidget = new Akonadi::CustomFieldsWidget;
    mTabWidget->addTab(mCustomFieldsWidget, i18nc("@title:tab", "Custom Fields"));
}

void ContactEditorWidget::Private::loadCustomPages()
{
    qDeleteAll(mCustomPages);
    mCustomPages.clear();

    const QString pluginDirectory = QStringLiteral("%1/akonadi/contact/editorpageplugins/").arg(QStringLiteral(AKONADI_CONTACT_LIB));
    QDirIterator it(pluginDirectory, QDir::Files);

    while (it.hasNext()) {
        QPluginLoader loader(it.next());
        if (!loader.load()) {
            continue;
        }

        Akonadi::ContactEditorPagePlugin *plugin = qobject_cast<Akonadi::ContactEditorPagePlugin *>(loader.instance());
        if (!plugin) {
            continue;
        }

        mCustomPages.append(plugin);
    }

    foreach (Akonadi::ContactEditorPagePlugin *plugin, mCustomPages) {
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

    //TODO PORT
    //connect(d->mNameWidget, &NameEditWidget::nameChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeName);
    //connect(d->mBusinessEditorWidget, &Akonadi::BusinessEditorWidget::organizationChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeOrganization);
}

ContactEditorWidget::ContactEditorWidget(ContactEditorWidget::DisplayMode displayMode, QWidget *parent)
    : d(new Private(displayMode, this))
{
    Q_UNUSED(parent)
    d->initGui();

    //TODO PORT
    //connect(d->mNameWidget, &NameEditWidget::nameChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeName);
    //connect(d->mBusinessEditorWidget, &Akonadi::BusinessEditorWidget::organizationChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeOrganization);
}

ContactEditorWidget::~ContactEditorWidget()
{
    delete d;
}

void ContactEditorWidget::loadContact(const KContacts::Addressee &contact, const Akonadi::ContactMetaData &metaData)
{    
    d->mGeneralInfoWidget->loadContact(contact);

    // address group
    d->mAddressesLocationWidget->loadContact(contact);

    // general group
    d->mBusinessEditorWidget->loadContact(contact);
    // notes group
    d->mNotesWidget->setPlainText(contact.note());

    d->mPersonalEditorWidget->loadContact(contact);

    if (d->mDisplayMode == FullMode) {
        // custom fields group
        d->mCustomFieldsWidget->setLocalCustomFieldDescriptions(metaData.customFieldDescriptions());
        d->mCustomFieldsWidget->loadContact(contact);

        // custom pages
        foreach (Akonadi::ContactEditorPagePlugin *plugin, d->mCustomPages) {
            plugin->loadContact(contact);
        }
    }
}

void ContactEditorWidget::storeContact(KContacts::Addressee &contact, Akonadi::ContactMetaData &metaData) const
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

        //TODO metaData.setDisplayNameMode(d->mDisplayNameWidget->displayType());

        // custom pages
        foreach (Akonadi::ContactEditorPagePlugin *plugin, d->mCustomPages) {
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
        foreach (Akonadi::ContactEditorPagePlugin *plugin, d->mCustomPages) {
            plugin->setReadOnly(readOnly);
        }
    }
}
