/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldsmodel.h"

#include <KLocalizedString>

#include <QDateTime>
#include <QLocale>

Q_DECLARE_METATYPE(Qt::CheckState)

CustomFieldsModel::CustomFieldsModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

CustomFieldsModel::~CustomFieldsModel() = default;

void CustomFieldsModel::setCustomFields(const CustomField::List &customFields)
{
    Q_EMIT layoutAboutToBeChanged();

    mCustomFields = customFields;

    Q_EMIT layoutChanged();
}

CustomField::List CustomFieldsModel::customFields() const
{
    return mCustomFields;
}

QModelIndex CustomFieldsModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex CustomFieldsModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return {};
}

QVariant CustomFieldsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (index.row() < 0 || index.row() >= mCustomFields.count()) {
        return {};
    }

    if (index.column() < 0 || index.column() > 2) {
        return {};
    }

    const CustomField &customField = mCustomFields[index.row()];

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return customField.title();
        } else if (index.column() == 1) {
            switch (customField.type()) {
            case CustomField::TextType:
            case CustomField::NumericType:
            case CustomField::UrlType:
                return customField.value();
            case CustomField::BooleanType:
                return QString();
            case CustomField::DateType: {
                const QDate value = QDate::fromString(customField.value(), Qt::ISODate);
                return QLocale().toString(value, QLocale::ShortFormat);
            }
            case CustomField::TimeType: {
                const QTime value = QTime::fromString(customField.value(), Qt::ISODate);
                return QLocale().toString(value);
            }
            case CustomField::DateTimeType: {
                const QDateTime value = QDateTime::fromString(customField.value(), Qt::ISODate);
                return QLocale().toString(value);
            }
            }
            return customField.value();
        } else {
            return customField.key();
        }
    }

    if (role == Qt::CheckStateRole) {
        if (index.column() == 1) {
            if (customField.type() == CustomField::BooleanType) {
                return customField.value() == QLatin1String("true") ? Qt::Checked : Qt::Unchecked;
            }
        }
    }

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
            return customField.title();
        } else if (index.column() == 1) {
            return customField.value();
        } else {
            return customField.key();
        }
    }

    if (role == TypeRole) {
        return customField.type();
    }

    if (role == ScopeRole) {
        return customField.scope();
    }

    return {};
}

bool CustomFieldsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (index.row() < 0 || index.row() >= mCustomFields.count()) {
        return false;
    }

    if (index.column() < 0 || index.column() > 2) {
        return false;
    }

    CustomField &customField = mCustomFields[index.row()];

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
            customField.setTitle(value.toString());
        } else if (index.column() == 1) {
            customField.setValue(value.toString());
        } else {
            customField.setKey(value.toString());
        }

        Q_EMIT dataChanged(index, index);
        return true;
    }

    if (role == Qt::CheckStateRole) {
        if (index.column() == 1) {
            if (customField.type() == CustomField::BooleanType) {
                customField.setValue(static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked ? QStringLiteral("true") : QStringLiteral("false"));
                Q_EMIT dataChanged(index, index);
                return true;
            }
        }
    }

    if (role == TypeRole) {
        customField.setType((CustomField::Type)value.toInt());
        Q_EMIT dataChanged(index, index);
        return true;
    }

    if (role == ScopeRole) {
        customField.setScope((CustomField::Scope)value.toInt());
        Q_EMIT dataChanged(index, index);
        return true;
    }

    return false;
}

QVariant CustomFieldsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0 || section > 1) {
        return {};
    }

    if (orientation != Qt::Horizontal) {
        return {};
    }

    if (role != Qt::DisplayRole) {
        return {};
    }

    if (section == 0) {
        return i18nc("custom field title", "Title");
    } else {
        return i18nc("custom field value", "Value");
    }
}

Qt::ItemFlags CustomFieldsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= mCustomFields.count()) {
        return QAbstractItemModel::flags(index);
    }

    const CustomField &customField = mCustomFields[index.row()];

    const Qt::ItemFlags parentFlags = QAbstractItemModel::flags(index);
    if ((customField.type() == CustomField::BooleanType) && (index.column() == 1)) {
        return parentFlags | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
    } else {
        return parentFlags | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
}

int CustomFieldsModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 3;
    } else {
        return 0;
    }
}

int CustomFieldsModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return mCustomFields.count();
    } else {
        return 0;
    }
}

bool CustomFieldsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        mCustomFields.insert(row, CustomField());
    }
    endInsertRows();

    return true;
}

bool CustomFieldsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        mCustomFields.remove(row);
    }
    endRemoveRows();

    return true;
}

#include "moc_customfieldsmodel.cpp"
