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

#include "dateeditwidget.h"

#include "kdatepickerpopup_p.h"

#include <kdatepicker.h>


#include <klocalizedstring.h>

#include <QContextMenuEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <KLocale>
#include <QLocale>

DateView::DateView(QWidget *parent)
    : QLabel(parent)
{
    setTextInteractionFlags(Qt::TextSelectableByMouse);
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Sunken);
}

void DateView::contextMenuEvent(QContextMenuEvent *event)
{
    if (text().isEmpty()) {
        return;
    }

    QMenu menu;
    menu.addAction(i18n("Remove"), this, SLOT(emitSignal()));

    menu.exec(event->globalPos());
}

void DateView::emitSignal()
{
    emit resetDate();
}

DateEditWidget::DateEditWidget(Type type, QWidget *parent)
    : QWidget(parent)
    , mReadOnly(false)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

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

DateEditWidget::~DateEditWidget()
{
}

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
