/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef AKONADI_CONTACTCOMPLETIONMODEL_P_H
#define AKONADI_CONTACTCOMPLETIONMODEL_P_H

#include <entitytreemodel.h>

namespace Akonadi {
class ContactCompletionModel : public EntityTreeModel
{
    Q_OBJECT

public:
    enum Columns {
        NameColumn,         ///< The name of the contact.
        NameAndEmailColumn, ///< The name and the email of the contact.
        EmailColumn         ///< The preferred email of the contact.
    };

    explicit ContactCompletionModel(Monitor *monitor, QObject *parent = nullptr);
    ~ContactCompletionModel() override;

    Q_REQUIRED_RESULT QVariant entityData(const Item &item, int column, int role = Qt::DisplayRole) const override;
    Q_REQUIRED_RESULT QVariant entityData(const Collection &collection, int column, int role = Qt::DisplayRole) const override;
    Q_REQUIRED_RESULT int columnCount(const QModelIndex &parent) const override;
    Q_REQUIRED_RESULT int entityColumnCount(HeaderGroup) const override;

    static QAbstractItemModel *self();

private:
    static QAbstractItemModel *mSelf;
};
}

#endif
