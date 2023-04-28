/*
    This file is part of Akonadi Contact.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "contactdefaultactions.h"

#include <QDesktopServices>
#include <QUrl>

using namespace Akonadi;

class Akonadi::ContactDefaultActionsPrivate
{
};

ContactDefaultActions::ContactDefaultActions(QObject *parent)
    : QObject(parent)
    , d(nullptr)
{
}

ContactDefaultActions::~ContactDefaultActions() = default;

void ContactDefaultActions::connectToView(QObject *view)
{
    const QMetaObject *metaObject = view->metaObject();

    if (metaObject->indexOfSignal(QMetaObject::normalizedSignature("urlClicked(const QUrl&)").constData()) != -1) {
        connect(view, SIGNAL(urlClicked(QUrl)), SLOT(showUrl(QUrl)));
    }
}

void ContactDefaultActions::showUrl(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}
