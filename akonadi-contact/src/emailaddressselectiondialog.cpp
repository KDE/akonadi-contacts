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

#include "emailaddressselectiondialog.h"

#include <KConfigGroup>

#include <KSharedConfig>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace Akonadi;

class EmailAddressSelectionDialog::Private
{
  public:
    Private( EmailAddressSelectionDialog *qq, QAbstractItemModel *model )
      : q( qq )
    {
      QVBoxLayout *mainLayout = new QVBoxLayout(q);
      if ( model ) {
        mView = new EmailAddressSelectionWidget( model, q );
      } else {
        mView = new EmailAddressSelectionWidget( q );
      }
      mainLayout->addWidget(mView);
      q->connect( mView, SIGNAL(doubleClicked()), q, SLOT(accept()));
      QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
      QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
      okButton->setDefault(true);
      okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
      connect(buttonBox, SIGNAL(accepted()), q, SLOT(accept()));
      connect(buttonBox, SIGNAL(rejected()), q, SLOT(reject()));

      mainLayout->addWidget(buttonBox);
      readConfig();
    }

    void readConfig()
    {
       KConfigGroup group( KSharedConfig::openConfig(), QLatin1String( "EmailAddressSelectionDialog" ) );
       const QSize size = group.readEntry( "Size", QSize() );
       if ( size.isValid() ) {
          q->resize( size );
       } else {
          q->resize( q->sizeHint().width(), q->sizeHint().height() );
       }
    }

    void writeConfig()
    {
        KConfigGroup group( KSharedConfig::openConfig(), QLatin1String( "EmailAddressSelectionDialog" ) );
        group.writeEntry( "Size", q->size() );
    }

    EmailAddressSelectionDialog *q;
    EmailAddressSelectionWidget *mView;
};

EmailAddressSelectionDialog::EmailAddressSelectionDialog( QWidget *parent )
  : QDialog( parent ), d( new Private( this, 0 ) )
{
}

EmailAddressSelectionDialog::EmailAddressSelectionDialog( QAbstractItemModel *model, QWidget *parent )
  : QDialog( parent ), d( new Private( this, model ) )
{
}

EmailAddressSelectionDialog::~EmailAddressSelectionDialog()
{
  d->writeConfig();
  delete d;
}

EmailAddressSelection::List EmailAddressSelectionDialog::selectedAddresses() const
{
  return d->mView->selectedAddresses();
}

EmailAddressSelectionWidget* EmailAddressSelectionDialog::view() const
{
  return d->mView;
}

