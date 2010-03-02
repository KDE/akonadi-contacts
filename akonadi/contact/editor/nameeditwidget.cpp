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

#include "nameeditwidget.h"

#include "nameeditdialog.h"

#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolButton>

#include <kabc/addressee.h>
#include <kdialog.h>
#include <klineedit.h>
#include <klocale.h>

NameEditWidget::NameEditWidget( QWidget *parent )
  : QWidget( parent )
{
  QHBoxLayout *layout = new QHBoxLayout( this );
  layout->setMargin( 0 );
  layout->setSpacing( KDialog::spacingHint() );

  mNameEdit = new KLineEdit;
  layout->addWidget( mNameEdit );

  QToolButton *button = new QToolButton;
  button->setText( i18n( "..." ) );
  layout->addWidget( button );

  connect( mNameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );
  connect( button, SIGNAL( clicked() ), this, SLOT( openNameEditDialog() ) );
}

NameEditWidget::~NameEditWidget()
{
}

void NameEditWidget::setReadOnly( bool readOnly )
{
  mNameEdit->setReadOnly( readOnly );
}

void NameEditWidget::loadContact( const KABC::Addressee &contact )
{
  mContact = contact;

  disconnect( mNameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );
  mNameEdit->setText( contact.assembledName() );
  connect( mNameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );
}

void NameEditWidget::storeContact( KABC::Addressee &contact ) const
{
  contact.setPrefix( mContact.prefix() );
  contact.setGivenName( mContact.givenName() );
  contact.setAdditionalName( mContact.additionalName() );
  contact.setFamilyName( mContact.familyName() );
  contact.setSuffix( mContact.suffix() );
}

void NameEditWidget::textChanged( const QString &text )
{
  mContact.setNameFromString( text );

  emit nameChanged( mContact );
}

void NameEditWidget::openNameEditDialog()
{
  NameEditDialog dlg( this );

  dlg.setPrefix( mContact.prefix() );
  dlg.setGivenName( mContact.givenName() );
  dlg.setAdditionalName( mContact.additionalName() );
  dlg.setFamilyName( mContact.familyName() );
  dlg.setSuffix( mContact.suffix() );

  if ( dlg.exec() ) {
    mContact.setPrefix( dlg.prefix() );
    mContact.setGivenName( dlg.givenName() );
    mContact.setAdditionalName( dlg.additionalName() );
    mContact.setFamilyName( dlg.familyName() );
    mContact.setSuffix( dlg.suffix() );

    disconnect( mNameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );
    mNameEdit->setText( mContact.assembledName() );
    connect( mNameEdit, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );

    emit nameChanged( mContact );
  }
}

#include "nameeditwidget.moc"
