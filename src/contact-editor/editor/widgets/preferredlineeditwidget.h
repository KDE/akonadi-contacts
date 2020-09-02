/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PREFERREDLINEEDITWIDGET_H
#define PREFERREDLINEEDITWIDGET_H

#include <KLineEdit>
#include <QIcon>
class QAction;
namespace ContactEditor {
class PreferredLineEditWidget : public KLineEdit
{
    Q_OBJECT
public:
    explicit PreferredLineEditWidget(QWidget *parent = nullptr);
    ~PreferredLineEditWidget();

    Q_REQUIRED_RESULT bool preferred() const;

    void setPreferred(bool preferred);

Q_SIGNALS:
    void preferredChanged(QWidget *w);

private:
    void slotPreferredStatusChanged();
    void updatePreferredIcon();
    bool mPreferred = false;
    QIcon mIconEnabled;
    QIcon mIconDisabled;
    QAction *mPreferredAction = nullptr;
};
}
#endif // PREFERREDLINEEDITWIDGET_H
