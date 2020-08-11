/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CONTACTEDITOR_ADDRESSDELEGATE_H
#define CONTACTEDITOR_ADDRESSDELEGATE_H

#include <QStyledItemDelegate>

namespace ContactEditor {

class AddressDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit AddressDelegate(QObject *parent = nullptr);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

}

#endif // CONTACTEDITOR_ADDRESSDELEGATE_H
