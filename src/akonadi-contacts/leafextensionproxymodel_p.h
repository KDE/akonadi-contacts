/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef LEAFEXTENSIONPROXYMODEL_H
#define LEAFEXTENSIONPROXYMODEL_H

#include <QSortFilterProxyModel>

namespace Akonadi
{
class LeafExtensionProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit LeafExtensionProxyModel(QObject *parent = nullptr);
    ~LeafExtensionProxyModel() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &data, int role = Qt::EditRole) override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex buddy(const QModelIndex &index) const override;
    void fetchMore(const QModelIndex &index) override;

    void setSourceModel(QAbstractItemModel *sourceModel) override;

protected:
    /**
     * This method is called to retrieve the row count for the given leaf @p index.
     */
    virtual int leafRowCount(const QModelIndex &index) const = 0;

    /**
     * This method is called to retrieve the column count for the given leaf @p index.
     */
    virtual int leafColumnCount(const QModelIndex &index) const = 0;

    /**
     * This method is called to retrieve the data of the child of the given leaf @p index
     * at @p row and @p column with the given @p role.
     */
    virtual QVariant leafData(const QModelIndex &index, int row, int column, int role = Qt::DisplayRole) const = 0;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;

    Q_PRIVATE_SLOT(d, void sourceRowsInserted(const QModelIndex &, int, int))
    Q_PRIVATE_SLOT(d, void sourceRowsRemoved(const QModelIndex &, int, int))
    //@endcond
};
}

#endif
