/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupmodel_p.h"

#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KContacts/Addressee>

#include <KIconUtils>
#include <KLocalizedString>
#include <QIcon>

using namespace Akonadi;

struct GroupMember {
    KContacts::ContactGroup::ContactReference reference;
    KContacts::ContactGroup::Data data;
    KContacts::Addressee referencedContact;
    bool isReference = false;
    bool loadingError = false;
};

class Akonadi::ContactGroupModelPrivate
{
public:
    ContactGroupModelPrivate(ContactGroupModel *parent)
        : mParent(parent)
    {
    }

    void resolveContactReference(const KContacts::ContactGroup::ContactReference &reference, int row)
    {
        Item item;
        if (!reference.gid().isEmpty()) {
            item.setGid(reference.gid());
        } else {
            item.setId(reference.uid().toLongLong());
        }
        auto job = new ItemFetchJob(item, mParent);
        job->setProperty("row", row);
        job->fetchScope().fetchFullPayload();

        mParent->connect(job, &ItemFetchJob::result, mParent, [this](KJob *job) {
            itemFetched(job);
        });
    }

    void itemFetched(KJob *job)
    {
        const int row = job->property("row").toInt();

        if (job->error()) {
            mMembers[row].loadingError = true;
            Q_EMIT mParent->dataChanged(mParent->index(row, 0, QModelIndex()), mParent->index(row, 1, QModelIndex()));
            return;
        }

        auto fetchJob = qobject_cast<ItemFetchJob *>(job);

        if (fetchJob->items().count() != 1) {
            mMembers[row].loadingError = true;
            Q_EMIT mParent->dataChanged(mParent->index(row, 0, QModelIndex()), mParent->index(row, 1, QModelIndex()));
            return;
        }

        const Item item = fetchJob->items().at(0);
        const auto contact = item.payload<KContacts::Addressee>();

        GroupMember &member = mMembers[row];
        member.referencedContact = contact;
        Q_EMIT mParent->dataChanged(mParent->index(row, 0, QModelIndex()), mParent->index(row, 1, QModelIndex()));
    }

    void normalizeMemberList()
    {
        // check whether a normalization is needed or not
        bool needsNormalization = false;
        if (mMembers.isEmpty()) {
            needsNormalization = true;
        } else {
            for (int i = 0; i < mMembers.count(); ++i) {
                const GroupMember &member = mMembers[i];
                if (!member.isReference && !(i == mMembers.count() - 1)) {
                    if (member.data.name().isEmpty() && member.data.email().isEmpty()) {
                        needsNormalization = true;
                        break;
                    }
                }
            }

            const GroupMember &member = mMembers.last();
            if (member.isReference || !(member.data.name().isEmpty() && member.data.email().isEmpty())) {
                needsNormalization = true;
            }
        }

        // if not, avoid to update the model and view
        if (!needsNormalization) {
            return;
        }

        bool foundEmpty = false;

        // add an empty line at the end
        mParent->beginInsertRows(QModelIndex(), mMembers.count(), mMembers.count());
        GroupMember member;
        member.isReference = false;
        mMembers.append(member);
        mParent->endInsertRows();

        // remove all empty lines first except the last line
        do {
            foundEmpty = false;
            for (int i = 0, total = mMembers.count(); i < total; ++i) {
                const GroupMember &member = mMembers[i];
                if (!member.isReference && !(i == mMembers.count() - 1)) {
                    if (member.data.name().isEmpty() && member.data.email().isEmpty()) {
                        mParent->beginRemoveRows(QModelIndex(), i, i);
                        mMembers.remove(i);
                        mParent->endRemoveRows();
                        foundEmpty = true;
                        break;
                    }
                }
            }
        } while (foundEmpty);
    }

    ContactGroupModel *const mParent;
    QList<GroupMember> mMembers;
    KContacts::ContactGroup mGroup;
    QString mLastErrorMessage;
};

ContactGroupModel::ContactGroupModel(QObject *parent)
    : QAbstractItemModel(parent)
    , d(new ContactGroupModelPrivate(this))
{
}

ContactGroupModel::~ContactGroupModel() = default;

void ContactGroupModel::loadContactGroup(const KContacts::ContactGroup &contactGroup)
{
    Q_EMIT layoutAboutToBeChanged();

    d->mMembers.clear();
    d->mGroup = contactGroup;

    for (int i = 0; i < d->mGroup.dataCount(); ++i) {
        const KContacts::ContactGroup::Data data = d->mGroup.data(i);
        GroupMember member;
        member.isReference = false;
        member.data = data;

        d->mMembers.append(member);
    }

    for (int i = 0; i < d->mGroup.contactReferenceCount(); ++i) {
        const KContacts::ContactGroup::ContactReference reference = d->mGroup.contactReference(i);
        GroupMember member;
        member.isReference = true;
        member.reference = reference;

        d->mMembers.append(member);

        d->resolveContactReference(reference, d->mMembers.count() - 1);
    }

    d->normalizeMemberList();

    Q_EMIT layoutChanged();
}

