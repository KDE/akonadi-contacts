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

#include "dialphonenumberaction.h"

#include "contactactionssettings.h"
#include "qdialer.h"
#include "qskypedialer.h"
#ifdef Q_OS_WINCE
#include "qwincedialer.h"
#endif // Q_OS_WINCE

#include <kabc/phonenumber.h>
#include <kconfig.h>
#include <kconfiggroup.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <krun.h>

using namespace Akonadi;

static QString strippedDialNumber( const QString &number )
{
  QString result;

  for ( int i = 0; i < number.length(); ++i ) {
    const QChar character = number.at( i );
    if ( character.isDigit() || ( character == QLatin1Char( '+' ) && i == 0 ) ) {
      result += character;
    }
  }

  return result;
}

void DialPhoneNumberAction::dialNumber( const KABC::PhoneNumber &number )
{
  // synchronize
  ContactActionsSettings::self()->readConfig();

  QDialer *dialer = NULL;
  // we handle skype separated
  if ( ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseSkype ) {
    dialer = new QSkypeDialer( QLatin1String( "AkonadiContacts" ) );
  }
#ifdef Q_OS_WINCE
  else if ( ContactActionsSettings::self()->dialPhoneNumberAction() == ContactActionsSettings::UseWinCE ) {
    dialer = new QWinCEDialer( QLatin1String( "AkonadiContacts" ) );
  }
#endif // Q_OS_WINCE
  if ( dialer ) {
    if ( !dialer->dialNumber( strippedDialNumber( number.number().trimmed() ) ) ) {
      KMessageBox::sorry( 0, dialer->errorMessage() );
    }
    delete dialer;
    return;
  }

  QString command = ContactActionsSettings::self()->phoneCommand();

  if ( command.isEmpty() ) {
    KMessageBox::sorry( 0, i18n( "There is no application set which could be executed. Please go to the settings dialog and configure one." ) );
    return;
  }

  /*
   * %N the raw number
   * %n the number with all additional non-number characters removed
   */
  command = command.replace( QLatin1String( "%N" ), number.number() );
  command = command.replace( QLatin1String( "%n" ), strippedDialNumber( number.number().trimmed() ) );

  KRun::runCommand( command, 0 );
}
