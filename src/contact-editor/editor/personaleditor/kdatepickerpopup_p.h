/*
    This file is part of Contact Editor.

  SPDX-FileCopyrightText: 2004 Bram Schoenmakers <bramschoenmakers@kde.nl>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDATEPICKERPOPUP_P_H
#define KDATEPICKERPOPUP_P_H

#include <QDateTime>
#include <QMenu>

class KDatePicker;

/**
   @short This menu helps the user to select a date quickly.

   This menu helps the user to select a date quicly. It offers various
   ways of selecting, e.g. with a KDatePicker or with words like "Tomorrow".

   The available items are:

   @li NoDate: A menu-item with "No Date". If chosen, the datepicker will emit
       a null QDate.
   @li DatePicker: Show a KDatePicker-widget.
   @li Words: Show items like "Today", "Tomorrow" or "Next Week".

   When supplying multiple items, separate each item with a bitwise OR.

   @author Bram Schoenmakers <bram_s@softhome.net>
*/
class KDatePickerPopup : public QMenu
{
    Q_OBJECT

public:
    enum ItemFlag { NoDate = 1, DatePicker = 2, Words = 4 };

    Q_DECLARE_FLAGS(Items, ItemFlag)

    /**
       A constructor for the KDatePickerPopup.

       @param items List of all desirable items, separated with a bitwise OR.
       @param date Initial date of datepicker-widget.
       @param parent The object's parent.
    */
    explicit KDatePickerPopup(Items items = DatePicker, const QDate &date = QDate::currentDate(), QWidget *parent = nullptr);

    /**
       @return A pointer to the private variable mDatePicker, an instance of
       KDatePicker.
    */
    KDatePicker *datePicker() const;

    void setDate(const QDate &date);

    /** @return Returns the bitwise result of the active items in the popup. */
    int items() const
    {
        return mItems;
    }

Q_SIGNALS:

    /**
      This signal emits the new date (selected with datepicker or other
      menu-items).
      @param date changed date
    */
    void dateChanged(const QDate &date);

protected Q_SLOTS:
    void slotDateChanged(const QDate &date);

    void slotToday();
    void slotTomorrow();
    void slotNextWeek();
    void slotNextMonth();
    void slotNoDate();

private:
    void buildMenu();

    KDatePicker *mDatePicker = nullptr;
    Items mItems;
    QDate mDate;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KDatePickerPopup::Items)

#endif
