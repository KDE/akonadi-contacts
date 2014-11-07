/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 KDAB
    Author: Tobias Koenig <tokoe@kde.org>

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

#include "emailaddressselectionproxymodel_p.h"

#include <item.h>
#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>
#include <klocalizedstring.h>

using namespace Akonadi;

static QString createToolTip( const KContacts::ContactGroup &group )
{
  QString txt = QLatin1String( "<qt>" );

  txt += QString::fromLatin1( "<b>%1</b>" ).arg( i18n( "Distribution List %1", group.name() ) );
  txt += QLatin1String( "<ul>" );
  const uint groupDataCount( group.dataCount() );
  for ( uint i = 0; i < groupDataCount; ++i ) {
    txt += QLatin1String( "<li>" );
    txt += group.data( i ).name() + QLatin1Char( ' ' );
    txt += QLatin1String( "<em>" );
    txt += group.data( i ).email();
    txt += QLatin1String( "</em></li>" );
  }
  txt += QLatin1String( "</ul>" );
  txt += QLatin1String( "</qt>" );

  return txt;
}

static QString createToolTip( const QString &name, const QString &email )
{
  return QString::fromLatin1( "<qt>%1<b>%2</b></qt>" )
      .arg( name.isEmpty() ? QString() : name + QLatin1String( "<br/>" ) )
      .arg( email );
}

EmailAddressSelectionProxyModel::EmailAddressSelectionProxyModel( QObject *parent )
  : LeafExtensionProxyModel( parent )
{
}

EmailAddressSelectionProxyModel::~EmailAddressSelectionProxyModel()
{
}

QVariant EmailAddressSelectionProxyModel::data( const QModelIndex &index, int role ) const
{
  const QVariant value = LeafExtensionProxyModel::data( index, role );

  if ( !value.isValid() ) { // index is not a leaf child
    if ( role == NameRole ) {
      const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
      if ( item.hasPayload<KContacts::Addressee>() ) {
        const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
        return contact.realName();
      } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
        const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
        return group.name();
      }
    } else if ( role == EmailAddressRole ) {
      const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
      if ( item.hasPayload<KContacts::Addressee>() ) {
        const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
        return contact.preferredEmail();
      } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
        const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
        return group.name(); // the name must be resolved by the caller
      }
    } else if ( role == Qt::ToolTipRole ) {
      const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
      if ( item.hasPayload<KContacts::Addressee>() ) {
        const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
        return createToolTip( contact.realName(), contact.preferredEmail() );
      } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
        return createToolTip( item.payload<KContacts::ContactGroup>() );
      }
    }
  }

  return value;
}

int EmailAddressSelectionProxyModel::leafRowCount( const QModelIndex &index ) const
{
  const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
  if ( item.hasPayload<KContacts::Addressee>() ) {
    const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
    if ( contact.emails().count() == 1 ) {
      return 0;
    } else {
      return contact.emails().count();
    }
  } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
    const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
    return group.dataCount();
  } else {
    return 0;
  }
}

int EmailAddressSelectionProxyModel::leafColumnCount( const QModelIndex &index ) const
{
  const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
  if ( item.hasPayload<KContacts::Addressee>() ) {
    return 1;
  } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
    return 1;
  } else {
    return 0;
  }
}

QVariant EmailAddressSelectionProxyModel::leafData( const QModelIndex &index, int row, int, int role ) const
{
  if ( role == Qt::DisplayRole ) {
    const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
    if ( item.hasPayload<KContacts::Addressee>() ) {
      const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
      if ( row >= 0 && row < contact.emails().count() ) {
        return contact.emails().at( row );
      }
    } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
      const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
      if ( row >= 0 && row < (int)group.dataCount() ) {
        return i18nc( "Name and email address of a contact", "%1 <%2>",
                      group.data( row ).name(), group.data( row ).email() );
      }
    }
  } else if ( role == NameRole ) {
    const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
    if ( item.hasPayload<KContacts::Addressee>() ) {
      const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
      return contact.realName();
    } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
      const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
      if ( row >= 0 && row < (int)group.dataCount() ) {
        return group.data( row ).name();
      }
    }
  } else if ( role == EmailAddressRole ) {
    const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
    if ( item.hasPayload<KContacts::Addressee>() ) {
      const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
      if ( row >= 0 && row < contact.emails().count() ) {
        return contact.emails().at( row );
      }
    } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
      const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
      if ( row >= 0 && row < (int)group.dataCount() ) {
        return group.data( row ).email();
      }
    }
  } else if ( role == Qt::ToolTipRole ) {
    const Akonadi::Item item = index.data( ContactsTreeModel::ItemRole ).value<Akonadi::Item>();
    if ( item.hasPayload<KContacts::Addressee>() ) {
      const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
      if ( row >= 0 && row < contact.emails().count() ) {
        return createToolTip( contact.realName(), contact.emails().at( row ) );
      }
    } else if ( item.hasPayload<KContacts::ContactGroup>() ) {
      const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
      if ( row >= 0 && row < (int)group.dataCount() ) {
        return createToolTip( group.data( row ).name(), group.data( row ).email() );
      }
    }
  } else
    return index.data( role );

  return QVariant();
}
