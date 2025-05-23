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
#include <KTextTemplate/Context>
#include <KTextTemplate/MetaType>
#include <KTextTemplate/TemplateLoader>

#include <Akonadi/Item>

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KStringHandler>

#include <QGuiApplication>
#include <QLocale>
#include <QMetaProperty>
#include <QPalette>
#include <QSet>

using namespace KAddressBookGrantlee;

KTEXTTEMPLATE_BEGIN_LOOKUP(QUrl)
if (property == QLatin1StringView("scheme")) {
    return object.scheme();
} else if (property == QLatin1StringView("path")) {
    return object.path();
}
KTEXTTEMPLATE_END_LOOKUP

class KAddressBookGrantlee::GrantleeContactFormatterPrivate
{
public:
    GrantleeContactFormatterPrivate()
    {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        showQRCode = group.readEntry("QRCodes", true);
        mEngine = std::make_unique<GrantleeTheme::Engine>();
        mTemplateLoader = QSharedPointer<KTextTemplate::FileSystemTemplateLoader>(new KTextTemplate::FileSystemTemplateLoader());
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

    QList<QObject *> mObjects;
    std::unique_ptr<GrantleeTheme::Engine> mEngine;
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> mTemplateLoader;
    KTextTemplate::Template mSelfcontainedTemplate;
    KTextTemplate::Template mEmbeddableTemplate;
    QString mErrorMessage;
    bool forceDisableQRCode = false;
    bool showQRCode = true;
};

GrantleeContactFormatter::GrantleeContactFormatter()
    : d(new GrantleeContactFormatterPrivate)
{
    KTextTemplate::registerMetaType<QUrl>();
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
        if (custom.startsWith(QLatin1StringView("KADDRESSBOOK-"))) {
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
                    if (descriptionType == QLatin1StringView("boolean")) {
                        if (value == QLatin1StringView("true")) {
                            value = i18nc("Boolean value", "yes");
                        } else {
                            value = i18nc("Boolean value", "no");
                        }
                    } else if (descriptionType == QLatin1StringView("date")) {
                        const QDate date = QDate::fromString(value, Qt::ISODate);
                        value = QLocale().toString(date, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1StringView("time")) {
                        const QTime time = QTime::fromString(value, Qt::ISODate);
                        value = QLocale::system().toString(time, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1StringView("datetime")) {
                        const QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
                        value = QLocale().toString(dateTime, QLocale::ShortFormat);
                    } else if (descriptionType == QLatin1StringView("url")) {
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

    colorsObject.insert(QStringLiteral("linkColor"), qApp->palette().text().color().name());

    colorsObject.insert(QStringLiteral("textColor"), qApp->palette().text().color().name());

    colorsObject.insert(QStringLiteral("backgroundColor"), qApp->palette().base().color().name());

    QVariantHash mapping;
    mapping.insert(QStringLiteral("contact"), QVariant::fromValue(ContactGrantleeWrapper(rawContact)));
    mapping.insert(QStringLiteral("colors"), colorsObject);
    mapping.insert(QStringLiteral("customFields"), customFields);
    mapping.insert(QStringLiteral("customFieldsUrl"), customFieldsUrl);
    mapping.insert(QStringLiteral("hasqrcode"), !d->forceDisableQRCode && d->showQRCode);
    KTextTemplate::Context context(mapping);
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
