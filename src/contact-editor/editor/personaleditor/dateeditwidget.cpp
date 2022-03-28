/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dateeditwidget.h"

#include <KDatePicker>
#include <KDatePickerPopup>

#include <KLocalizedString>
#include <QContextMenuEvent>
#include <QHBoxLayout>
#include <QLocale>
#include <QToolButton>

DateView::DateView(QWidget *parent)
    : QLineEdit(parent)
{
    setPlaceholderText(i18n("Click to add date"));
    setReadOnly(true);
}

void DateView::contextMenuEvent(QContextMenuEvent *event)
{
    if (text().isEmpty()) {
        return;
    }

    QMenu menu;
    menu.addAction(i18n("Remove"), this, &DateView::emitSignal);

    menu.exec(event->globalPos());
}

void DateView::emitSignal()
{
    Q_EMIT resetDate();
}

DateEditWidget::DateEditWidget(Type type, QWidget *parent)
    : QWidget(parent)
    , mReadOnly(false)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});

    mView = new DateView;
    layout->addWidget(mView);

    mClearButton = new QToolButton;
    if (layoutDirection() == Qt::LeftToRight) {
        mClearButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-clear-locationbar-rtl")));
    } else {
        mClearButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-clear-locationbar-ltr")));
    }
    layout->addWidget(mClearButton);

    mSelectButton = new QToolButton;
    mSelectButton->setPopupMode(QToolButton::InstantPopup);
    switch (type) {
    case General:
        mSelectButton->setIcon(QIcon::fromTheme(QStringLiteral("view-calendar-day")));
        break;
    case Birthday:
        mSelectButton->setIcon(QIcon::fromTheme(QStringLiteral("view-calendar-birthday")));
        break;
    case Anniversary:
        mSelectButton->setIcon(QIcon::fromTheme(QStringLiteral("view-calendar-wedding-anniversary")));
        break;
    }

    layout->addWidget(mSelectButton);
    setFocusProxy(mSelectButton);
    setFocusPolicy(Qt::StrongFocus);

    mMenu = new KDatePickerPopup(KDatePickerPopup::DatePicker, QDate(), this);
    mSelectButton->setMenu(mMenu);

    connect(mClearButton, &QToolButton::clicked, this, &DateEditWidget::resetDate);
    connect(mMenu, &KDatePickerPopup::dateChanged, this, &DateEditWidget::dateSelected);
    connect(mView, &DateView::resetDate, this, &DateEditWidget::resetDate);

    updateView();
}

DateEditWidget::~DateEditWidget() = default;

void DateEditWidget::setDate(const QDate &date)
{
    mDate = date;
    mMenu->setDate(mDate);
    updateView();
}

QDate DateEditWidget::date() const
{
    return mDate;
}

void DateEditWidget::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;

    mSelectButton->setEnabled(!readOnly);
    mClearButton->setEnabled(!readOnly);
}

void DateEditWidget::dateSelected(const QDate &date)
{
    mDate = date;
    updateView();
}

void DateEditWidget::resetDate()
{
    mDate = QDate();
    updateView();
}

void DateEditWidget::updateView()
{
    if (mDate.isValid()) {
        mView->setText(QLocale().toString(mDate));
        mClearButton->show();
    } else {
        mView->setText(QString());
        mClearButton->hide();
    }
}
