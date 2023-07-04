/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QLineEdit>

#include <QStyledItemDelegate>

#include "contactcompletionmodel_p.h"
#include <Akonadi/Item>

#include <memory>

namespace Akonadi
{
class ContactLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ContactLineEdit(bool isReference, Akonadi::ContactCompletionModel::Columns column, QWidget *parent = nullptr);

    bool isReference() const;
    Akonadi::Item completedItem() const;

Q_SIGNALS:
    void completed(QWidget *widget);

private:
    void completed(const QModelIndex &index);
    void slotTextEdited();
    bool mIsReference;
    Akonadi::Item mItem;
};

class ContactGroupEditorDelegatePrivate;

class ContactGroupEditorDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ContactGroupEditorDelegate(QAbstractItemView *view, QObject *parent = nullptr);
    ~ContactGroupEditorDelegate() override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    void completed(QWidget *widget);
    void setFirstColumnAsCurrent();

private:
    std::unique_ptr<ContactGroupEditorDelegatePrivate> const d;
};
}
