/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardcontactgroupformatter.h"

#include "job/contactgroupexpandjob.h"
#include <KColorScheme>
#include <item.h>
#include <kcontacts/addressee.h>

using namespace Akonadi;

StandardContactGroupFormatter::StandardContactGroupFormatter()
    : d(nullptr)
{
}

StandardContactGroupFormatter::~StandardContactGroupFormatter()
{
}

QString StandardContactGroupFormatter::toHtml(HtmlForm form) const
{
    KContacts::ContactGroup group;
    const Akonadi::Item localItem = item();
    if (localItem.isValid() && localItem.hasPayload<KContacts::ContactGroup>()) {
        group = localItem.payload<KContacts::ContactGroup>();
    } else {
        group = contactGroup();
    }

    if (group.name().isEmpty() && group.count() == 0) { // empty group
        return QString();
    }

    if (group.contactReferenceCount() != 0) {
        // we got a contact group with unresolved references -> we have to resolve it ourself
        // this shouldn't be the normal case, actually the calling code should pass in an already resolved
        // contact group
        auto job = new ContactGroupExpandJob(group);
        if (job->exec()) {
            group.removeAllContactData();
            const KContacts::Addressee::List listContact = job->contacts();
            for (const KContacts::Addressee &contact : listContact) {
                group.append(KContacts::ContactGroup::Data(contact.realName(), contact.preferredEmail()));
            }
        }
    }

    // Assemble all parts
    QString strGroup = QStringLiteral(
                           "<table cellpadding=\"3\" cellspacing=\"0\" width=\"100%\">"
                           "<tr>"
                           "<td align=\"right\" valign=\"top\" width=\"30%\">"
                           "<img src=\"%1\" width=\"100\" vspace=\"1\">" // image
                           "</td>"
                           "<td align=\"left\" width=\"70%\"><font size=\"+2\"><b>%2</b></font></td>" // name
                           "</tr>"
                           "</table>")
                           .arg(QStringLiteral("group_photo"), group.name());

    strGroup += QLatin1String("<table width=\"100%\">");

    for (int i = 0; i < group.dataCount(); ++i) {
        const KContacts::ContactGroup::Data data = group.data(i);

        if (data.email().isEmpty()) {
            strGroup.append(QStringLiteral("<tr><td align=\"right\" width=\"50%\"><b><font color=\"grey\">%1</font></b></td>"
                                           "<td width=\"50%\"></td></tr>")
                                .arg(data.name()));
        } else {
            KContacts::Addressee contact;
            contact.setFormattedName(data.name());
            contact.insertEmail(data.email());

            const QString fullEmail = QLatin1String("<a href=\"mailto:") + QString::fromLatin1(QUrl::toPercentEncoding(contact.fullEmail()))
                + QStringLiteral("\">%1</a>").arg(contact.preferredEmail());

            strGroup.append(QStringLiteral("<tr><td align=\"right\" width=\"50%\"><b><font color=\"grey\">%1</font></b></td>"
                                           "<td valign=\"bottom\" align=\"left\" width=\"50%\"><font>&lt;%2&gt;</font></td></tr>")
                                .arg(contact.realName(), fullEmail));
        }
    }

    const auto additionalFieldsLst = additionalFields();
    for (const QVariantMap &map : additionalFieldsLst) {
        strGroup.append(QStringLiteral("<tr><td colspan=\"2\">&nbsp;</td></tr><tr><td align=\"right\" width=\"30%\"><b><font color=\"grey\">%1</font></b></td>"
                                       "<td valign=\"bottom\" align=\"left\" width=\"50%\"><font>%2</font></td></tr>")
                            .arg(map.value(QStringLiteral("title")).toString(), map.value(QStringLiteral("value")).toString()));
    }

    strGroup.append(QLatin1String("</table>\n"));

    QString document = QStringLiteral("<div align=\"center\">%1</div>").arg(strGroup);

    if (form == EmbeddableForm) {
        return document;
    }

    document = QStringLiteral(
                   "<html>"
                   "<head>"
                   " <style type=\"text/css\">"
                   "  a {text-decoration:none; color:%1}"
                   " </style>"
                   "</head>"
                   "<body text=\"%1\" bgcolor=\"%2\">" // text and background color
                   "%3" // contact group part
                   "</body>"
                   "</html>")
                   .arg(KColorScheme(QPalette::Active, KColorScheme::View).foreground().color().name(),
                        KColorScheme(QPalette::Active, KColorScheme::View).background().color().name(),
                        document);

    return document;
}
