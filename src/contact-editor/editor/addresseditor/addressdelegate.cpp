/*
    This file is part of Contact Editor.

    Copyright (C) 2019 Volker Krause <vkrause@kde.org>

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

#include "addressdelegate.h"

#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QTextDocument>

using namespace ContactEditor;

AddressDelegate::AddressDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QSize AddressDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    QTextDocument doc;
    doc.setHtml(options.text);
    doc.setTextWidth(options.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}

void AddressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    painter->save();
    QTextDocument doc;
    doc.setHtml(options.text);
    options.text = QString();
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);
    painter->translate(options.rect.left(), options.rect.top());

    const QRect clip(0, 0, options.rect.width(), options.rect.height());
    QAbstractTextDocumentLayout::PaintContext ctx;
    ctx.clip = clip;
    if (option.state & QStyle::State_Selected) {
        ctx.palette.setColor(QPalette::Text, options.palette.color(QPalette::HighlightedText));
    }
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}