bool ContactGroupModel::storeContactGroup(KContacts::ContactGroup &group) const
{
    group.removeAllContactReferences();
    group.removeAllContactData();

    for (int i = 0; i < d->mMembers.count(); ++i) {
        const GroupMember &member = d->mMembers[i];
        if (member.isReference) {
            group.append(member.reference);
        } else {
            if (i != (d->mMembers.count() - 1)) {
                if (member.data.email().isEmpty()) {
                    d->mLastErrorMessage = i18n("The member with name <b>%1</b> is missing an email address", member.data.name());
                    return false;
                }
                group.append(member.data);
            }
        }
    }

    return true;
}

QString ContactGroupModel::lastErrorMessage() const
{
    return d->mLastErrorMessage;
}

QModelIndex ContactGroupModel::index(int row, int col, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return createIndex(row, col);
}

QModelIndex ContactGroupModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return {};
}

QVariant ContactGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (index.row() < 0 || index.row() >= d->mMembers.count()) {
        return {};
    }

    if (index.column() < 0 || index.column() > 1) {
        return {};
    }

    const GroupMember &member = d->mMembers[index.row()];

    if (role == Qt::DisplayRole) {
        if (member.loadingError) {
            if (index.column() == 0) {
                return i18n("Contact does not exist any more");
            } else {
                return QString();
            }
        }

        if (member.isReference) {
            if (index.column() == 0) {
                return member.referencedContact.realName();
            } else {
                if (!member.reference.preferredEmail().isEmpty()) {
                    return member.reference.preferredEmail();
                } else {
                    return member.referencedContact.preferredEmail();
                }
            }
        } else {
            if (index.column() == 0) {
                return member.data.name();
            } else {
                return member.data.email();
            }
        }
    }

    if (role == Qt::DecorationRole) {
        if (index.column() == 1) {
            return {};
        }

        if (member.loadingError) {
            return QIcon::fromTheme(QStringLiteral("emblem-important"));
        }

        if (index.row() == (d->mMembers.count() - 1)) {
            return QIcon::fromTheme(QStringLiteral("contact-new"));
        }

        if (member.isReference) {
            return KIconUtils::addOverlays(QStringLiteral("x-office-contact"), {QStringLiteral("emblem-symbolic-link")});
        } else {
            return QIcon::fromTheme(QStringLiteral("x-office-contact"));
        }
    }

    if (role == Qt::EditRole) {
        if (member.isReference) {
            if (index.column() == 0) {
                return member.referencedContact.realName();
            } else {
                if (!member.reference.preferredEmail().isEmpty()) {
                    return member.reference.preferredEmail();
                } else {
                    return member.referencedContact.preferredEmail();
                }
            }
        } else {
            if (index.column() == 0) {
                return member.data.name();
            } else {
                return member.data.email();
            }
        }
    }

    if (role == IsReferenceRole) {
        return member.isReference;
    }

    if (role == AllEmailsRole) {
        if (member.isReference) {
            return member.referencedContact.emails();
        } else {
            return QStringList();
        }
    }

    return {};
}

bool ContactGroupModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (index.row() < 0 || index.row() >= d->mMembers.count()) {
        return false;
    }

    if (index.column() < 0 || index.column() > 1) {
        return false;
    }

    GroupMember &member = d->mMembers[index.row()];

    if (role == Qt::EditRole) {
        if (member.isReference) {
            if (index.column() == 0) {
                member.reference.setUid(QString::number(value.toLongLong()));
                d->resolveContactReference(member.reference, index.row());
            }
            if (index.column() == 1) {
                const QString email = value.toString();
                if (email != member.referencedContact.preferredEmail()) {
                    member.reference.setPreferredEmail(email);
                } else {
                    member.reference.setPreferredEmail(QString());
                }
            }
        } else {
            if (index.column() == 0) {
                member.data.setName(value.toString());
            } else {
                member.data.setEmail(value.toString());
            }
        }

        d->normalizeMemberList();

        return true;
    }

    if (role == IsReferenceRole) {
        if ((value.toBool() == true) && !member.isReference) {
            member.isReference = true;
        }
        if ((value.toBool() == false) && member.isReference) {
            member.isReference = false;
            member.data.setName(member.referencedContact.realName());
            member.data.setEmail(member.referencedContact.preferredEmail());
        }

        return true;
    }

    return false;
}

QVariant ContactGroupModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        return i18nc("contact's name", "Name");
    } else {
        return i18nc("contact's email address", "EMail");
    }
}

Qt::ItemFlags ContactGroupModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= d->mMembers.count()) {
        return Qt::ItemIsEnabled;
    }

    if (d->mMembers[index.row()].loadingError) {
        return {Qt::ItemIsEnabled};
    }

    Qt::ItemFlags parentFlags = QAbstractItemModel::flags(index);
    return parentFlags | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

int ContactGroupModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 2;
    } else {
        return 0;
    }
}

int ContactGroupModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return d->mMembers.count();
    } else {
        return 0;
    }
}

bool ContactGroupModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        d->mMembers.remove(row);
    }
    endRemoveRows();

    return true;
}

GroupFilterModel::GroupFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterKeyColumn(-1);
}

bool GroupFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (sourceRow == sourceModel()->rowCount() - 1) {
        return true;
    }

    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

bool GroupFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (left.row() == sourceModel()->rowCount() - 1) {
        return true;
    }

    if (right.row() == sourceModel()->rowCount() - 1) {
        return false;
    }

    return QSortFilterProxyModel::lessThan(left, right);
}

#include "moc_contactgroupmodel_p.cpp"
