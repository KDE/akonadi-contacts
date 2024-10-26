/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QDate>
#include <QLineEdit>
#include <QWidget>

class KDatePickerPopup;

class QContextMenuEvent;
class QToolButton;

class DateView : public QLineEdit
{
    Q_OBJECT

public:
    explicit DateView(QWidget *parent = nullptr);

Q_SIGNALS:
    void resetDate();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void emitSignal();
};

class DateEditWidget : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        General,
        Birthday,
        Anniversary
    };

    explicit DateEditWidget(Type type = General, QWidget *parent = nullptr);
    ~DateEditWidget() override;

    void setDate(const QDate &date);
    [[nodiscard]] QDate date() const;

    void setReadOnly(bool readOnly);

private:
    void dateSelected(const QDate &date);
    void resetDate();
    void updateView();
    DateView *mView = nullptr;
    QToolButton *mSelectButton = nullptr;
    QToolButton *mClearButton = nullptr;
    KDatePickerPopup *mMenu = nullptr;
    QDate mDate;
    bool mReadOnly = false;
};
