/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "grantleecontactformatter.h"
#include "contactgrantleewrapper.h"

#include <KContacts/Addressee>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeTheme>
#include <GrantleeTheme/GrantleeThemeEngine>

#include <grantlee/context.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>

#include <AkonadiCore/Item>

#include <KColorScheme>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KStringHandler>

#include <QLocale>
#include <QMetaProperty>
#include <QSet>

using namespace KAddressBookGrantlee;

// Grantlee has no Q_GADGET support yet
#define GRANTLEE_MAKE_GADGET(Class)                                                                                                                            \
    GRANTLEE_BEGIN_LOOKUP(Class)                                                                                                                               \
    const auto idx = Class::staticMetaObject.indexOfProperty(property.toUtf8().constData());                                                                   \
    if (idx < 0) {                                                                                                                                             \
        return {};                                                                                                                                             \
    }                                                                                                                                                          \
    const auto mp = Class::staticMetaObject.property(idx);                                                                                                     \
    return mp.readOnGadget(&object);                                                                                                                           \
    GRANTLEE_END_LOOKUP

GRANTLEE_MAKE_GADGET(KContacts::Address)
GRANTLEE_MAKE_GADGET(KContacts::Email)
GRANTLEE_MAKE_GADGET(KContacts::Impp)
GRANTLEE_MAKE_GADGET(KContacts::PhoneNumber)
GRANTLEE_MAKE_GADGET(KContacts::ResourceLocatorUrl)
GRANTLEE_MAKE_GADGET(KAddressBookGrantlee::ContactGrantleeWrapper)

GRANTLEE_BEGIN_LOOKUP(QUrl)
if (property == QLatin1String("scheme")) {
    return object.scheme();
} else if (property == QLatin1String("path")) {
    return object.path();
}
GRANTLEE_END_LOOKUP

class Q_DECL_HIDDEN GrantleeContactFormatter::Private
{
public:
    Private()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        showQRCode = group.readEntry("QRCodes", true);

        mEngine.reset(new GrantleeTheme::Engine);

        mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader());
    }

    ~Private()
    {
        mTemplateLoader.clear();
    }

    void changeGrantleePath(const QString &path)
    {
        mTemplateLoader->setTemplateDirs(QStringList() << path);
        mEngine->addTemplateLoader(mTemplateLoader);

        mSelfcontainedTemplate = mEngine->loadByName(QStringLiteral("contact.html"));
        if (mSelfcontainedTemplate->error()) {
            mErrorMessage += mSelfcontainedTemplate->errorString() + QStringLiteral("<br>");
        }

        mEmbeddableTemplate = mEngine->loadByName(QStringLiteral("contact_embedded.html"));
        if (mEmbeddableTemplate->error()) {
            mErrorMessage += mEmbeddableTemplate->errorString() + QStringLiteral("<br>");
        }
    }

    QVector<QObject *> mObjects;
    std::unique_ptr<GrantleeTheme::Engine> mEngine;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mSelfcontainedTemplate;
    Grantlee::Template mEmbeddableTemplate;
    QString mErrorMessage;
    bool forceDisableQRCode = false;
    bool showQRCode = true;
};

GrantleeContactFormatter::GrantleeContactFormatter()
    : d(new Private)
{
    Grantlee::registerMetaType<KContacts::Address>();
    Grantlee::registerMetaType<KContacts::Email>();
    Grantlee::registerMetaType<KContacts::Impp>();
    Grantlee::registerMetaType<KContacts::PhoneNumber>();
    Grantlee::registerMetaType<KContacts::ResourceLocatorUrl>();
    Grantlee::registerMetaType<ContactGrantleeWrapper>();
    Grantlee::registerMetaType<QUrl>();
}

GrantleeContactFormatter::~GrantleeContactFormatter()
{
    delete d;
}

void GrantleeContactFormatter::setAbsoluteThemePath(const QString &path)
{
    d->changeGrantleePath(path);
}

void GrantleeContactFormatter::setGrantleeTheme(const GrantleeTheme::Theme &theme)
{
    d->changeGrantleePath(theme.absolutePath());
}

void GrantleeContactFormatter::setForceDisableQRCode(bool b)
{
    d->forceDisableQRCode = b;
}

bool GrantleeContactFormatter::forceDisableQRCode() const
{
    return d->forceDisableQRCode;
}

void GrantleeContactFormatter::setShowQRCode(bool b)
{
    d->showQRCode = b;
}

