/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customfieldslistdelegate.h"

#include "customfieldsmodel.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QAbstractItemView>
#include <QCheckBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QMouseEvent>
#include <QSpinBox>
#include <QTimeEdit>
#include <QTimer>

using namespace Akonadi;
CustomFieldsListDelegate::CustomFieldsListDelegate(QAbstractItemView *view, QObject *parent)
    : QStyledItemDelegate(parent)
    , mIcon(QIcon::fromTheme(QStringLiteral("list-remove")))
    , mButtonSize(16, 16)
    , mItemView(view)
{
}

CustomFieldsListDelegate::~CustomFieldsListDelegate() = default;

QWidget *CustomFieldsListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &item, const QModelIndex &index) const
{
    if (index.column() == 1) {
        const CustomField::Type type = static_cast<CustomField::Type>(index.data(CustomFieldsModel::TypeRole).toInt());

        switch (type) {
        case CustomField::TextType:
        case CustomField::UrlType:
        default:
            return QStyledItemDelegate::createEditor(parent, item, index);
        case CustomField::NumericType: {
            auto editor = new QSpinBox(parent);
            editor->setFrame(false);
            editor->setAutoFillBackground(true);
            return editor;
        }
        case CustomField::BooleanType: {
            auto editor = new QCheckBox(parent);
            return editor;
        }
        case CustomField::DateType: {
            auto editor = new QDateEdit(parent);
            editor->setFrame(false);
            editor->setAutoFillBackground(true);
            return editor;
        }
        case CustomField::TimeType: {
            auto editor = new QTimeEdit(parent);
            editor->setFrame(false);
            editor->setAutoFillBackground(true);
            return editor;
        }
        case CustomField::DateTimeType: {
            auto editor = new QDateTimeEdit(parent);
            editor->setFrame(false);
            editor->setAutoFillBackground(true);
            return editor;
        }
        }
    } else {
        return QStyledItemDelegate::createEditor(parent, item, index);
    }
}

void CustomFieldsListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 1) {
        const CustomField::Type type = static_cast<CustomField::Type>(index.data(CustomFieldsModel::TypeRole).toInt());

        switch (type) {
        case CustomField::TextType:
        case CustomField::UrlType:
            QStyledItemDelegate::setEditorData(editor, index);
            break;
        case CustomField::NumericType: {
            auto widget = qobject_cast<QSpinBox *>(editor);
            widget->setValue(index.data(Qt::EditRole).toInt());
            break;
        }
        case CustomField::BooleanType: {
            auto widget = qobject_cast<QCheckBox *>(editor);
            widget->setChecked(index.data(Qt::EditRole).toString() == QLatin1StringView("true"));
            break;
        }
        case CustomField::DateType: {
            auto widget = qobject_cast<QDateEdit *>(editor);
            widget->setDisplayFormat(QStringLiteral("dd.MM.yyyy"));
            widget->setDate(QDate::fromString(index.data(Qt::EditRole).toString(), Qt::ISODate));
            break;
        }
        case CustomField::TimeType: {
            auto widget = qobject_cast<QTimeEdit *>(editor);
            widget->setDisplayFormat(QStringLiteral("hh:mm"));
            widget->setTime(QTime::fromString(index.data(Qt::EditRole).toString(), Qt::ISODate));
            break;
        }
        case CustomField::DateTimeType: {
            auto widget = qobject_cast<QDateTimeEdit *>(editor);
            widget->setDisplayFormat(QStringLiteral("dd.MM.yyyy hh:mm"));
            widget->setDateTime(QDateTime::fromString(index.data(Qt::EditRole).toString(), Qt::ISODate));
            break;
        }
        }
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void CustomFieldsListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == 1) {
        const CustomField::Type type = static_cast<CustomField::Type>(index.data(CustomFieldsModel::TypeRole).toInt());

        switch (type) {
        case CustomField::TextType:
        case CustomField::UrlType:
            QStyledItemDelegate::setModelData(editor, model, index);
            break;
        case CustomField::NumericType: {
            auto widget = qobject_cast<QSpinBox *>(editor);
            model->setData(index, QString::number(widget->value()));
            break;
        }
        case CustomField::BooleanType: {
            auto widget = qobject_cast<QCheckBox *>(editor);
            model->setData(index, widget->isChecked() ? QStringLiteral("true") : QStringLiteral("false"));
            break;
        }
        case CustomField::DateType: {
            auto widget = qobject_cast<QDateEdit *>(editor);
            model->setData(index, widget->date().toString(Qt::ISODate));
            break;
        }
        case CustomField::TimeType: {
            auto widget = qobject_cast<QTimeEdit *>(editor);
            model->setData(index, widget->time().toString(Qt::ISODate));
            break;
        }
        case CustomField::DateTimeType: {
            auto widget = qobject_cast<QDateTimeEdit *>(editor);
            model->setData(index, widget->dateTime().toString(Qt::ISODate));
            break;
        }
        }
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void CustomFieldsListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO: somehow mark local/global/external fields
    QStyledItemDelegate::paint(painter, option, index);
    if (index.column() == 1) {
        mIcon.paint(painter, option.rect, Qt::AlignRight);
    }
}

QSize CustomFieldsListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    QSize hint = QStyledItemDelegate::sizeHint(option, index);
    hint.setHeight(qMax(hint.height(), mButtonSize.height()));

    if (index.column() == 1) {
        hint.setWidth(hint.width() + mButtonSize.width());
    }

    return hint;
}

bool CustomFieldsListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column() == 1) {
        if (event->type() == QEvent::MouseButtonRelease) {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QRect buttonRect = mItemView->visualRect(index);
            buttonRect.setLeft(buttonRect.right() - mButtonSize.width());

            if (buttonRect.contains(mouseEvent->pos())) {
                removeField(index.row(), model);
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void CustomFieldsListDelegate::setFirstColumnAsCurrent()
{
    mItemView->setCurrentIndex(mItemView->model()->index(mItemView->currentIndex().row(), 0));
}

void CustomFieldsListDelegate::removeField(int row, QAbstractItemModel *model)
{
    if (KMessageBox::warningContinueCancel(mItemView,
                                           i18nc("Custom Fields", "Do you really want to delete the selected custom field?"),
                                           i18nc("@title:window", "Confirm Delete"),
                                           KStandardGuiItem::del())
        != KMessageBox::Continue) {
        return;
    }

    model->removeRow(row);
    QTimer::singleShot(0, this, &CustomFieldsListDelegate::setFirstColumnAsCurrent);
}

#include "moc_customfieldslistdelegate.cpp"
