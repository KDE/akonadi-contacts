/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Stephen Kelly <steveire@gmail.com>
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactstreemodel.h"

#include <KContacts/Addressee>
#include <KContacts/ContactGroup>

#include <KIconLoader>
#include <KLocalizedString>

#include <QIcon>
#include <QLocale>

using namespace Akonadi;

class Akonadi::ContactsTreeModelPrivate
{
public:
    ContactsTreeModelPrivate()
        : mColumns(ContactsTreeModel::Columns() << ContactsTreeModel::FullName)
        , mIconSize(KIconLoader::global()->currentSize(KIconLoader::Small))
    {
    }

    ContactsTreeModel::Columns mColumns;
    const int mIconSize;
};

ContactsTreeModel::ContactsTreeModel(Monitor *monitor, QObject *parent)
    : EntityTreeModel(monitor, parent)
    , d(new ContactsTreeModelPrivate)
{
}

ContactsTreeModel::~ContactsTreeModel() = default;

QHash<int, QByteArray> ContactsTreeModel::roleNames() const
{
    auto roles = EntityTreeModel::roleNames();
    roles[AddresseeRole] = "addressee";
    return roles;
}

void ContactsTreeModel::setColumns(const Columns &columns)
{
    beginResetModel();
    d->mColumns = columns;
    endResetModel();
}

ContactsTreeModel::Columns ContactsTreeModel::columns() const
{
    return d->mColumns;
}

QVariant ContactsTreeModel::entityData(const Item &item, int column, int role) const
{
    if (item.mimeType() == KContacts::Addressee::mimeType()) {
        if (!item.hasPayload<KContacts::Addressee>()) {
            // Pass modeltest
            if (role == Qt::DisplayRole) {
                return item.remoteId();
            }

            return {};
        }

        const auto contact = item.payload<KContacts::Addressee>();

        if (role == AddresseeRole) {
            return QVariant::fromValue(contact);
        } else if (role == Qt::DecorationRole) {
            if (column == 0) {
                const KContacts::Picture picture = contact.photo();
                if (picture.isIntern()) {
                    return picture.data().scaled(QSize(d->mIconSize, d->mIconSize), Qt::KeepAspectRatio);
                } else {
                    return QIcon::fromTheme(QStringLiteral("user-identity"));
                }
            }
            return {};
        } else if ((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            switch (d->mColumns.at(column)) {
            case FullName:
                if (contact.realName().isEmpty()) {
                    if (contact.preferredEmail().isEmpty()) {
                        return contact.familyName();
                    }
                    return contact.preferredEmail();
                }
                return contact.realName();
            case FamilyName:
                return contact.familyName();
            case GivenName:
                return contact.givenName();
            case Birthday:
                if (contact.birthday().date().isValid()) {
                    return QLocale().toString(contact.birthday().date(), QLocale::ShortFormat);
                }
                break;
            case HomeAddress: {
                const KContacts::Address address = contact.address(KContacts::Address::Home);
                if (!address.isEmpty()) {
                    return address.formatted(KContacts::AddressFormatStyle::Postal);
                }
                break;
            }
            case BusinessAddress: {
                const KContacts::Address address = contact.address(KContacts::Address::Work);
                if (!address.isEmpty()) {
                    return address.formatted(KContacts::AddressFormatStyle::Postal);
                }
                break;
            }
            case PhoneNumbers: {
                QStringList values;

                const KContacts::PhoneNumber::List numbers = contact.phoneNumbers();
                values.reserve(numbers.count());
                for (const KContacts::PhoneNumber &number : numbers) {
                    values += number.number();
                }

                return values.join(QLatin1Char('\n'));
                break;
            }
            case PreferredEmail:
                return contact.preferredEmail();
            case AllEmails:
                return contact.emails().join(QLatin1Char('\n'));
            case Organization:
                return contact.organization();
            case Role:
                return contact.role();
            case Homepage:
                return contact.url().url();
            case Note:
                return contact.note();
            }
        } else if (role == DateRole) {
            if (d->mColumns.at(column) == Birthday) {
                return contact.birthday();
            } else {
                return QDate();
            }
        }
    } else if (item.mimeType() == KContacts::ContactGroup::mimeType()) {
        if (role == AddresseeRole) {
            // expose empty addressee so that required properties in QML are not broken
            return QVariant::fromValue(KContacts::Addressee());
        }

        if (!item.hasPayload<KContacts::ContactGroup>()) {
            // Pass modeltest
            if (role == Qt::DisplayRole) {
                return item.remoteId();
            }

            return {};
        }

        if (role == Qt::DecorationRole) {
            if (column == 0) {
                return QIcon::fromTheme(QStringLiteral("x-mail-distribution-list"));
            } else {
                return {};
            }
        } else if ((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            switch (d->mColumns.at(column)) {
            case FullName: {
                const auto group = item.payload<KContacts::ContactGroup>();
                return group.name();
            }
            default:
                return {};
            }
        }
    }

    return EntityTreeModel::entityData(item, column, role);
}

QVariant ContactsTreeModel::entityData(const Collection &collection, int column, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (column) {
        case 0:
            return EntityTreeModel::entityData(collection, column, role);
        default:
            return QString(); // pass model test
        }
    }

    return EntityTreeModel::entityData(collection, column, role);
}

int ContactsTreeModel::entityColumnCount(HeaderGroup headerGroup) const
{
    if (headerGroup == EntityTreeModel::CollectionTreeHeaders) {
        return 1;
    } else if (headerGroup == EntityTreeModel::ItemListHeaders) {
        return d->mColumns.count();
    } else {
        return EntityTreeModel::entityColumnCount(headerGroup);
    }
}

QVariant ContactsTreeModel::entityHeaderData(int section, Qt::Orientation orientation, int role, HeaderGroup headerGroup) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (headerGroup == EntityTreeModel::CollectionTreeHeaders) {
                if (section >= 1) {
                    return {};
                }

                switch (section) {
                case 0:
                    return i18nc("@title:column address books overview", "Address Books");
                    break;
                }
            } else if (headerGroup == EntityTreeModel::ItemListHeaders) {
                if (section < 0 || section >= d->mColumns.count()) {
                    return {};
                }

                switch (d->mColumns.at(section)) {
                case FullName:
                    return i18nc("@title:column name of a person", "Name");
                case FamilyName:
                    return i18nc("@title:column family name of a person", "Family Name");
                case GivenName:
                    return i18nc("@title:column given name of a person", "Given Name");
                case Birthday:
                    return KContacts::Addressee::birthdayLabel();
                case HomeAddress:
                    return i18nc("@title:column home address of a person", "Home");
                case BusinessAddress:
                    return i18nc("@title:column work address of a person", "Work");
                case PhoneNumbers:
                    return i18nc("@title:column phone numbers of a person", "Phone Numbers");
                case PreferredEmail:
                    return i18nc("@title:column the preferred email addresses of a person", "Preferred EMail");
                case AllEmails:
                    return i18nc("@title:column all email addresses of a person", "All EMails");
                case Organization:
                    return KContacts::Addressee::organizationLabel();
                case Role:
                    return KContacts::Addressee::roleLabel();
                case Homepage:
                    return KContacts::Addressee::urlLabel();
                case Note:
                    return KContacts::Addressee::noteLabel();
                }
            }
        }
    }

    return EntityTreeModel::entityHeaderData(section, orientation, role, headerGroup);
}

#include "moc_contactstreemodel.cpp"
