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

#include "imeditwidget.h"

#include "im/imeditordialog.h"
#include "im/improtocols.h"

#include <QtCore/QPointer>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolButton>

#include <kabc/addressee.h>
#include <klineedit.h>
#include <klocale.h>

static void splitCustomField( const QString &str, QString &app, QString &name, QString &value )
{
  const int colon = str.indexOf( QLatin1Char( ':' ) );
  if ( colon != -1 ) {
    const QString tmp = str.left( colon );
    value = str.mid( colon + 1 );

    const int dash = tmp.indexOf( QLatin1Char( '-' ) );
    if ( dash != -1 ) {
      app = tmp.left( dash );
      name = tmp.mid( dash + 1 );
    }
  }
}

IMEditWidget::IMEditWidget( QWidget *parent )
  : QWidget( parent )
{
  QHBoxLayout *layout = new QHBoxLayout( this );
  layout->setMargin( 0 );

  mIMEdit = new KLineEdit;
  layout->addWidget( mIMEdit );

  mEditButton = new QToolButton;
  mEditButton->setText( i18n( "..." ) );
  layout->addWidget( mEditButton );

  connect( mEditButton, SIGNAL( clicked() ), SLOT( edit() ) );
}

IMEditWidget::~IMEditWidget()
{
}

void IMEditWidget::loadContact( const KABC::Addressee &contact )
{
  mIMEdit->setText( contact.custom( QLatin1String( "KADDRESSBOOK" ), QLatin1String( "X-IMAddress" ) ) );

  const QStringList customs = contact.customs();

  foreach ( const QString &custom, customs ) {
    QString app, name, value;
    splitCustomField( custom, app, name, value );

    if ( app.startsWith( QLatin1String( "messaging/" ) ) ) {
      if ( name == QLatin1String( "All" ) ) {
        const QString protocol = app;
        const QStringList names = value.split( QChar( 0xE000 ), QString::SkipEmptyParts );

        foreach ( const QString &name, names )
          mIMAddresses << IMAddress( protocol, name, (name == mIMEdit->text()) );
      }
    }
  }
}

void IMEditWidget::storeContact( KABC::Addressee &contact ) const
{
  if ( !mIMEdit->text().isEmpty() )
    contact.insertCustom( QLatin1String( "KADDRESSBOOK" ), QLatin1String( "X-IMAddress" ), mIMEdit->text() );
  else
    contact.removeCustom( QLatin1String( "KADDRESSBOOK" ), QLatin1String( "X-IMAddress" ) );

  // create a map with protocol as key and list of names for that protocol as value
  QMap<QString, QStringList> protocolMap;

  // fill map with all known protocols
  foreach ( const QString &protocol, IMProtocols::self()->protocols() )
    protocolMap.insert( protocol, QStringList() );

  // add the configured addresses
  foreach ( const IMAddress &address, mIMAddresses )
    protocolMap[ address.protocol() ].append( address.name() );

  // iterate over this list and modify the contact according
  QMapIterator<QString, QStringList> it( protocolMap );
  while ( it.hasNext() ) {
    it.next();

    if ( !it.value().isEmpty() ) {
      contact.insertCustom( it.key(), QLatin1String( "All" ), it.value().join( QString( 0xE000 ) ) );
    } else {
      contact.removeCustom( it.key(), QLatin1String( "All" ) );
    }
  }
}

void IMEditWidget::setReadOnly( bool readOnly )
{
  mIMEdit->setReadOnly( readOnly );
  mEditButton->setEnabled( !readOnly );
}

void IMEditWidget::edit()
{
  QPointer<IMEditorDialog> dlg = new IMEditorDialog( this );
  dlg->setAddresses( mIMAddresses );

  if ( dlg->exec() == QDialog::Accepted ) {
    mIMAddresses = dlg->addresses();

    foreach ( const IMAddress &address, mIMAddresses ) {
      if ( address.preferred() ) {
        mIMEdit->setText( address.name() );
        break;
      }
    }
  }

  delete dlg;
}

#include "imeditwidget.moc"
