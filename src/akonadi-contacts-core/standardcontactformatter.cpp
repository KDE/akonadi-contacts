/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardcontactformatter.h"

#include <Akonadi/Item>
#include <KConfigGroup>

#include <KContacts/Addressee>

#include <KConfig>
#include <KLocalizedString>
#include <KStringHandler>

#include <QGuiApplication>
#include <QLocale>
#include <QPalette>
#include <QRegularExpression>
#include <QSet>

using namespace Akonadi;

class Akonadi::StandardContactFormatterPrivate
{
public:
    bool displayQRcode = true;
};

StandardContactFormatter::StandardContactFormatter()
    : d(new StandardContactFormatterPrivate())
{
}

StandardContactFormatter::~StandardContactFormatter() = default;

static int contactAge(const QDate &date)
{
    const QDate now = QDate::currentDate();
    int age = now.year() - date.year();
    if (date > now.addYears(-age)) {
        age--;
    }
    return age;
}

QString StandardContactFormatter::toHtml(HtmlForm form) const
{
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

    // We'll be building a table to display the vCard in.
    // Each row of the table will be built using one of these strings for its HTML.

    // single data item:
    //  %1 is the item name
    //  %2 is the item value
    QString rowFmtStr1 = QStringLiteral(
        "<tr valign=\"top\">"
        "<td align=\"right\" valign=\"top\" width=\"30%\"><b><font color=\"grey\">%1</font></b></td>\n"
        "<td colspan=\"2\" align=\"left\" valign=\"top\" width=\"70%\"><font>%2</font></td>\n"
        "</tr>\n");

    // data item plus additional icon(s):
    //  %1 is the item name
    //  %2 is the item value
    //  %3 is the icon(s), each as a HTML <a><img> tag
    QString rowFmtStr2 = QStringLiteral(
        "<tr valign=\"top\">"
        "<td align=\"right\" valign=\"top\" width=\"30%\"><b><font color=\"grey\">%1</font></b></td>\n"
        "<td align=\"left\" valign=\"top\"><font>%2</font></td>\n"
        "<td align=\"left\" valign=\"top\">%3</td>\n"
        "</tr>\n");

    // Build the table's rows here
    QString dynamicPart;

    // Birthday
    const QDate date = rawContact.birthday().date();
    const int years = contactAge(date);

    if (date.isValid()) {
        dynamicPart += rowFmtStr1.arg(KContacts::Addressee::birthdayLabel(),
                                      QLocale().toString(date) + QLatin1StringView("&nbsp;&nbsp;") + i18np("(One year old)", "(%1 years old)", years));
    }

    // Phone Numbers
    const auto phoneNumbers = rawContact.phoneNumbers();
    for (const KContacts::PhoneNumber &number : phoneNumbers) {
        const QString dispLabel = number.typeLabel().replace(u' ', QStringLiteral("&nbsp;"));
        const QString dispValue = QStringLiteral("<a href=\"tel:%1\">%2</a>").arg(number.normalizedNumber()).arg(number.number().toHtmlEscaped());
        if (number.type() & KContacts::PhoneNumber::Cell) {
            const QString dispIcon = QStringLiteral("<a href=\"sms:%1\" title=\"%2\"><img src=\"sms_icon\" align=\"top\"/>")
                                         .arg(number.normalizedNumber())
                                         .arg(i18nc("@info:tooltip", "Send SMS"));
            dynamicPart += rowFmtStr2.arg(dispLabel, dispValue, dispIcon);
        } else {
            dynamicPart += rowFmtStr1.arg(dispLabel, dispValue);
        }
    }

    // EMails
    for (const QString &email : rawContact.emails()) {
        const QString type = i18nc("a contact's email address", "Email");

        const QString fullEmail = QString::fromLatin1(QUrl::toPercentEncoding(rawContact.fullEmail(email)));

        dynamicPart += rowFmtStr1.arg(type, QStringLiteral("<a href=\"mailto:%1\">%2</a>").arg(fullEmail, email));
    }

    // Homepage
    if (rawContact.url().isValid()) {
        QString url = rawContact.url().url().url();
        if (!url.startsWith(QLatin1StringView("http://")) && !url.startsWith(QLatin1StringView("https://"))) {
            url = QLatin1StringView("http://") + url;
        }

        url = KStringHandler::tagUrls(url.toHtmlEscaped());
        dynamicPart += rowFmtStr1.arg(i18n("Homepage"), url);
    }

    // Blog Feed
    const QString blog = rawContact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("BlogFeed"));
    if (!blog.isEmpty()) {
        dynamicPart += rowFmtStr1.arg(i18n("Blog Feed"), KStringHandler::tagUrls(blog.toHtmlEscaped()));
    }

    // Addresses
    const auto addresses = rawContact.addresses();
    for (const KContacts::Address &address : addresses) {
        QString formattedAddress;

        if (address.label().isEmpty()) {
            formattedAddress = address.formatted(KContacts::AddressFormatStyle::Postal).trimmed().toHtmlEscaped();
        } else {
            formattedAddress = address.label().toHtmlEscaped();
        }

        formattedAddress.replace(QRegularExpression(QStringLiteral("\n+")), QStringLiteral("<br>"));

        const QString url = QStringLiteral("<a href=\"%1\" title=\"%2\"><img src=\"map_icon\" alt=\"%2\"/></a>")
                                .arg(address.geoUri().toString())
                                .arg(i18nc("@info:tooltip", "Show address on map"));
        dynamicPart += rowFmtStr2.arg(KContacts::Address::typeLabel(address.type()), formattedAddress, url);
    }

    // Note
    QString notes;
    if (!rawContact.note().isEmpty()) {
        notes = rowFmtStr1.arg(i18n("Notes"), rawContact.note().toHtmlEscaped().replace(u'\n', QLatin1StringView("<br>")));
    }

    // Custom Data
    QString customData;
    static QMap<QString, QString> titleMap;
    if (titleMap.isEmpty()) {
        titleMap.insert(QStringLiteral("Department"), i18n("Department"));
        titleMap.insert(QStringLiteral("Profession"), i18n("Profession"));
        titleMap.insert(QStringLiteral("AssistantsName"), i18n("Assistant's Name"));
        titleMap.insert(QStringLiteral("ManagersName"), i18n("Manager's Name"));
        titleMap.insert(QStringLiteral("SpousesName"), i18nc("Wife/Husband/...", "Partner's Name"));
        titleMap.insert(QStringLiteral("Office"), i18n("Office"));
        titleMap.insert(QStringLiteral("IMAddress"), i18n("IM Address"));
        titleMap.insert(QStringLiteral("Anniversary"), i18n("Anniversary"));
        titleMap.insert(QStringLiteral("AddressBook"), i18n("Address Book"));
        const QMap<QString, QString> tmpTitleMap = titleMap;

        QMap<QString, QString>::const_iterator iterator = tmpTitleMap.constBegin();
        while (iterator != tmpTitleMap.constEnd()) {
            titleMap.insert(iterator.key().toUpper(), iterator.value());
            ++iterator;
        }
    }

    static QSet<QString> blacklistedKeys;
    if (blacklistedKeys.isEmpty()) {
        blacklistedKeys.insert(QStringLiteral("CRYPTOPROTOPREF"));
        blacklistedKeys.insert(QStringLiteral("OPENPGPFP"));
        blacklistedKeys.insert(QStringLiteral("SMIMEFP"));
        blacklistedKeys.insert(QStringLiteral("CRYPTOSIGNPREF"));
        blacklistedKeys.insert(QStringLiteral("CRYPTOENCRYPTPREF"));
        blacklistedKeys.insert(QStringLiteral("MailPreferedFormatting"));
        blacklistedKeys.insert(QStringLiteral("MailAllowToRemoteContent"));
        blacklistedKeys.insert(QStringLiteral("MAILPREFEREDFORMATTING"));
        blacklistedKeys.insert(QStringLiteral("MAILALLOWTOREMOTECONTENT"));
    }

    if (!rawContact.customs().empty()) {
        const QStringList customs = rawContact.customs();
        for (QString custom : customs) {
            if (custom.startsWith(QLatin1StringView("KADDRESSBOOK-"))) {
                custom.remove(QStringLiteral("KADDRESSBOOK-X-"));
                custom.remove(QStringLiteral("KADDRESSBOOK-"));

                int pos = custom.indexOf(u':');
                QString key = custom.left(pos);
                QString value = custom.mid(pos + 1);

                // convert anniversary correctly
                if (key == QLatin1StringView("Anniversary") || key == QLatin1StringView("ANNIVERSARY")) {
                    const QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
                    value = QLocale().toString(dateTime.date());
                } else if (key == QLatin1StringView("BlogFeed") || key == QLatin1StringView("BLOGFEED")) { // blog is handled separated
                    continue;
                } else if (blacklistedKeys.contains(key)) {
                    continue;
                }

                // check whether we have a mapping for the title
                const QMap<QString, QString>::ConstIterator keyIt = titleMap.constFind(key);
                bool needToEscape = true;
                if (keyIt != titleMap.constEnd()) {
                    key = keyIt.value();
                } else {
                    // check whether it is a custom local field
                    for (const QVariantMap &description : customFieldDescriptions()) {
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
                                value = QLocale().toString(time);
                            } else if (descriptionType == QLatin1StringView("datetime")) {
                                const QDateTime dateTime = QDateTime::fromString(value, Qt::ISODate);
                                value = QLocale().toString(dateTime, QLocale::ShortFormat);
                            } else if (descriptionType == QLatin1StringView("url")) {
                                value = KStringHandler::tagUrls(value.toHtmlEscaped());
                                needToEscape = false;
                            }

                            break;
                        }
                    }
                }
                if (needToEscape) {
                    value = value.toHtmlEscaped();
                }
                customData += rowFmtStr1.arg(key, value);
            }
        }
    }

    // Assemble all parts
    QString role = rawContact.title();
    if (role.isEmpty()) {
        role = rawContact.role();
    }
    if (role.isEmpty()) {
        role = rawContact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"));
    }

    QString strAddr =
        QStringLiteral(
            "<div align=\"center\">"
            "<table cellpadding=\"3\" cellspacing=\"1\">"
            "<tr>"
            "<td align=\"right\" valign=\"top\" width=\"30%\" rowspan=\"3\">"
            "<img src=\"%1\" width=\"100\" vspace=\"1\"/>" // image
            "</td>"
            "<td colspan=\"2\" align=\"left\" width=\"70%\"><font size=\"+2\"><b>%2</b></font></td>" // name
            "</tr>"
            "<tr>"
            "<td colspan=\"2\" align=\"left\" width=\"70%\">%3</td>" // role
            "</tr>"
            "<tr>"
            "<td colspan=\"2\" align=\"left\" width=\"70%\">%4</td>" // organization
            "</tr>")
            .arg(QStringLiteral("contact_photo"), rawContact.realName().toHtmlEscaped(), role.toHtmlEscaped(), rawContact.organization().toHtmlEscaped());

    strAddr.append(dynamicPart);
    strAddr.append(notes);
    strAddr.append(customData);
    strAddr.append(QLatin1StringView("</table>"));

    if (d->displayQRcode) {
        KConfig config(QStringLiteral("akonadi_contactrc"));
        KConfigGroup group(&config, QStringLiteral("View"));
        if (group.readEntry("QRCodes", true)) {
            strAddr.append(QString::fromLatin1("<p align=\"center\">"
                                               "<img src=\"%1\" vspace=\"1\"/>"
                                               "</p>")
                               .arg(QStringLiteral("qrcode")));
        }
    }

    strAddr.append(QLatin1StringView("</div>\n"));

    if (form == EmbeddableForm) {
        return strAddr;
    }

    const QString document = QStringLiteral(
                                 "<html>"
                                 "<head>"
                                 " <style type=\"text/css\">"
                                 "  a {text-decoration:none; color:%1}"
                                 " </style>"
                                 "</head>"
                                 "<body text=\"%1\" bgcolor=\"%2\">" // text and background color
                                 "%3" // contact part
                                 "</body>"
                                 "</html>")
                                 .arg(qApp->palette().text().color().name(), qApp->palette().base().color().name(), strAddr);

    return document;
}

void StandardContactFormatter::setDisplayQRCode(bool show)
{
    d->displayQRcode = show;
}

bool StandardContactFormatter::displayQRCode() const
{
    return d->displayQRcode;
}
