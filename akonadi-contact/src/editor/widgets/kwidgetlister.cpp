/*  -*- c++ -*-

  kwidgetlister.cpp

  This file is part of libkdepim.
  Copyright (c) 2001 Marc Mutz <mutz@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  In addition, as a special exception, the copyright holders give
  permission to link the code of this library with any edition of
  the Qt library by Trolltech AS, Norway (or with modified versions
  of Qt that use the same license as Qt), and distribute linked
  combinations including the two.  You must obey the GNU General
  Public License in all respects for all of the code used other than
  Qt.  If you modify this file, you may extend this exception to
  your version of the file, but you are not obligated to do so.  If
  you do not wish to do so, delete this exception statement from
  your version.
*/

#include "kwidgetlister_p.h"

#include <QDialog>
#include <KLocalizedString>
#include <KGuiItem>
#include <QHBoxLayout>

#include <QPushButton>
#include <QVBoxLayout>

#include <assert.h>
#include <KStandardGuiItem>

class Q_DECL_HIDDEN KWidgetLister::Private
{
public:
    Private(KWidgetLister *qq)
        : q(qq),
          mLayout(Q_NULLPTR),
          mButtonBox(Q_NULLPTR),
          mMinWidgets(0),
          mMaxWidgets(0)

    {
    }

    ~Private()
    {
        qDeleteAll(mWidgetList);
        mWidgetList.clear();
    }

    KWidgetLister *q;
    QVBoxLayout *mLayout;
    QWidget *mButtonBox;
    QList<QWidget *> mWidgetList;
    int mMinWidgets;
    int mMaxWidgets;
};


KWidgetLister::KWidgetLister(int minWidgets, int maxWidgets, QWidget *parent)
    : QWidget(parent), d(new Private(this))
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
    d->mLayout->setMargin(0);
    d->mLayout->setSpacing(4);

    d->mButtonBox = new QWidget(this);
    QHBoxLayout *mButtonBoxHBoxLayout = new QHBoxLayout(d->mButtonBox);
    mButtonBoxHBoxLayout->setMargin(0);
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
    foreach (QWidget *widget, d->mWidgetList) {
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
    int missingWidgets     = qMax(aNum - (int)d->mWidgetList.count(), 0);

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

    if (d->mWidgetList.count()  <= widgetsMinimum()) {
        return;
    }

    const int index = d->mWidgetList.indexOf(widget);
    QWidget *w =  d->mWidgetList.takeAt(index);
    w->deleteLater();
    w = Q_NULLPTR;
    Q_EMIT widgetRemoved(widget);
    Q_EMIT widgetRemoved();

}

void KWidgetLister::addWidgetAfterThisWidget(QWidget *currentWidget, QWidget *widget)
{
    if (!widget) {
        widget = this->createWidget(this);
    }

    int index = d->mLayout->indexOf(currentWidget ? currentWidget :  d->mButtonBox) + 1;
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

