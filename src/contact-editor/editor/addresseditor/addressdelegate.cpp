/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
