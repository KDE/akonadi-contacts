/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#include "standardcontactformatter.h"

#include <akonadi/item.h>
#include <kabc/addressee.h>
#include <kcolorscheme.h>
#include <kconfiggroup.h>
#include <kglobal.h>
#include <klocale.h>
#include <kstringhandler.h>

#include <QtCore/QSet>
#include <QTextDocument>

using namespace Akonadi;

class StandardContactFormatter::Private
{
public:
  Private()
   :displayQRcode(true)
  {

  }

  bool displayQRcode;
};

StandardContactFormatter::StandardContactFormatter()
  : d( new Private() )
{
}

StandardContactFormatter::~StandardContactFormatter()
{
  delete d;
}

static int contactAge( const QDate &date )
{
  QDate now = QDate::currentDate();
  int age = now.year() - date.year();
  if ( date > now.addYears( -age ) ) {
    age--;
  }
  return age;
}

QString StandardContactFormatter::toHtml( HtmlForm form ) const
{
  KABC::Addressee rawContact;
  const Akonadi::Item localItem = item();
  if ( localItem.isValid() && localItem.hasPayload<KABC::Addressee>() ) {
    rawContact = localItem.payload<KABC::Addressee>();
  } else {
    rawContact = contact();
  }

  if ( rawContact.isEmpty() ) {
    return QString();
  }

  // We'll be building a table to display the vCard in.
  // Each row of the table will be built using this string for its HTML.

  QString rowFmtStr = QString::fromLatin1(
        "<tr>"
        "<td align=\"right\" valign=\"top\" width=\"30%\"><b><font color=\"grey\">%1</font></b></td>\n"
        "<td align=\"left\" valign=\"top\" width=\"70%\"><font>%2</font></td>\n"
        "</tr>\n"
        );

  // Build the table's rows here
  QString dynamicPart;

  // Birthday
  const QDate date = rawContact.birthday().date();
  const int years = contactAge( date );

  if ( date.isValid() ) {
    dynamicPart += rowFmtStr
      .arg( KABC::Addressee::birthdayLabel() )
      .arg( KGlobal::locale()->formatDate( date ) +
            QLatin1String( "&nbsp;&nbsp;" ) + i18np( "(One year old)", "(%1 years old)", years ) );
  }

  // Phone Numbers
  int counter = 0;
  foreach ( const KABC::PhoneNumber &number, rawContact.phoneNumbers() ) {

      QString url;
      if ( number.type() & KABC::PhoneNumber::Cell ) {
        url = QString::fromLatin1( "<a href=\"phone:?index=%1\">%2</a> (<a href=\"sms:?index=%1\">SMS</a>)" ).arg( counter ).arg( Qt::escape( number.number() ) );
      } else {
        url = QString::fromLatin1( "<a href=\"phone:?index=%1\">%2</a>" ).arg( counter ).arg( Qt::escape( number.number() ) );
      }

      counter++;

      dynamicPart += rowFmtStr
        .arg( number.typeLabel().replace( QLatin1String( " " ), QLatin1String( "&nbsp;" ) ) )
        .arg( url );
  }

  // EMails
  foreach ( const QString &email, rawContact.emails() ) {
    const QString type = i18nc( "a contact's email address", "Email" );

    const QString fullEmail = QString::fromLatin1( KUrl::toPercentEncoding( rawContact.fullEmail( email ) ) );

    dynamicPart += rowFmtStr.arg( type )
      .arg( QString::fromLatin1( "<a href=\"mailto:%1\">%2</a>" )
      .arg( fullEmail, email ) );
  }

  // Homepage
  if ( rawContact.url().isValid() ) {
    QString url = rawContact.url().url();
    if ( !url.startsWith( QLatin1String( "http://" ) ) && !url.startsWith( QLatin1String( "https://" ) ) ) {
      url = QLatin1String( "http://" ) + url;
    }

    url = KStringHandler::tagUrls( Qt::escape( url ) );
    dynamicPart += rowFmtStr.arg( i18n( "Homepage" ) ).arg( url );
  }

  // Blog Feed
  const QString blog = rawContact.custom( QLatin1String( "KADDRESSBOOK" ), QLatin1String( "BlogFeed" ) );
  if ( !blog.isEmpty() ) {
    dynamicPart += rowFmtStr.arg( i18n( "Blog Feed" ) ).arg( KStringHandler::tagUrls( Qt::escape( blog ) ) );
  }

  // Addresses
  counter = 0;
  foreach ( const KABC::Address &address, rawContact.addresses() ) {
    QString formattedAddress;

    if ( address.label().isEmpty() ) {
      formattedAddress = Qt::escape( address.formattedAddress().trimmed() );
    } else {
      formattedAddress = Qt::escape( address.label() );
    }

    formattedAddress = formattedAddress.replace( QLatin1Char( '\n' ), QLatin1String( "<br>" ) );

    const QString url = QString::fromLatin1( "%1 <a href=\"address:?index=%2\"><img src=\"map_icon\" alt=\"%3\"/></a>" )
                                           .arg( formattedAddress )
                                           .arg( counter )
                                           .arg( i18n( "Show address on map" ) );
    counter++;

    dynamicPart += rowFmtStr
      .arg( KABC::Address::typeLabel( address.type() ) )
      .arg( url );
  }

  // Note
  QString notes;
  if ( !rawContact.note().isEmpty() ) {
    notes = rowFmtStr.arg( i18n( "Notes" ) ).arg( Qt::escape( rawContact.note() ).replace( QLatin1Char( '\n' ), QLatin1String( "<br>" ) ) ) ;
  }

  // Custom Data
  QString customData;
  static QMap<QString, QString> titleMap;
  if ( titleMap.isEmpty() ) {
    titleMap.insert( QLatin1String( "Department" ), i18n( "Department" ) );
    titleMap.insert( QLatin1String( "Profession" ), i18n( "Profession" ) );
    titleMap.insert( QLatin1String( "AssistantsName" ), i18n( "Assistant's Name" ) );
    titleMap.insert( QLatin1String( "ManagersName" ), i18n( "Manager's Name" ) );
    titleMap.insert( QLatin1String( "SpousesName" ), i18nc( "Wife/Husband/...", "Partner's Name" ) );
    titleMap.insert( QLatin1String( "Office" ), i18n( "Office" ) );
    titleMap.insert( QLatin1String( "IMAddress" ), i18n( "IM Address" ) );
    titleMap.insert( QLatin1String( "Anniversary" ), i18n( "Anniversary" ) );
    titleMap.insert( QLatin1String( "AddressBook" ), i18n( "Address Book" ) );
  }

  static QSet<QString> blacklistedKeys;
  if ( blacklistedKeys.isEmpty() ) {
    blacklistedKeys.insert( QLatin1String( "CRYPTOPROTOPREF" ) );
    blacklistedKeys.insert( QLatin1String( "OPENPGPFP" ) );
    blacklistedKeys.insert( QLatin1String( "SMIMEFP" ) );
    blacklistedKeys.insert( QLatin1String( "CRYPTOSIGNPREF" ) );
    blacklistedKeys.insert( QLatin1String( "CRYPTOENCRYPTPREF" ) );
    blacklistedKeys.insert( QLatin1String( "MailPreferedFormatting" ) );
    blacklistedKeys.insert( QLatin1String( "MailAllowToRemoteContent" ) );
  }

  if ( !rawContact.customs().empty() ) {
    const QStringList customs = rawContact.customs();
    foreach ( QString custom, customs ) { //krazy:exclude=foreach
      if ( custom.startsWith( QLatin1String( "KADDRESSBOOK-" ) ) ) {
        custom.remove( QLatin1String( "KADDRESSBOOK-X-" ) );
        custom.remove( QLatin1String( "KADDRESSBOOK-" ) );

        int pos = custom.indexOf( QLatin1Char( ':' ) );
        QString key = custom.left( pos );
        QString value = custom.mid( pos + 1 );

        // convert anniversary correctly
        if ( key == QLatin1String( "Anniversary" ) || key == QLatin1String( "ANNIVERSARY" ) ) {
          const QDateTime dateTime = QDateTime::fromString( value, Qt::ISODate );
          value = KGlobal::locale()->formatDate( dateTime.date() );
        } else if ( key == QLatin1String( "BlogFeed" ) ) {  // blog is handled separated
          continue;
        } else if ( blacklistedKeys.contains( key ) ) {
          continue;
        }

        // check whether we have a mapping for the title
        const QMap<QString, QString>::ConstIterator keyIt = titleMap.constFind( key );
        if ( keyIt != titleMap.constEnd() ) {
          key = keyIt.value();
        } else {
          // check whether it is a custom local field
          foreach ( const QVariantMap &description, customFieldDescriptions() ) {
            if ( description.value( QLatin1String( "key" ) ).toString() == key ) {
              key = description.value( QLatin1String( "title" ) ).toString();
              if ( description.value( QLatin1String( "type" ) ) == QLatin1String( "boolean" ) ) {
                if ( value == QLatin1String( "true" ) ) {
                  value = i18nc( "Boolean value", "yes" );
                } else {
                  value = i18nc( "Boolean value", "no" );
                }
              } else if ( description.value( QLatin1String( "type" ) ) == QLatin1String( "date" ) ) {
                const QDate date = QDate::fromString( value, Qt::ISODate );
                value = KGlobal::locale()->formatDate( date, KLocale::ShortDate );
              } else if ( description.value( QLatin1String( "type" ) ) == QLatin1String( "time" ) ) {
                const QTime time = QTime::fromString( value, Qt::ISODate );
                value = KGlobal::locale()->formatTime( time );
              } else if ( description.value( QLatin1String( "type" ) ) == QLatin1String( "datetime" ) ) {
                const QDateTime dateTime = QDateTime::fromString( value, Qt::ISODate );
                value = KGlobal::locale()->formatDateTime( dateTime, KLocale::ShortDate );
              }
              break;
            }
          }
        }

        customData += rowFmtStr.arg( key ).arg( Qt::escape( value ) ) ;
      }
    }
  }

  // Assemble all parts
  QString role = rawContact.title();
  if ( role.isEmpty() ) {
    role = rawContact.role();
  }
  if ( role.isEmpty() ) {
    role = rawContact.custom( QLatin1String( "KADDRESSBOOK" ), QLatin1String( "X-Profession" ) );
  }

  QString strAddr = QString::fromLatin1(
    "<div align=\"center\">"
    "<table cellpadding=\"3\" cellspacing=\"0\">"
    "<tr>"
    "<td align=\"right\" valign=\"top\" width=\"30%\" rowspan=\"3\">"
    "<img src=\"%1\" width=\"100\" vspace=\"1\">" // image
    "</td>"
    "<td align=\"left\" width=\"70%\"><font size=\"+2\"><b>%2</b></font></td>" // name
    "</tr>"
    "<tr>"
    "<td align=\"left\" width=\"70%\">%3</td>"  // role
    "</tr>"
    "<tr>"
    "<td align=\"left\" width=\"70%\">%4</td>"  // organization
    "</tr>")
      .arg( QLatin1String( "contact_photo" ) )
      .arg( Qt::escape( rawContact.realName() ) )
      .arg( Qt::escape( role ) )
      .arg( Qt::escape( rawContact.organization() ) );

  strAddr.append( dynamicPart );
  strAddr.append( notes );
  strAddr.append( customData );
  strAddr.append( QString::fromLatin1( "</table>" ) );

#ifdef HAVE_PRISON
  if(d->displayQRcode) {
    KConfig config( QLatin1String( "akonadi_contactrc" ) );
    KConfigGroup group( &config, QLatin1String( "View" ) );
    if ( group.readEntry( "QRCodes", true ) ) {
      strAddr.append( QString::fromLatin1(
        "<p align=\"center\">"
        "<img src=\"%1\" vspace=\"1\">"
        "<img src=\"%2\" vspace=\"1\">"
        "</p>"
      )
      .arg( QLatin1String( "datamatrix" ) )
      .arg( QLatin1String( "qrcode" ) ) );
    }
  }
#endif // HAVE_PRISON

  strAddr.append( QString::fromLatin1( "</div>\n" ) );

  if ( form == EmbeddableForm ) {
    return strAddr;
  }

  const QString document = QString::fromLatin1(
    "<html>"
    "<head>"
    " <style type=\"text/css\">"
    "  a {text-decoration:none; color:%1}"
    " </style>"
    "</head>"
    "<body text=\"%1\" bgcolor=\"%2\">" // text and background color
    "%3" // contact part
    "</body>"
    "</html>" )
     .arg( KColorScheme( QPalette::Active, KColorScheme::View ).foreground().color().name() )
     .arg( KColorScheme( QPalette::Active, KColorScheme::View ).background().color().name() )
     .arg( strAddr );

  return document;
}

void StandardContactFormatter::setDisplayQRCode( bool show )
{
  d->displayQRcode = show;
}

bool StandardContactFormatter::displayQRCode() const
{
  return d->displayQRcode;
}

