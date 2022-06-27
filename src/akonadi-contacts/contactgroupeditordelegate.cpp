/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactgroupeditordelegate_p.h"

#include "contactcompletionmodel_p.h"
#include "contactgroupmodel_p.h"

#include <Akonadi/EntityTreeModel>
#include <KComboBox>

#include <QAbstractItemView>
#include <QCompleter>
#include <QIcon>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include <QTimer>

using namespace Akonadi;

/**
 * @short Model that filters out all contacts without email address.
 */
class ContactsWithEmailFilterModel : public QSortFilterProxyModel
{
public:
    ContactsWithEmailFilterModel(QObject *parent)
        : QSortFilterProxyModel(parent)
    {
        // contact names should be sorted correctly
        setSortLocaleAware(true);
    }

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override
    {
        const QModelIndex index = sourceModel()->index(row, Akonadi::ContactCompletionModel::EmailColumn, parent);
        if (!index.isValid()) {
            return false;
        }

        return !index.data().toString().isEmpty();
    }
};

ContactLineEdit::ContactLineEdit(bool isReference, ContactCompletionModel::Columns column, QWidget *parent)
    : QLineEdit(parent)
    , mIsReference(isReference)
{
    setFrame(false);

    auto filter = new ContactsWithEmailFilterModel(this);
    filter->setSourceModel(Akonadi::ContactCompletionModel::self());

    auto completer = new QCompleter(filter, this);
    completer->setCompletionColumn(column);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    connect(completer, qOverload<const QModelIndex &>(&QCompleter::activated), this, qOverload<const QModelIndex &>(&ContactLineEdit::completed));

    setCompleter(completer);

    connect(this, &QLineEdit::textEdited, this, &ContactLineEdit::slotTextEdited);
}

bool ContactLineEdit::isReference() const
{
    return mIsReference;
}

Akonadi::Item ContactLineEdit::completedItem() const
{
    return mItem;
}

void ContactLineEdit::completed(const QModelIndex &index)
{
    if (index.isValid()) {
        mItem = index.data(Akonadi::EntityTreeModel::ItemRole).value<Akonadi::Item>();
        mIsReference = true;
    } else {
        mItem = Item();
        mIsReference = false;
    }

    Q_EMIT completed(this);
}

void ContactLineEdit::slotTextEdited()
{
    // if the user has edited the text, we break up the reference
    mIsReference = false;
}

class Akonadi::ContactGroupEditorDelegatePrivate
{
public:
    ContactGroupEditorDelegatePrivate()
        : mButtonSize(16, 16)
        , mIcon(QIcon::fromTheme(QStringLiteral("list-remove")))
    {
    }

    QSize mButtonSize;
    const QIcon mIcon;
    QAbstractItemView *mItemView = nullptr;
};

ContactGroupEditorDelegate::ContactGroupEditorDelegate(QAbstractItemView *view, QObject *parent)
    : QStyledItemDelegate(parent)
    , d(new ContactGroupEditorDelegatePrivate)
{
    d->mItemView = view;
}

ContactGroupEditorDelegate::~ContactGroupEditorDelegate() = default;

QWidget *ContactGroupEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isReference = index.data(ContactGroupModel::IsReferenceRole).toBool();
    Q_UNUSED(option)
    if (index.column() == 0) {
        auto edit = new ContactLineEdit(isReference, ContactCompletionModel::NameAndEmailColumn, parent);
        connect(edit, qOverload<QWidget *>(&ContactLineEdit::completed), this, &ContactGroupEditorDelegate::completed);

        return edit;
    } else {
        if (index.data(ContactGroupModel::IsReferenceRole).toBool()) {
            auto comboBox = new KComboBox(parent);
            comboBox->setFrame(false);
            comboBox->setAutoFillBackground(true);
            return comboBox;
        } else {
            auto edit = new ContactLineEdit(isReference, ContactCompletionModel::NameAndEmailColumn, parent);
            connect(edit, qOverload<QWidget *>(&ContactLineEdit::completed), this, &ContactGroupEditorDelegate::completed);
            return edit;
        }
    }
}

void ContactGroupEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.data(ContactGroupModel::IsReferenceRole).toBool()) {
        if (index.column() == 0) {
            auto lineEdit = qobject_cast<QLineEdit *>(editor);
            if (!lineEdit) {
                return;
            }

            lineEdit->setText(index.data(Qt::EditRole).toString());
        } else {
            auto comboBox = qobject_cast<KComboBox *>(editor);
            if (!comboBox) {
                return;
            }

            const QStringList emails = index.data(ContactGroupModel::AllEmailsRole).toStringList();
            comboBox->clear();
            comboBox->addItems(emails);
            comboBox->setCurrentIndex(comboBox->findText(index.data(Qt::EditRole).toString()));
        }
    } else {
        auto lineEdit = qobject_cast<QLineEdit *>(editor);
        if (!lineEdit) {
            return;
        }

        lineEdit->setText(index.data(Qt::EditRole).toString());
    }
}

void ContactGroupEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.data(ContactGroupModel::IsReferenceRole).toBool()) {
        if (index.column() == 0) {
            auto lineEdit = static_cast<ContactLineEdit *>(editor);

            const bool isReference = lineEdit->isReference();
            const Item item = lineEdit->completedItem();
            model->setData(index, isReference, ContactGroupModel::IsReferenceRole);
            if (isReference) {
                if (item.isValid()) {
                    model->setData(index, item.id(), Qt::EditRole);
                }
            } else {
                model->setData(index, lineEdit->text(), Qt::EditRole);
            }
        }

        if (index.column() == 1) {
            auto comboBox = qobject_cast<KComboBox *>(editor);
            if (!comboBox) {
                return;
            }

            model->setData(index, comboBox->currentText(), Qt::EditRole);
        }
    } else {
        auto lineEdit = static_cast<ContactLineEdit *>(editor);

        const bool isReference = lineEdit->isReference();
        const Item item = lineEdit->completedItem();
        model->setData(index, isReference, ContactGroupModel::IsReferenceRole);
        if (isReference) {
            if (item.isValid()) {
                model->setData(index.sibling(index.row(), 0), item.id(), Qt::EditRole);
            }
        } else {
            model->setData(index, lineEdit->text(), Qt::EditRole);
        }
    }
}

static bool isLastRow(const QModelIndex &index)
{
    return index.row() == (index.model()->rowCount() - 1);
}

void ContactGroupEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    if (index.column() == 1 && !isLastRow(index)) {
        QRect buttonRect = d->mItemView->visualRect(index);
        buttonRect.setLeft(buttonRect.right() - d->mButtonSize.width());
        d->mIcon.paint(painter, buttonRect, Qt::AlignRight);
    }
}

QSize ContactGroupEditorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    QSize hint = QStyledItemDelegate::sizeHint(option, index);
    hint.setHeight(qMax(hint.height(), d->mButtonSize.height()));

    if (index.column() == 1) {
        hint.setWidth(hint.width() + d->mButtonSize.width());
    }

    return hint;
}

bool ContactGroupEditorDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column() == 1 && !isLastRow(index)) {
        if (event->type() == QEvent::MouseButtonRelease) {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QRect buttonRect = d->mItemView->visualRect(index);
            buttonRect.setLeft(buttonRect.right() - d->mButtonSize.width());

            if (buttonRect.contains(mouseEvent->pos())) {
                model->removeRows(index.row(), 1);
                QTimer::singleShot(0, this, &ContactGroupEditorDelegate::setFirstColumnAsCurrent);
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ContactGroupEditorDelegate::completed(QWidget *widget)
{
    Q_EMIT commitData(widget);
    Q_EMIT closeEditor(widget);
}

void ContactGroupEditorDelegate::setFirstColumnAsCurrent()
{
    d->mItemView->setCurrentIndex(d->mItemView->model()->index(d->mItemView->currentIndex().row(), 0));
}

#include "moc_contactgroupeditordelegate_p.cpp"
