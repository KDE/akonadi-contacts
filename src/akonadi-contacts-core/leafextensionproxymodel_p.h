/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <QSortFilterProxyModel>

#include <memory>

namespace Akonadi
{
class LeafExtensionProxyModelPrivate;

class AKONADI_CONTACT_CORE_EXPORT LeafExtensionProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    /*!
     * Creates a new leaf extension proxy model.
     *
     * \a parent The parent object.
     */
    explicit LeafExtensionProxyModel(QObject *parent = nullptr);

    /*!
     * Destroys the leaf extension proxy model.
     */
    ~LeafExtensionProxyModel() override;

    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;
    [[nodiscard]] int rowCount(const QModelIndex &index) const override;
    [[nodiscard]] int columnCount(const QModelIndex &index) const override;

    [[nodiscard]] QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &data, int role = Qt::EditRole) override;
    [[nodiscard]] bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QModelIndex buddy(const QModelIndex &index) const override;
    void fetchMore(const QModelIndex &index) override;

    void setSourceModel(QAbstractItemModel *sourceModel) override;

protected:
    /*!
     * This method is called to retrieve the row count for the given leaf \a index.
     */
    virtual int leafRowCount(const QModelIndex &index) const = 0;

    /*!
     * This method is called to retrieve the column count for the given leaf \a index.
     */
    virtual int leafColumnCount(const QModelIndex &index) const = 0;

    /*!
     * This method is called to retrieve the data of the child of the given leaf \a index
     * at \a row and \a column with the given \a role.
     */
    virtual QVariant leafData(const QModelIndex &index, int row, int column, int role = Qt::DisplayRole) const = 0;

private:
    std::unique_ptr<LeafExtensionProxyModelPrivate> const d;

    Q_PRIVATE_SLOT(d, void sourceRowsInserted(const QModelIndex &, int, int))
    Q_PRIVATE_SLOT(d, void sourceRowsRemoved(const QModelIndex &, int, int))
};
}
