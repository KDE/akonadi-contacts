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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/context.h>
#include <grantlee/metatype.h>
#include <grantlee/templateloader.h>
#else
#include <KTextTemplate/context.h>
#include <KTextTemplate/metatype.h>
#include <KTextTemplate/templateloader.h>
#endif

#include <Akonadi/Item>

#include <KColorScheme>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KStringHandler>

#include <QLocale>
#include <QMetaProperty>
#include <QSet>

using namespace KAddressBookGrantlee;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_BEGIN_LOOKUP(QUrl)
#else
KTEXTTEMPLATE_BEGIN_LOOKUP(QUrl)
#endif
if (property == QLatin1String("scheme")) {
    return object.scheme();
} else if (property == QLatin1String("path")) {
    return object.path();
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GRANTLEE_END_LOOKUP
#else
KTEXTTEMPLATE_END_LOOKUP
#endif

class KAddressBookGrantlee::GrantleeContactFormatterPrivate
{
public:
    GrantleeContactFormatterPrivate()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        showQRCode = group.readEntry("QRCodes", true);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        mEngine = std::make_unique<GrantleeTheme::Engine>();

        mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader());
#else
        mEngine = std::make_unique<KTextTemplate::Engine>();

        mTemplateLoader = QSharedPointer<KTextTemplate::FileSystemTemplateLoader>(new KTextTemplate::FileSystemTemplateLoader());
#endif
    }

    ~GrantleeContactFormatterPrivate()
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    std::unique_ptr<GrantleeTheme::Engine> mEngine;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mSelfcontainedTemplate;
    Grantlee::Template mEmbeddableTemplate;
#else
    std::unique_ptr<KTextTemplate::Engine> mEngine;
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> mTemplateLoader;
    KTextTemplate::Template mSelfcontainedTemplate;
    KTextTemplate::Template mEmbeddableTemplate;
#endif
    QString mErrorMessage;
    bool forceDisableQRCode = false;
    bool showQRCode = true;
};

GrantleeContactFormatter::GrantleeContactFormatter()
    : d(new GrantleeContactFormatterPrivate)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::registerMetaType<QUrl>();
#else
    KTextTemplate::registerMetaType<QUrl>();
#endif
}

GrantleeContactFormatter::~GrantleeContactFormatter() = default;

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
        return {};
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::Context context(mapping);
#else
    KTextTemplate::Context context(mapping);
#endif
    context.setLocalizer(d->mEngine->localizer());

    if (form == SelfcontainedForm) {
        return d->mSelfcontainedTemplate->render(&context);
    } else if (form == EmbeddableForm) {
        return d->mEmbeddableTemplate->render(&context);
    } else {
        return {};
    }
}

void GrantleeContactFormatter::setApplicationDomain(const QByteArray &domain)
{
    d->mEngine->localizer()->setApplicationDomain(domain);
}
