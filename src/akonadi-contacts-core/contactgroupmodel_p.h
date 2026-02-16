/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadi-contact-core_export.h"
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include <KContacts/ContactGroup>

#include <memory>

namespace Akonadi
{
class ContactGroupModelPrivate;

class AKONADI_CONTACT_CORE_EXPORT ContactGroupModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Role {
        IsReferenceRole = Qt::UserRole,
        AllEmailsRole
    };

    /*!
     * Creates a new contact group model.
     *
     * \a parent The parent object.
     */
    explicit ContactGroupModel(QObject *parent = nullptr);

    /*!
     * Destroys the contact group model.
     */
    ~ContactGroupModel() override;

    /*!
     * Loads a contact \a group into the model.
     *
     * \a contactGroup The contact group to load.
     */
    void loadContactGroup(const KContacts::ContactGroup &contactGroup);

    /*!
     * Stores the model's contents back to a contact \a group.
     *
     * \a contactGroup The contact group to store the data to.
     * \returns True if successful, false otherwise.
     */
    bool storeContactGroup(KContacts::ContactGroup &contactGroup) const;

    /*!
     * Returns the last error message, if any operation failed.
     *
     * \returns A description of the last error.
     */
    [[nodiscard]] QString lastErrorMessage() const;

    [[nodiscard]] QModelIndex index(int row, int col, const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    friend class ContactGroupModelPrivate;
    std::unique_ptr<ContactGroupModelPrivate> const d;
};

class AKONADI_CONTACT_CORE_EXPORT GroupFilterModel : public QSortFilterProxyModel
{
public:
    /*!
     * Creates a new group filter model.
     *
     * \a parent The parent object.
     */
    explicit GroupFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

}
