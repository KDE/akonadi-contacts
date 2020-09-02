/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "freebusyeditwidget.h"

#include <kcontacts/addressee.h>
#include <kurlrequester.h>
#include <KConfig>
#include <KLineEdit>
#include <KLocalizedString>
#include <KConfigGroup>
#include <QHBoxLayout>
#include <QStandardPaths>

FreeBusyEditWidget::FreeBusyEditWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    mURL = new KUrlRequester(this);
    mURL->lineEdit()->setTrapReturnKey(true);
    mURL->lineEdit()->setPlaceholderText(i18n("Add FreeBusy"));
    layout->addWidget(mURL);
    setFocusProxy(mURL);
    setFocusPolicy(Qt::StrongFocus);
}

FreeBusyEditWidget::~FreeBusyEditWidget()
{
}

static QString freeBusyUrlStore()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/korganizer/freebusyurls");
}

void FreeBusyEditWidget::loadContact(const KContacts::Addressee &contact)
{
    if (contact.preferredEmail().isEmpty()) {
        return;
    }

    KConfig config(freeBusyUrlStore());
    mURL->setUrl(QUrl(config.group(contact.preferredEmail()).readEntry("url")));
}

void FreeBusyEditWidget::storeContact(KContacts::Addressee &contact) const
{
    if (contact.preferredEmail().isEmpty()) {
        return;
    }

    KConfig config(freeBusyUrlStore());
    config.group(contact.preferredEmail()).writeEntry("url", mURL->url().url());
}

void FreeBusyEditWidget::setReadOnly(bool readOnly)
{
    mURL->setEnabled(!readOnly);
}
