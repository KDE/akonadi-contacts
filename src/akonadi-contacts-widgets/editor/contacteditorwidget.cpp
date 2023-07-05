/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contacteditorwidget.h"

#include "contacteditorpageplugin.h"
#include "contactmetadatabase_p.h"
#include "personaleditor/personaleditorwidget.h"

#include <KLocalizedString>
#include <KTextEdit>
#include <QTabWidget>

#include "addresseditor/addresseslocationwidget.h"
#include "businesseditor/businesseditorwidget.h"
#include "customfieldeditor/customfieldswidget.h"
#include "generalinfoeditor/generalinfowidget.h"
#include <QCoreApplication>
#include <QDirIterator>
#include <QPluginLoader>
#include <QVBoxLayout>

class ContactEditorWidgetPrivate
{
public:
    ContactEditorWidgetPrivate(ContactEditorWidget::DisplayMode displayMode, ContactEditorWidget *parent)
        : mDisplayMode(displayMode)
        , mParent(parent)
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
    ContactEditorWidget *const mParent;
    QTabWidget *mTabWidget = nullptr;

    Akonadi::GeneralInfoWidget *mGeneralInfoWidget = nullptr;

    // widgets from addresses group
    Akonadi::AddressesLocationWidget *mAddressesLocationWidget = nullptr;

    Akonadi::BusinessEditorWidget *mBusinessEditorWidget = nullptr;

    // widgets from notes group
    KTextEdit *mNotesWidget = nullptr;

    Akonadi::PersonalEditorWidget *mPersonalEditorWidget = nullptr;

    // widgets from custom fields group
    Akonadi::CustomFieldsWidget *mCustomFieldsWidget = nullptr;

    // custom editor pages
    QList<Akonadi::ContactEditorPagePlugin *> mCustomPages;
};

void ContactEditorWidgetPrivate::initGui()
{
    auto layout = new QVBoxLayout(mParent);
    layout->setContentsMargins({});

    mTabWidget = new QTabWidget(mParent);
    layout->addWidget(mTabWidget);

    initGuiContactTab();
    initGuiLocationTab();
    initGuiBusinessTab();
    initGuiPersonalTab();
    initGuiNotesTab();
    if (mDisplayMode == ContactEditorWidget::FullMode) {
        initGuiCustomFieldsTab();
        loadCustomPages();
    }
}

void ContactEditorWidgetPrivate::initGuiContactTab()
{
    mGeneralInfoWidget = new Akonadi::GeneralInfoWidget;
    mTabWidget->addTab(mGeneralInfoWidget, i18nc("@title:tab", "Contact"));
}

void ContactEditorWidgetPrivate::initGuiLocationTab()
{
    mAddressesLocationWidget = new Akonadi::AddressesLocationWidget;
    mTabWidget->addTab(mAddressesLocationWidget, i18nc("@title:tab", "Location"));
}

void ContactEditorWidgetPrivate::initGuiBusinessTab()
{
    mBusinessEditorWidget = new Akonadi::BusinessEditorWidget();
    mTabWidget->addTab(mBusinessEditorWidget, i18nc("@title:tab", "Business"));
}

void ContactEditorWidgetPrivate::initGuiPersonalTab()
{
    mPersonalEditorWidget = new Akonadi::PersonalEditorWidget;
    mTabWidget->addTab(mPersonalEditorWidget, i18nc("@title:tab Personal properties of a contact", "Personal"));
}

void ContactEditorWidgetPrivate::initGuiNotesTab()
{
    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);

    mTabWidget->addTab(widget, i18nc("@title:tab", "Notes"));

    mNotesWidget = new KTextEdit;
    mNotesWidget->setAcceptRichText(false);
    layout->addWidget(mNotesWidget);
}

void ContactEditorWidgetPrivate::initGuiCustomFieldsTab()
{
    mCustomFieldsWidget = new Akonadi::CustomFieldsWidget(mParent);
    mTabWidget->addTab(mCustomFieldsWidget, i18nc("@title:tab", "Custom Fields"));
}

void ContactEditorWidgetPrivate::loadCustomPages()
{
    qDeleteAll(mCustomPages);
    mCustomPages.clear();

    const QStringList pluginDirs = QCoreApplication::libraryPaths();

    for (const QString &dir : pluginDirs) {
        QDirIterator it(dir + QLatin1String("/pim6/contacteditor/editorpageplugins"), QDir::Files);

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
    }

    for (Akonadi::ContactEditorPagePlugin *plugin : std::as_const(mCustomPages)) {
        mTabWidget->addTab(plugin, plugin->title());
    }
}

QString ContactEditorWidgetPrivate::loadCustom(const KContacts::Addressee &contact, const QString &key) const
{
    return contact.custom(QStringLiteral("KADDRESSBOOK"), key);
}

void ContactEditorWidgetPrivate::storeCustom(KContacts::Addressee &contact, const QString &key, const QString &value) const
{
    if (value.isEmpty()) {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), key);
    } else {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), key, value);
    }
}

ContactEditorWidget::ContactEditorWidget(QWidget *parent)
    : d(new ContactEditorWidgetPrivate(FullMode, this))
{
    Q_UNUSED(parent)
    d->initGui();
}

ContactEditorWidget::ContactEditorWidget(ContactEditorWidget::DisplayMode displayMode, QWidget *parent)
    : d(new ContactEditorWidgetPrivate(displayMode, this))
{
    Q_UNUSED(parent)
    d->initGui();
}

ContactEditorWidget::~ContactEditorWidget() = default;

void ContactEditorWidget::loadContact(const KContacts::Addressee &contact, const Akonadi::ContactMetaDataBase &metaData)
{
    d->mGeneralInfoWidget->loadContact(contact);

    // address group
    d->mAddressesLocationWidget->loadContact(contact);

    // general group
    d->mBusinessEditorWidget->loadContact(contact);
    // notes group
    d->mNotesWidget->setPlainText(contact.note());

    d->mPersonalEditorWidget->loadContact(contact);
    d->mGeneralInfoWidget->setDisplayType((Akonadi::DisplayNameEditWidget::DisplayType)metaData.displayNameMode());
    if (d->mDisplayMode == FullMode) {
        // custom fields group
        d->mCustomFieldsWidget->setLocalCustomFieldDescriptions(metaData.customFieldDescriptions());
        d->mCustomFieldsWidget->loadContact(contact);

        // custom pages
        for (Akonadi::ContactEditorPagePlugin *plugin : std::as_const(d->mCustomPages)) {
            plugin->loadContact(contact);
        }
    }
}

void ContactEditorWidget::storeContact(KContacts::Addressee &contact, Akonadi::ContactMetaDataBase &metaData) const
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
        for (Akonadi::ContactEditorPagePlugin *plugin : std::as_const(d->mCustomPages)) {
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
        for (Akonadi::ContactEditorPagePlugin *plugin : std::as_const(d->mCustomPages)) {
            plugin->setReadOnly(readOnly);
        }
    }
}

bool ContactEditorWidget::hasNoSavedData() const
{
    return d->mAddressesLocationWidget->hasNoSavedData();
}

#include "moc_contacteditorwidget.cpp"
