/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#ifndef AKONADI_CONTACTGROUPMODEL_P_H
#define AKONADI_CONTACTGROUPMODEL_P_H

#include <QAbstractItemModel>

#include <kcontacts/contactgroup.h>

namespace Akonadi {
class ContactGroupModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Role {
        IsReferenceRole = Qt::UserRole,
        AllEmailsRole
    };

    explicit ContactGroupModel(QObject *parent = nullptr);
    ~ContactGroupModel();

    void loadContactGroup(const KContacts::ContactGroup &contactGroup);
    bool storeContactGroup(KContacts::ContactGroup &contactGroup) const;

    QString lastErrorMessage() const;

    QModelIndex index(int row, int col, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    class Private;
    Private *const d;
};
}

#endif
