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
#include "categorieseditwidget.h"
#include "contacteditorpageplugin.h"
#include "contactmetadata_p.h"
#include "dateeditwidget.h"
#include "displaynameeditwidget.h"
#include "emaileditwidget.h"
#include "freebusyeditwidget.h"
#include "imagewidget.h"
#include "imeditwidget.h"
#include "nameeditwidget.h"
#include "phoneeditwidget.h"

#include <kconfig.h>
#include <kconfiggroup.h>
#include <KLineEdit>
#include <KLocalizedString>
#include <qtabwidget.h>
#include <ktextedit.h>
#include <QUrl>

#include <QtCore/QDirIterator>
#include <QtCore/QPluginLoader>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <KCompletion/KLineEdit>
#include <editor/addresseditor/addresseslocationwidget.h>
#include "customfieldeditor/customfieldswidget.h"

#include <editor/businesseditor/businesseditorwidget.h>

class Q_DECL_HIDDEN ContactEditorWidget::Private
{
public:
    Private(ContactEditorWidget::DisplayMode displayMode, ContactEditorWidget *parent)
        : mDisplayMode(displayMode)
        , mParent(parent)
        , mCustomFieldsWidget(0)
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

    // widgets from name group
    NameEditWidget *mNameWidget;
    ImageWidget *mPhotoWidget;
    DisplayNameEditWidget *mDisplayNameWidget;
    KLineEdit *mNickNameWidget;

    // widgets from Internet group
    EmailEditWidget *mEmailWidget;
    KLineEdit *mHomepageWidget;
    KLineEdit *mBlogWidget;
    IMEditWidget *mIMWidget;

    // widgets from phones group
    PhoneEditWidget *mPhonesWidget;

    CategoriesEditWidget *mCategoriesWidget;

    KComboBox *mMailPreferFormatting;
    QCheckBox *mAllowRemoteContent;

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
    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout(widget);

    mTabWidget->addTab(widget, i18nc("@title:tab", "Contact"));

    QGroupBox *nameGroupBox = new QGroupBox(i18nc("@title:group Name related properties of a contact", "Name"));
    QGroupBox *internetGroupBox = new QGroupBox(i18nc("@title:group", "Internet"));
    QGroupBox *phonesGroupBox = new QGroupBox(i18nc("@title:group", "Phones"));

    nameGroupBox->setMinimumSize(320, 200);
    layout->addWidget(nameGroupBox, 0, 0);
    layout->addWidget(internetGroupBox, 0, 1);
    layout->addWidget(phonesGroupBox, 1, 0, 4, 1);

    QGridLayout *nameLayout = new QGridLayout(nameGroupBox);
    QGridLayout *internetLayout = new QGridLayout(internetGroupBox);
    QGridLayout *phonesLayout = new QGridLayout(phonesGroupBox);

