/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KLineEdit>
#include <QIcon>
class QAction;
namespace Akonadi
{
class PreferredLineEditWidget : public KLineEdit
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
    QIcon mIconEnabled;
    QIcon mIconDisabled;
    QAction *mPreferredAction = nullptr;
};
}
