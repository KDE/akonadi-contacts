/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QIcon>
#include <QLineEdit>
class QAction;
namespace Akonadi
{
class PreferredLineEditWidget : public QLineEdit
{
    Q_OBJECT
public:
    explicit PreferredLineEditWidget(QWidget *parent = nullptr);
    ~PreferredLineEditWidget() override;

    [[nodiscard]] bool preferred() const;

    void setPreferred(bool preferred);

Q_SIGNALS:
    void preferredChanged(QWidget *w);

private:
    void slotPreferredStatusChanged();
    void updatePreferredIcon();
    bool mPreferred = false;
    const QIcon mIconEnabled;
    const QIcon mIconDisabled;
    QAction *mPreferredAction = nullptr;
};
}
