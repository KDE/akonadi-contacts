/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2010 KDAB
    SPDX-FileContributor: Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include "leafextensionproxymodel_p.h"

#include "contactstreemodel.h"

namespace Akonadi
{
class AKONADI_CONTACT_CORE_EXPORT EmailAddressSelectionProxyModel : public Akonadi::LeafExtensionProxyModel
{
    Q_OBJECT

public:
    enum Role {
        NameRole = ContactsTreeModel::DateRole + 1,
        EmailAddressRole
    };

    explicit EmailAddressSelectionProxyModel(QObject *parent = nullptr);
    ~EmailAddressSelectionProxyModel() override;

    [[nodiscard]] QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;

protected:
    /**
     * This method is called to retrieve the row count for the given leaf @p index.
     */
    int leafRowCount(const QModelIndex &index) const override;

    /**
     * This method is called to retrieve the column count for the given leaf @p index.
     */
    int leafColumnCount(const QModelIndex &index) const override;

    /**
     * This method is called to retrieve the data of the child of the given leaf @p index
     * at @p row and @p column with the given @p role.
     */
    QVariant leafData(const QModelIndex &index, int row, int column, int role = Qt::DisplayRole) const override;

private:
};
}
