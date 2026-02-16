/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <Akonadi/EntityTreeModel>

namespace Akonadi
{
class AKONADI_CONTACT_CORE_EXPORT ContactCompletionModel : public EntityTreeModel
{
    Q_OBJECT

public:
    enum Columns {
        NameColumn, ///< The name of the contact.
        NameAndEmailColumn, ///< The name and the email of the contact.
        EmailColumn ///< The preferred email of the contact.
    };

    /*!
     * Creates a new contact completion model.
     *
     * \a monitor The monitor whose entities should be represented in the model.
     * \a parent The parent object.
     */
    explicit ContactCompletionModel(Monitor *monitor, QObject *parent = nullptr);

    /*!
     * Destroys the contact completion model.
     */
    ~ContactCompletionModel() override;

    [[nodiscard]] QVariant entityData(const Item &item, int column, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QVariant entityData(const Collection &collection, int column, int role = Qt::DisplayRole) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
    [[nodiscard]] int entityColumnCount(HeaderGroup) const override;

    /*!
     * Returns the singleton instance of the contact completion model.
     *
     * \returns The contact completion model instance.
     */
    static QAbstractItemModel *self();

private:
    static QAbstractItemModel *mSelf;
};
}
