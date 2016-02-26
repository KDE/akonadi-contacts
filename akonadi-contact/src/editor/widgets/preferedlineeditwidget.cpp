/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

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

#include "preferedlineeditwidget.h"
#include <KIconLoader>
#include <KIconEffect>
#include <QAction>
#include <QDebug>

using namespace Akonadi;

PreferedLineEditWidget::PreferedLineEditWidget(QWidget *parent)
    : KLineEdit(parent),
      mPrefered(false)
{
    mIconEnabled = QIcon(QIcon::fromTheme(QStringLiteral("rating")));
    KIconLoader loader;
    QImage iconDisabled =
        mIconEnabled.pixmap(loader.currentSize(KIconLoader::Panel)).toImage();
    KIconEffect::toGray(iconDisabled, 1.0);
    mIconDisabled = QIcon(QPixmap::fromImage(iconDisabled));
    mPreferedAction = addAction(mIconDisabled, QLineEdit::TrailingPosition);
    mPreferedAction->setObjectName(QStringLiteral("preferedaction"));
    connect(mPreferedAction, &QAction::triggered, this, &PreferedLineEditWidget::slotPreferedStatusChanged);
}

PreferedLineEditWidget::~PreferedLineEditWidget()
{

}

void PreferedLineEditWidget::slotPreferedStatusChanged()
{
    mPrefered = !mPrefered;
    updatePreferedIcon();
    Q_EMIT preferedChanged(this);
}

void PreferedLineEditWidget::updatePreferedIcon()
{
    mPreferedAction->setIcon(mPrefered ? mIconEnabled : mIconDisabled);
}

void PreferedLineEditWidget::setPrefered(bool prefered)
{
    if (mPrefered != prefered) {
        mPrefered = prefered;
        updatePreferedIcon();
    }
}

bool PreferedLineEditWidget::prefered() const
{
    return mPrefered;
}
