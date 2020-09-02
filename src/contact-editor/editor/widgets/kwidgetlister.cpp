/*  -*- c++ -*-

  kwidgetlister.cpp

  This file is part of libkdepim.
  SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kwidgetlister_p.h"

#include <QHBoxLayout>

#include <QPushButton>
#include <QVBoxLayout>

#include <assert.h>

class Q_DECL_HIDDEN KWidgetLister::Private
{
public:
    Private(KWidgetLister *qq)
        : q(qq)
    {
    }

    ~Private()
    {
        qDeleteAll(mWidgetList);
        mWidgetList.clear();
    }

    KWidgetLister *const q;
    QVBoxLayout *mLayout = nullptr;
    QWidget *mButtonBox = nullptr;
    QList<QWidget *> mWidgetList;
    int mMinWidgets = 0;
    int mMaxWidgets = 0;
};

KWidgetLister::KWidgetLister(int minWidgets, int maxWidgets, QWidget *parent)
    : QWidget(parent)
    , d(new Private(this))
{
    d->mMinWidgets = qMax(minWidgets, 1);
    d->mMaxWidgets = qMax(maxWidgets, d->mMinWidgets + 1);
    init();
}

KWidgetLister::~KWidgetLister()
{
    delete d;
}

void KWidgetLister::init()
{
    //--------- the button box
    d->mLayout = new QVBoxLayout(this);
    d->mLayout->setContentsMargins(0, 0, 0, 0);
    d->mLayout->setSpacing(4);

    d->mButtonBox = new QWidget(this);
    QHBoxLayout *mButtonBoxHBoxLayout = new QHBoxLayout(d->mButtonBox);
    mButtonBoxHBoxLayout->setContentsMargins(0, 0, 0, 0);
    d->mLayout->addWidget(d->mButtonBox);
    d->mLayout->addStretch(1);
}

void KWidgetLister::slotMore()
{
    // the class should make certain that slotMore can't
    // be called when mMaxWidgets are on screen.
    assert((int)d->mWidgetList.count() < d->mMaxWidgets);

    addWidgetAtEnd();
}

void KWidgetLister::slotFewer()
{
    // the class should make certain that slotFewer can't
    // be called when mMinWidgets are on screen.
    assert((int)d->mWidgetList.count() > d->mMinWidgets);

    removeLastWidget();
}

void KWidgetLister::slotClear()
{
    setNumberOfShownWidgetsTo(d->mMinWidgets);

    // clear remaining widgets
    for (QWidget *widget : qAsConst(d->mWidgetList)) {
        clearWidget(widget);
    }

    Q_EMIT clearWidgets();
}

void KWidgetLister::addWidgetAtEnd(QWidget *widget)
{
    if (!widget) {
        widget = this->createWidget(this);
    }

    d->mLayout->insertWidget(d->mLayout->indexOf(d->mButtonBox), widget);
    d->mWidgetList.append(widget);
    widget->show();
    Q_EMIT widgetAdded();
    Q_EMIT widgetAdded(widget);
}

void KWidgetLister::removeLastWidget()
{
    // The layout will take care that the
    // widget is removed from screen, too.
    delete d->mWidgetList.takeLast();
    Q_EMIT widgetRemoved();
}

void KWidgetLister::clearWidget(QWidget *widget)
{
    Q_UNUSED(widget);
}

QWidget *KWidgetLister::createWidget(QWidget *parent)
{
    return new QWidget(parent);
}

void KWidgetLister::setNumberOfShownWidgetsTo(int aNum)
{
    int superfluousWidgets = qMax((int)d->mWidgetList.count() - aNum, 0);
    int missingWidgets = qMax(aNum - (int)d->mWidgetList.count(), 0);

    // remove superfluous widgets
    for (; superfluousWidgets; superfluousWidgets--) {
        removeLastWidget();
    }

    // add missing widgets
    for (; missingWidgets; missingWidgets--) {
        addWidgetAtEnd();
    }
}

QList<QWidget *> KWidgetLister::widgets() const
{
    return d->mWidgetList;
}

int KWidgetLister::widgetsMinimum() const
{
    return d->mMinWidgets;
}

int KWidgetLister::widgetsMaximum() const
{
    return d->mMaxWidgets;
}

void KWidgetLister::removeWidget(QWidget *widget)
{
    // The layout will take care that the
    // widget is removed from screen, too.

    if (d->mWidgetList.count() <= widgetsMinimum()) {
        return;
    }

    const int index = d->mWidgetList.indexOf(widget);
    QWidget *w = d->mWidgetList.takeAt(index);
    w->deleteLater();
    w = nullptr;
    Q_EMIT widgetRemoved(widget);
    Q_EMIT widgetRemoved();
}

void KWidgetLister::addWidgetAfterThisWidget(QWidget *currentWidget, QWidget *widget)
{
    if (!widget) {
        widget = this->createWidget(this);
    }

    int index = d->mLayout->indexOf(currentWidget ? currentWidget : d->mButtonBox) + 1;
    d->mLayout->insertWidget(index, widget);
    if (currentWidget) {
        index = d->mWidgetList.indexOf(currentWidget);
        d->mWidgetList.insert(index + 1, widget);
    } else {
        d->mWidgetList.append(widget);
    }
    widget->show();

    Q_EMIT widgetAdded();
    Q_EMIT widgetAdded(widget);
}
