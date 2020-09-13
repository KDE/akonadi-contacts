/*
   SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "config-akonadi-contact.h"
#include "contactgrantleewrapper.h"
#ifdef HAVE_KLEO
#include <Libkleo/Enum>
#endif
#include <KLocalizedString>

#include <QBuffer>
#include <QImage>
#include <QLocale>

using namespace KAddressBookGrantlee;

static_assert(sizeof(KContacts::Addressee) == sizeof(KAddressBookGrantlee::ContactGrantleeWrapper), "Grantlee wrapper must not have member variables to prevent slicing issues");

ContactGrantleeWrapper::ContactGrantleeWrapper() = default;

ContactGrantleeWrapper::ContactGrantleeWrapper(const KContacts::Addressee& addr)
    : KContacts::Addressee(addr)
{
}

QString ContactGrantleeWrapper::addressBookLabel() const
{
    return i18n("Address Book");
}

QString ContactGrantleeWrapper::anniversaryLabel() const
{
    return i18n("Anniversary");
}

QString ContactGrantleeWrapper::assistantLabel() const
{
    return i18n("Assistant's Name");
}

QString ContactGrantleeWrapper::managerLabel() const
{
    return i18n("Manager's Name");
}

QString ContactGrantleeWrapper::officeLabel() const
{
    return i18n("Office");
}

QString ContactGrantleeWrapper::professionLabel() const
{
    return i18n("Profession");
}

QString ContactGrantleeWrapper::spouseLabel() const
{
    return i18nc("Wife/Husband/...", "Partner's Name");
}

QString ContactGrantleeWrapper::addressBookName() const
{
    return custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("AddressBook"));
}

int ContactGrantleeWrapper::age() const
{
    QDate now = QDate::currentDate();
    int age = now.year() - birthday().date().year();
    if (birthday().date() > now.addYears(-age)) {
        age--;
    }
    return age;
}

QString ContactGrantleeWrapper::cryptoPreference() const
{
#ifdef HAVE_KLEO
    return Kleo::encryptionPreferenceToLabel(Kleo::stringToEncryptionPreference(custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOENCRYPTPREF"))));
#else
    return custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOENCRYPTPREF"));
#endif
}

QString ContactGrantleeWrapper::signaturePreference() const
{
#ifdef HAVE_KLEO
    return Kleo::signingPreferenceToLabel(Kleo::stringToSigningPreference(custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"))));
#else
    custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"));
#endif
}

static QString imgToDataUrl(const QImage &image)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return QStringLiteral("data:image/%1;base64,%2").arg(QStringLiteral("PNG"), QString::fromLatin1(ba.toBase64()));
}

QString ContactGrantleeWrapper::logoImgElement() const
{
    if (logo().isEmpty()) {
        return {};
    }
    return QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;").arg(imgToDataUrl(logo().data()), QString::number(60), QString::number(60));
}

QString ContactGrantleeWrapper::photoImgElement() const
{
    if (photo().isEmpty()) {
        return {};
    }
    return QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"> &nbsp;").arg(imgToDataUrl(photo().data()), QString::number(60), QString::number(60));
}

QString ContactGrantleeWrapper::formattedBirthday() const
{
    return QLocale().toString(birthday().date());
}

QString ContactGrantleeWrapper::formattedAnniversary() const
{
    return QLocale().toString(anniversary());
}

#include "moc_contactgrantleewrapper.cpp"
