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

#include "contactgroupviewerdialog.h"

#include "contactgroupviewer.h"

#include <item.h>
#include <klocalizedstring.h>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QPushButton>

using namespace Akonadi;

class ContactGroupViewerDialog::Private
{
  public:
    ContactGroupViewer *mViewer;
};

ContactGroupViewerDialog::ContactGroupViewerDialog( QWidget *parent )
  : QDialog( parent ), d( new Private )
{
  setWindowTitle( i18n( "Show Contact Group" ) );
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
  QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
  okButton->setDefault(true);
  okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &ContactGroupViewerDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactGroupViewerDialog::reject);

  mainLayout->addWidget(d->mViewer);
  mainLayout->addWidget(buttonBox);

  resize( QSize( 500, 600 ) );
}

ContactGroupViewerDialog::~ContactGroupViewerDialog()
{
  delete d;
}

Akonadi::Item ContactGroupViewerDialog::contactGroup() const
{
  return d->mViewer->contactGroup();
}

ContactGroupViewer* ContactGroupViewerDialog::viewer() const
{
  return d->mViewer;
}

void ContactGroupViewerDialog::setContactGroup( const Akonadi::Item &group )
{
  d->mViewer->setContactGroup( group );
}

