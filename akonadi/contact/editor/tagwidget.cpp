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

#include "tagwidget.h"

#include "autoqpointer_p.h"
#include "kedittagsdialog_p.h"

#include <kicon.h>
#include <klocale.h>

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>

TagWidget::TagWidget( QWidget *parent )
  : QWidget( parent )
{
  QHBoxLayout *layout = new QHBoxLayout( this );
  mTagLabel = new QLabel;
  mTagLabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );
  layout->addWidget( mTagLabel );

  mEditButton = new QToolButton;
  mEditButton->setText( QLatin1String( "..." ) );
  layout->addWidget( mEditButton, Qt::AlignRight );

  layout->setStretch( 0, 10 );

  connect( mEditButton, SIGNAL( clicked() ), SLOT( editTags() ) );
}

TagWidget::~TagWidget()
{
}

void TagWidget::setTags( const QVector<Nepomuk::Tag> &tags )
{
  mTags = tags;
  updateView();
}

QVector<Nepomuk::Tag> TagWidget::tags() const
{
  return mTags;
}

void TagWidget::editTags()
{
  AutoQPointer<KEditTagsDialog> dlg = new KEditTagsDialog( mTags, this );
  if ( dlg->exec() ) {
    mTags = dlg->tags();
    updateView();
  }
}

void TagWidget::updateView()
{
  QString text;
  foreach ( const Nepomuk::Tag &tag, mTags ) {
    const QString separator = (tag == mTags.last() ? QString() : QLatin1String( ", " ));
    text += tag.genericLabel() + separator;
  }

  mTagLabel->setText( text );
}

#include "tagwidget.h"
