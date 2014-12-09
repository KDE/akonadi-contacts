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

#include "contactviewerdialog.h"
#include "contactviewer.h"
#include "contactdefaultactions.h"

#include <item.h>
using namespace Akonadi;

#include <KConfig>
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QPushButton>

class ContactViewerDialog::Private
{
  public:
    Private( ContactViewerDialog *parent )
      : q( parent ), mViewer( 0 )
    {
    }

    void readConfig()
    {
      KConfig config( QStringLiteral( "akonadi_contactrc" ) );
      KConfigGroup group( &config, QStringLiteral( "ContactViewer" ) );
      const QSize size = group.readEntry( "Size", QSize(500, 600) );
      if ( size.isValid() ) {
        q->resize( size );
      }
    }

    void writeConfig()
    {
      KConfig config( QStringLiteral( "akonadi_contactrc" ) );
      KConfigGroup group( &config, QStringLiteral( "ContactViewer" ) );
      group.writeEntry( "Size", q->size() );
      group.sync();
    }

    ContactViewerDialog *q;
    ContactViewer *mViewer;
};

ContactViewerDialog::ContactViewerDialog( QWidget *parent )
  : QDialog( parent ), d( new Private( this ) )
{
  setWindowTitle( i18n( "Show Contact" ) );
  
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
  QWidget *mainWidget = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
  mainLayout->addWidget(mainWidget);
  QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
  okButton->setDefault(true);
  okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactViewerDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactViewerDialog::reject);

  QVBoxLayout *layout = new QVBoxLayout( mainWidget );

  d->mViewer = new ContactViewer;
  layout->addWidget( d->mViewer );

  ContactDefaultActions *actions = new ContactDefaultActions( this );
  actions->connectToView( d->mViewer );

  mainLayout->addWidget(buttonBox);


  d->readConfig();
}

ContactViewerDialog::~ContactViewerDialog()
{
  d->writeConfig();
  delete d;
}

Akonadi::Item ContactViewerDialog::contact() const
{
  return d->mViewer->contact();
}

ContactViewer* ContactViewerDialog::viewer() const
{
  return d->mViewer;
}

void ContactViewerDialog::setContact( const Akonadi::Item &contact )
{
  d->mViewer->setContact( contact );
}

