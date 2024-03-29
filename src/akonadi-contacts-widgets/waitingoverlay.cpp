/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2008 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "waitingoverlay_p.h"

#include <KJob>
#include <KLocalizedString>

#include <QBoxLayout>
#include <QEvent>
#include <QLabel>
#include <QPalette>

//@cond PRIVATE
using namespace Akonadi;
WaitingOverlay::WaitingOverlay(KJob *job, QWidget *baseWidget, QWidget *parent)
    : QWidget(parent ? parent : baseWidget->window())
    , mBaseWidget(baseWidget)
{
    Q_ASSERT(baseWidget);
    Q_ASSERT(parentWidget() != baseWidget);

    connect(baseWidget, &QObject::destroyed, this, &QObject::deleteLater);
    connect(job, &KJob::result, this, &QObject::deleteLater);
    mPreviousState = mBaseWidget->isEnabled();

    QBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->addStretch();
    auto description = new QLabel(this);
    description->setText(i18n("<p style=\"color: white;\"><b>Waiting for operation</b><br/></p>"));
    description->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    topLayout->addWidget(description);
    topLayout->addStretch();

    QPalette p = palette();
    p.setColor(backgroundRole(), QColor(0, 0, 0, 128));
    setPalette(p);
    setAutoFillBackground(true);

    mBaseWidget->installEventFilter(this);

    reposition();
}

WaitingOverlay::~WaitingOverlay()
{
    if (mBaseWidget) {
        mBaseWidget->setEnabled(mPreviousState);
    }
}

void WaitingOverlay::reposition()
{
    if (!mBaseWidget) {
        return;
    }

    // reparent to the current top level widget of the base widget if needed
    // needed eg. in dock widgets
    if (parentWidget() != mBaseWidget->window()) {
        setParent(mBaseWidget->window());
    }

    // follow base widget visibility
    // needed eg. in tab widgets
    if (!mBaseWidget->isVisible()) {
        hide();
        return;
    }
    show();

    // follow position changes
    const QPoint topLevelPos = mBaseWidget->mapTo(window(), QPoint(0, 0));
    const QPoint parentPos = parentWidget()->mapFrom(window(), topLevelPos);
    move(parentPos);

    // follow size changes
    // TODO: hide/scale icon if we don't have enough space
    resize(mBaseWidget->size());
}

bool WaitingOverlay::eventFilter(QObject *object, QEvent *event)
{
    if (object == mBaseWidget
        && (event->type() == QEvent::Move || event->type() == QEvent::Resize || event->type() == QEvent::Show || event->type() == QEvent::Hide
            || event->type() == QEvent::ParentChange)) {
        reposition();
    }
    return QWidget::eventFilter(object, event);
}

//@endcond

#include "moc_waitingoverlay_p.cpp"
