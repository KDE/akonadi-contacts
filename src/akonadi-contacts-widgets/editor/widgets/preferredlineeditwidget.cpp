/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "preferredlineeditwidget.h"
#include <KLocalizedString>
#include <QAction>

using namespace Akonadi;

PreferredLineEditWidget::PreferredLineEditWidget(QWidget *parent)
    : KLineEdit(parent)
{
    mIconEnabled = QIcon::fromTheme(QStringLiteral("rating"));
    mIconDisabled = QIcon::fromTheme(QStringLiteral("rating-unrated"));
    mPreferredAction = addAction(mIconDisabled, QLineEdit::TrailingPosition);
    mPreferredAction->setObjectName(QLatin1StringView("preferredaction"));
    mPreferredAction->setToolTip(i18nc("@info:tooltip", "Set as Preferred"));
    connect(mPreferredAction, &QAction::triggered, this, &PreferredLineEditWidget::slotPreferredStatusChanged);
}

PreferredLineEditWidget::~PreferredLineEditWidget() = default;

void PreferredLineEditWidget::slotPreferredStatusChanged()
{
    if (isReadOnly()) {
        return;
    }
    mPreferred = !mPreferred;
    updatePreferredIcon();
    Q_EMIT preferredChanged(this);
}

void PreferredLineEditWidget::updatePreferredIcon()
{
    mPreferredAction->setIcon(mPreferred ? mIconEnabled : mIconDisabled);
}

void PreferredLineEditWidget::setPreferred(bool preferred)
{
    if (mPreferred != preferred) {
        mPreferred = preferred;
        updatePreferredIcon();
    }
}

bool PreferredLineEditWidget::preferred() const
{
    return mPreferred;
}

#include "moc_preferredlineeditwidget.cpp"
