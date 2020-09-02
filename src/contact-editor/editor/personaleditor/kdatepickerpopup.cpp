/*
    This file is part of Contact Editor.

  SPDX-FileCopyrightText: 2004 Bram Schoenmakers <bramschoenmakers@kde.nl>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdatepickerpopup_p.h"

#include <KDatePicker>
#include <KLocalizedString>

#include <QDateTime>
#include <QWidgetAction>

class KDatePickerAction : public QWidgetAction
{
    Q_OBJECT
public:
    KDatePickerAction(KDatePicker *widget, QObject *parent)
        : QWidgetAction(parent)
        , mDatePicker(widget)
        , mOriginalParent(widget->parentWidget())
    {
    }

protected:
    QWidget *createWidget(QWidget *parent) override
    {
        mDatePicker->setParent(parent);
        return mDatePicker;
    }

    void deleteWidget(QWidget *widget) override
    {
        if (widget != mDatePicker) {
            return;
        }

        mDatePicker->setParent(mOriginalParent);
    }

private:
    KDatePicker *const mDatePicker;
    QWidget *const mOriginalParent;
};

KDatePickerPopup::KDatePickerPopup(Items items, const QDate &date, QWidget *parent)
    : QMenu(parent)
{
    mItems = items;
    mDate = date;
    mDatePicker = new KDatePicker(this);
    mDatePicker->setCloseButton(false);

    connect(mDatePicker, &KDatePicker::dateEntered, this, &KDatePickerPopup::slotDateChanged);
    connect(mDatePicker, &KDatePicker::dateSelected, this, &KDatePickerPopup::slotDateChanged);

    mDatePicker->setDate(date);

    buildMenu();
}

void KDatePickerPopup::buildMenu()
{
    if (isVisible()) {
        return;
    }
    clear();

    if (mItems & DatePicker) {
        addAction(new KDatePickerAction(mDatePicker, this));

        if ((mItems & NoDate) || (mItems & Words)) {
            addSeparator();
        }
    }

    if (mItems & Words) {
        addAction(i18nc("@option today", "&Today"), this, [this]() {
            slotToday();
        });
        addAction(i18nc("@option tomorrow", "To&morrow"), this, [this]() {
            slotTomorrow();
        });
        addAction(i18nc("@option next week", "Next &Week"), this, [this]() {
            slotNextWeek();
        });
        addAction(i18nc("@option next month", "Next M&onth"), this, [this]() {
            slotNextMonth();
        });

        if (mItems & NoDate) {
            addSeparator();
        }
    }

    if (mItems & NoDate) {
        addAction(i18nc("@option do not specify a date", "No Date"), this, [this]() {
            slotNoDate();
        });
    }
}

KDatePicker *KDatePickerPopup::datePicker() const
{
    return mDatePicker;
}

void KDatePickerPopup::setDate(const QDate &date)
{
    mDatePicker->setDate(date);
}

void KDatePickerPopup::slotDateChanged(const QDate &date)
{
    if (date != mDate) {
        Q_EMIT dateChanged(date);
    }
    hide();
}

void KDatePickerPopup::slotToday()
{
    Q_EMIT dateChanged(QDate::currentDate());
}

void KDatePickerPopup::slotTomorrow()
{
    Q_EMIT dateChanged(QDate::currentDate().addDays(1));
}

void KDatePickerPopup::slotNoDate()
{
    Q_EMIT dateChanged(QDate());
}

void KDatePickerPopup::slotNextWeek()
{
    Q_EMIT dateChanged(QDate::currentDate().addDays(7));
}

void KDatePickerPopup::slotNextMonth()
{
    Q_EMIT dateChanged(QDate::currentDate().addMonths(1));
}

#include "kdatepickerpopup.moc"
#include "moc_kdatepickerpopup_p.cpp"