QString GrantleeContactFormatter::toHtml(HtmlForm form) const
{
    if (!d->mErrorMessage.isEmpty()) {
        return d->mErrorMessage;
    }

    KContacts::Addressee rawContact;
    const Akonadi::Item localItem = item();
    if (localItem.isValid() && localItem.hasPayload<KContacts::Addressee>()) {
        rawContact = localItem.payload<KContacts::Addressee>();
    } else {
        rawContact = contact();
    }

    if (rawContact.isEmpty()) {
        return QString();
    }

    // Custom fields
    QVariantList customFields;
    QVariantList customFieldsUrl;
    static QSet<QString> blacklistedKeys = {QStringLiteral("CRYPTOPROTOPREF"),
                                            QStringLiteral("OPENPGPFP"),
                                            QStringLiteral("SMIMEFP"),
                                            QStringLiteral("CRYPTOSIGNPREF"),
                                            QStringLiteral("CRYPTOENCRYPTPREF"),
                                            QStringLiteral("Anniversary"),
                                            QStringLiteral("BlogFeed"),
                                            QStringLiteral("Profession"),
                                            QStringLiteral("Office"),
                                            QStringLiteral("ManagersName"),
                                            QStringLiteral("AssistantsName"),
                                            QStringLiteral("SpousesName"),
                                            QStringLiteral("IMAddress"),
                                            QStringLiteral("AddressBook"),
                                            QStringLiteral("MailPreferedFormatting"),
                                            QStringLiteral("MailAllowToRemoteContent"),
                                            QStringLiteral("MAILPREFEREDFORMATTING"),
                                            QStringLiteral("MAILALLOWTOREMOTECONTENT")};

    const auto customs = rawContact.customs();
    for (QString custom : customs) {
        if (custom.startsWith(QLatin1String("KADDRESSBOOK-"))) {
            custom.remove(QStringLiteral("KADDRESSBOOK-X-"));
            custom.remove(QStringLiteral("KADDRESSBOOK-"));

            int pos = custom.indexOf(QLatin1Char(':'));
            QString key = custom.left(pos);
            QString value = custom.mid(pos + 1);

            if (blacklistedKeys.contains(key)) {
                continue;
            }

            bool addUrl = false;
            // check whether it is a custom local field
            for (int i = 0; i < customFieldDescriptions().size(); ++i) {
                const QVariantMap description = customFieldDescriptions().at(i);
                if (description.value(QStringLiteral("key")).toString() == key) {
                    key = description.value(QStringLiteral("title")).toString();
                    const QString descriptionType = description.value(QStringLiteral("type")).toString();
                    if (descriptionType == QLatin1String("boolean")) {
                        if (value == QLatin1String("true")) {
                            value = i18nc("Boolean value", "yes");
                        } else {
                            value = i18nc("Boolean value", "no");
                        }
                    } else if (descriptionType == QLatin1String("date")) {
                        const QDate date = QDate::fromString(value, Qt::ISODate);
                        value = QLocale().toString(date, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1String("time")) {
                        const QTime time = QTime::fromString(value, Qt::ISODate);
                        value = QLocale::system().toString(time, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1String("datetime")) {
                        const QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
                        value = QLocale().toString(dateTime, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1String("url")) {
                        value = KStringHandler::tagUrls(value.toHtmlEscaped());
                        addUrl = true;
                    }
                    break;
                }
            }
            QVariantHash customFieldObject;
            customFieldObject.insert(QStringLiteral("title"), key);
            customFieldObject.insert(QStringLiteral("value"), value);

            if (addUrl) {
                customFieldsUrl.append(customFieldObject);
            } else {
                customFields.append(customFieldObject);
            }
        }
    }

    QVariantHash colorsObject;

    colorsObject.insert(QStringLiteral("linkColor"), KColorScheme(QPalette::Active, KColorScheme::View).foreground().color().name());

    colorsObject.insert(QStringLiteral("textColor"), KColorScheme(QPalette::Active, KColorScheme::View).foreground().color().name());

    colorsObject.insert(QStringLiteral("backgroundColor"), KColorScheme(QPalette::Active, KColorScheme::View).background().color().name());

    QVariantHash mapping;
    mapping.insert(QStringLiteral("contact"), QVariant::fromValue(ContactGrantleeWrapper(rawContact)));
    mapping.insert(QStringLiteral("colors"), colorsObject);
    mapping.insert(QStringLiteral("customFields"), customFields);
    mapping.insert(QStringLiteral("customFieldsUrl"), customFieldsUrl);
    mapping.insert(QStringLiteral("hasqrcode"), !d->forceDisableQRCode && d->showQRCode);

    Grantlee::Context context(mapping);
    context.setLocalizer(d->mEngine->localizer());

    if (form == SelfcontainedForm) {
        return d->mSelfcontainedTemplate->render(&context);
    } else if (form == EmbeddableForm) {
        return d->mEmbeddableTemplate->render(&context);
    } else {
        return QString();
    }
}

void GrantleeContactFormatter::setApplicationDomain(const QByteArray &domain)
{
    d->mEngine->localizer()->setApplicationDomain(domain);
}
