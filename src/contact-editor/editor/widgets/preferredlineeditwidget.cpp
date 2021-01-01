/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "preferredlineeditwidget.h"
#include <KLocalizedString>
#include <QAction>

using namespace ContactEditor;

PreferredLineEditWidget::PreferredLineEditWidget(QWidget *parent)
    : KLineEdit(parent)
{
    mIconEnabled = QIcon::fromTheme(QStringLiteral("rating"));
    mIconDisabled = QIcon::fromTheme(QStringLiteral("rating-unrated"));
    mPreferredAction = addAction(mIconDisabled, QLineEdit::TrailingPosition);
    mPreferredAction->setObjectName(QStringLiteral("preferredaction"));
    mPreferredAction->setToolTip(i18n("Set as Preferred"));
    connect(mPreferredAction, &QAction::triggered, this, &PreferredLineEditWidget::slotPreferredStatusChanged);
}

PreferredLineEditWidget::~PreferredLineEditWidget()
{
}

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