    // setup name group box
    QLabel *label = new QLabel(i18nc("@label The name of a contact", "Name:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    nameLayout->addWidget(label, 0, 0);

    mNameWidget = new NameEditWidget;
    label->setBuddy(mNameWidget);
    nameLayout->addWidget(mNameWidget, 0, 1);

    mPhotoWidget = new ImageWidget(ImageWidget::Photo);
    nameLayout->addWidget(mPhotoWidget, 0, 2, 4, 1);

    label = new QLabel(i18nc("@label The display name of a contact", "Display:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    nameLayout->addWidget(label, 1, 0);

    mDisplayNameWidget = new DisplayNameEditWidget;
    label->setBuddy(mDisplayNameWidget);
    nameLayout->addWidget(mDisplayNameWidget, 1, 1);

    label = new QLabel(i18nc("@label The nickname of a contact", "Nickname:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    nameLayout->addWidget(label, 2, 0);

    mNickNameWidget = new KLineEdit;
    mNickNameWidget->setTrapReturnKey(true);
    label->setBuddy(mNickNameWidget);
    nameLayout->addWidget(mNickNameWidget, 2, 1);

    nameLayout->setRowStretch(3, 1);

    // setup Internet group box
    label = new QLabel(i18nc("@label The email address of a contact", "Email:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    internetLayout->addWidget(label, 0, 0);

    mEmailWidget = new EmailEditWidget;
    label->setBuddy(mEmailWidget);
    internetLayout->addWidget(mEmailWidget, 0, 1);

    label = new QLabel(i18nc("@label The homepage URL of a contact", "Homepage:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    internetLayout->addWidget(label, 1, 0);

    mHomepageWidget = new KLineEdit;
    mHomepageWidget->setTrapReturnKey(true);
    label->setBuddy(mHomepageWidget);
    internetLayout->addWidget(mHomepageWidget, 1, 1);

    label = new QLabel(i18nc("@label The blog URL of a contact", "Blog:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    internetLayout->addWidget(label, 2, 0);

    mBlogWidget = new KLineEdit;
    mBlogWidget->setTrapReturnKey(true);
    label->setBuddy(mBlogWidget);
    internetLayout->addWidget(mBlogWidget, 2, 1);

    label = new QLabel(i18nc("@label The instant messaging address of a contact", "Messaging:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    internetLayout->addWidget(label, 3, 0);

    mIMWidget = new IMEditWidget;
    label->setBuddy(mIMWidget);
    internetLayout->addWidget(mIMWidget, 3, 1);

    internetLayout->setRowStretch(4, 1);

    // setup phones group box
    mPhonesWidget = new PhoneEditWidget;
    phonesLayout->addWidget(mPhonesWidget, 0, 0);

    //phonesLayout->setRowStretch( 1, 1 );

    // setup categories section
    QHBoxLayout *categoriesLayout = new QHBoxLayout;
    label = new QLabel(i18nc("@label The categories of a contact", "Categories:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    mCategoriesWidget = new CategoriesEditWidget;
    label->setBuddy(mCategoriesWidget);

    categoriesLayout->addWidget(label);
    categoriesLayout->addWidget(mCategoriesWidget);

    layout->addLayout(categoriesLayout, 1, 1);

    QGroupBox *receivedMessageGroupBox = new QGroupBox(i18n("Messages"));
    layout->addWidget(receivedMessageGroupBox, 2, 1);

    QVBoxLayout *vbox = new QVBoxLayout(receivedMessageGroupBox);

    QHBoxLayout *mailPreferFormattingLayout = new QHBoxLayout;
    label = new QLabel(i18n("Show messages received from this contact as:"));
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    mMailPreferFormatting = new KComboBox;
    label->setBuddy(mMailPreferFormatting);
    QStringList listFormat;
    listFormat << i18n("Default") << i18n("Plain Text") << i18n("HTML");
    mMailPreferFormatting->addItems(listFormat);
    mailPreferFormattingLayout->addWidget(label);
    mailPreferFormattingLayout->addWidget(mMailPreferFormatting);

    vbox->addLayout(mailPreferFormattingLayout);

    mAllowRemoteContent = new QCheckBox(i18n("Allow remote content in received HTML messages"));
    vbox->addWidget(mAllowRemoteContent);

    layout->setRowStretch(4, 1);
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

    connect(d->mNameWidget, &NameEditWidget::nameChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeName);
    connect(d->mBusinessEditorWidget, &Akonadi::BusinessEditorWidget::organizationChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeOrganization);
}

ContactEditorWidget::ContactEditorWidget(ContactEditorWidget::DisplayMode displayMode, QWidget *parent)
    : d(new Private(displayMode, this))
{
    Q_UNUSED(parent)
    d->initGui();

    connect(d->mNameWidget, &NameEditWidget::nameChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeName);
    connect(d->mBusinessEditorWidget, &Akonadi::BusinessEditorWidget::organizationChanged, d->mDisplayNameWidget, &DisplayNameEditWidget::changeOrganization);
}

ContactEditorWidget::~ContactEditorWidget()
{
    delete d;
}

void ContactEditorWidget::loadContact(const KContacts::Addressee &contact, const Akonadi::ContactMetaData &metaData)
{
    // name group
    d->mPhotoWidget->loadContact(contact);
    d->mNameWidget->loadContact(contact);
    d->mDisplayNameWidget->loadContact(contact);
    d->mNickNameWidget->setText(contact.nickName());

    // Internet group
    d->mEmailWidget->loadContact(contact);
    d->mHomepageWidget->setText(contact.url().url().toString());
    d->mBlogWidget->setText(d->loadCustom(contact, QStringLiteral("BlogFeed")));
    d->mIMWidget->loadContact(contact);

    // phones group
    d->mPhonesWidget->loadContact(contact);

    // categories section
    d->mCategoriesWidget->loadContact(contact);

    const QString mailPreferedFormatting = d->loadCustom(contact, QStringLiteral("MailPreferedFormatting"));
    if (mailPreferedFormatting.isEmpty()) {
        d->mMailPreferFormatting->setCurrentIndex(0);
    } else if (mailPreferedFormatting == QLatin1String("TEXT")) {
        d->mMailPreferFormatting->setCurrentIndex(1);
    } else if (mailPreferedFormatting == QLatin1String("HTML")) {
        d->mMailPreferFormatting->setCurrentIndex(2);
    } else {
        d->mMailPreferFormatting->setCurrentIndex(0);
    }

    const QString mailAllowToRemoteContent = d->loadCustom(contact, QStringLiteral("MailAllowToRemoteContent"));
    d->mAllowRemoteContent->setChecked(mailAllowToRemoteContent == QLatin1String("TRUE"));

    // address group
    d->mAddressesLocationWidget->loadContact(contact);

    // general group
    d->mBusinessEditorWidget->loadContact(contact);
    // notes group
    d->mNotesWidget->setPlainText(contact.note());

    d->mPersonalEditorWidget->loadContact(contact);
    d->mDisplayNameWidget->setDisplayType((DisplayNameEditWidget::DisplayType)metaData.displayNameMode());

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
    // name group
    d->mPhotoWidget->storeContact(contact);
    d->mNameWidget->storeContact(contact);
    d->mDisplayNameWidget->storeContact(contact);
    contact.setNickName(d->mNickNameWidget->text().trimmed());

    // Internet group
    d->mEmailWidget->storeContact(contact);
    KContacts::ResourceLocatorUrl resourceLocatorUrl;
    resourceLocatorUrl.setUrl(QUrl(d->mHomepageWidget->text().trimmed()));
    contact.setUrl(resourceLocatorUrl);
    d->storeCustom(contact, QStringLiteral("BlogFeed"), d->mBlogWidget->text().trimmed());
    d->mIMWidget->storeContact(contact);

    // phones group
    d->mPhonesWidget->storeContact(contact);

    // categories section
    d->mCategoriesWidget->storeContact(contact);

    QString mailPreferedFormatting;
    const int index = d->mMailPreferFormatting->currentIndex();
    if (index == 0) {
        //Nothing => remove custom variable
    } else if (index == 1) {
        mailPreferedFormatting = QStringLiteral("TEXT");
    } else if (index == 2) {
        mailPreferedFormatting = QStringLiteral("HTML");
    }
    d->storeCustom(contact, QStringLiteral("MailPreferedFormatting"), mailPreferedFormatting);

    QString mailAllowToRemoteContent;
    if (d->mAllowRemoteContent->isChecked()) {
        mailAllowToRemoteContent = QStringLiteral("TRUE");
    }
    d->storeCustom(contact, QStringLiteral("MailAllowToRemoteContent"), mailAllowToRemoteContent);

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

        metaData.setDisplayNameMode(d->mDisplayNameWidget->displayType());

        // custom pages
        foreach (Akonadi::ContactEditorPagePlugin *plugin, d->mCustomPages) {
            plugin->storeContact(contact);
        }
    }
}

void ContactEditorWidget::setReadOnly(bool readOnly)
{
    // widgets from name group
    d->mNameWidget->setReadOnly(readOnly);
    d->mPhotoWidget->setReadOnly(readOnly);
    d->mDisplayNameWidget->setReadOnly(readOnly);
    d->mNickNameWidget->setReadOnly(readOnly);

    // widgets from Internet group
    d->mEmailWidget->setReadOnly(readOnly);
    d->mHomepageWidget->setReadOnly(readOnly);
    d->mBlogWidget->setReadOnly(readOnly);
    d->mIMWidget->setReadOnly(readOnly);

    // widgets from phones group
    d->mPhonesWidget->setReadOnly(readOnly);

    // widgets from categories section
    d->mCategoriesWidget->setReadOnly(readOnly);

    // Preferred Mail formatting option
    d->mMailPreferFormatting->setEnabled(!readOnly);
    d->mAllowRemoteContent->setEnabled(!readOnly);

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
