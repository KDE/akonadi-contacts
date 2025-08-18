/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "grantleecontactgroupformatter.h"

#include <GrantleeTheme/GrantleeTheme>

#include <KTextTemplate/Context>
#include <KTextTemplate/Engine>
#include <KTextTemplate/TemplateLoader>

#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/Item>

#include <QGuiApplication>
#include <QPalette>

using namespace KAddressBookGrantlee;

class KAddressBookGrantlee::GrantleeContactGroupFormatterPrivate
{
public:
    GrantleeContactGroupFormatterPrivate()
        : mEngine(new KTextTemplate::Engine)
    {
        mTemplateLoader = QSharedPointer<KTextTemplate::FileSystemTemplateLoader>(new KTextTemplate::FileSystemTemplateLoader);
    }

    ~GrantleeContactGroupFormatterPrivate()
    {
        delete mEngine;
        mTemplateLoader.clear();
    }

    void changeGrantleePath(const QString &path)
    {
        mTemplateLoader->setTemplateDirs(QStringList() << path);
        mEngine->addTemplateLoader(mTemplateLoader);

        mSelfcontainedTemplate = mEngine->loadByName(QStringLiteral("contactgroup.html"));
        if (mSelfcontainedTemplate->error()) {
            mErrorMessage += mSelfcontainedTemplate->errorString() + QStringLiteral("<br>");
        }

        mEmbeddableTemplate = mEngine->loadByName(QStringLiteral("contactgroup_embedded.html"));
        if (mEmbeddableTemplate->error()) {
            mErrorMessage += mEmbeddableTemplate->errorString() + QStringLiteral("<br>");
        }
    }

    KTextTemplate::Engine *const mEngine;
    QSharedPointer<KTextTemplate::FileSystemTemplateLoader> mTemplateLoader;
    KTextTemplate::Template mSelfcontainedTemplate;
    KTextTemplate::Template mEmbeddableTemplate;
    QString mErrorMessage;
};

GrantleeContactGroupFormatter::GrantleeContactGroupFormatter()
    : d(new GrantleeContactGroupFormatterPrivate)
{
}

GrantleeContactGroupFormatter::~GrantleeContactGroupFormatter() = default;

void GrantleeContactGroupFormatter::setAbsoluteThemePath(const QString &path)
{
    d->changeGrantleePath(path);
}

void GrantleeContactGroupFormatter::setGrantleeTheme(const GrantleeTheme::Theme &theme)
{
    d->changeGrantleePath(theme.absolutePath());
}

inline static void setHashField(QVariantHash &hash, const QString &name, const QString &value)
{
    if (!value.isEmpty()) {
        hash.insert(name, value);
    }
}

static QVariantHash memberHash(const KContacts::ContactGroup::Data &data)
{
    QVariantHash memberObject;

    setHashField(memberObject, QStringLiteral("name"), data.name());
    setHashField(memberObject, QStringLiteral("email"), data.email());

    KContacts::Addressee contact;
    contact.setFormattedName(data.name());
    KContacts::Email email(data.email());
    contact.addEmail(email);
    const QString emailLink = QStringLiteral("<a href=\"mailto:") + QString::fromLatin1(QUrl::toPercentEncoding(contact.fullEmail()))
        + QStringLiteral("\">%1</a>").arg(contact.preferredEmail());

    setHashField(memberObject, QStringLiteral("emailLink"), emailLink);

    return memberObject;
}

QString GrantleeContactGroupFormatter::toHtml(HtmlForm form) const
{
    if (!d->mErrorMessage.isEmpty()) {
        return d->mErrorMessage;
    }

    KContacts::ContactGroup group;
    const Akonadi::Item localItem = item();
    if (localItem.isValid() && localItem.hasPayload<KContacts::ContactGroup>()) {
        group = localItem.payload<KContacts::ContactGroup>();
    } else {
        group = contactGroup();
    }

    if (group.name().isEmpty() && group.count() == 0) { // empty group
        return {};
    }

    if (group.contactReferenceCount() != 0) {
        // we got a contact group with unresolved references -> we have to resolve
        // it ourself.  this shouldn't be the normal case, actually the calling
        // code should pass in an already resolved contact group
        auto job = new Akonadi::ContactGroupExpandJob(group);
        if (job->exec()) {
            group.removeAllContactData();
            const KContacts::Addressee::List lstContacts = job->contacts();
            for (const KContacts::Addressee &contact : lstContacts) {
                group.append(KContacts::ContactGroup::Data(contact.realName(), contact.preferredEmail()));
            }
        }
    }

    QVariantHash contactGroupObject;

    setHashField(contactGroupObject, QStringLiteral("name"), group.name());

    // Group members
    QVariantList members;
    const int numberOfData(group.dataCount());
    members.reserve(numberOfData);
    for (int i = 0; i < numberOfData; ++i) {
        members << memberHash(group.data(i));
    }

    contactGroupObject.insert(QStringLiteral("members"), members);

    // Additional fields
    QVariantList fields;
    for (int i = 0; i < additionalFields().size(); ++i) {
        const QVariantMap field = additionalFields().at(i);
        QVariantHash fieldObject;
        setHashField(fieldObject, QStringLiteral("key"), field.value(QStringLiteral("key")).toString());

        setHashField(fieldObject, QStringLiteral("title"), field.value(QStringLiteral("title")).toString());

        setHashField(fieldObject, QStringLiteral("value"), field.value(QStringLiteral("value")).toString());

        fields << fieldObject;
    }

    contactGroupObject.insert(QStringLiteral("additionalFields"), fields);

    QVariantHash colorsObject;
    colorsObject.insert(QStringLiteral("linkColor"), qApp->palette().text().color().name());

    colorsObject.insert(QStringLiteral("textColor"), qApp->palette().text().color().name());

    colorsObject.insert(QStringLiteral("backgroundColor"), qApp->palette().base().color().name());

    QVariantHash mapping;
    mapping.insert(QStringLiteral("contactGroup"), contactGroupObject);
    mapping.insert(QStringLiteral("colors"), colorsObject);
    KTextTemplate::Context context(mapping);

    if (form == SelfcontainedForm) {
        return d->mSelfcontainedTemplate->render(&context);
    } else if (form == EmbeddableForm) {
        return d->mEmbeddableTemplate->render(&context);
    } else {
        return {};
    }
}
