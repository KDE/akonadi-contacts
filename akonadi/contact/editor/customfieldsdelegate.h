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

#ifndef CUSTOMFIELDSDELEGATE_H
#define CUSTOMFIELDSDELEGATE_H

#include <QtGui/QStyledItemDelegate>

class CustomFieldsDelegate : public QStyledItemDelegate
{
  public:
    explicit CustomFieldsDelegate( QObject *parent = 0 );
    ~CustomFieldsDelegate();

    virtual QWidget* createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    virtual void setEditorData( QWidget *editor, const QModelIndex &index ) const;
    virtual void setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const;
    virtual void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif
