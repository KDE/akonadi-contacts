/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QStyledItemDelegate>
class QAbstractItemView;
namespace ContactEditor
{
class CustomFieldsListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomFieldsListDelegate(QAbstractItemView *view, QObject *parent = nullptr);
    ~CustomFieldsListDelegate() override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    void setFirstColumnAsCurrent();
    void removeField(int row, QAbstractItemModel *model);
    const QIcon mIcon;
    QSize mButtonSize;
    QAbstractItemView *const mItemView;
};
}
