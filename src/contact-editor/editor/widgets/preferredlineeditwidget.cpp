/*
    This file is part of Contact Editor.

    Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "preferredlineeditwidget.h"
#include <KLocalizedString>
#include <QAction>

using namespace ContactEditor;

PreferredLineEditWidget::PreferredLineEditWidget(QWidget *parent)
    : KLineEdit(parent)
    , mPreferred(false)
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
