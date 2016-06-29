/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#include "freebusyeditwidget.h"

#include <kcontacts/addressee.h>
#include <kurlrequester.h>
#include <KConfig>
#include <KConfigGroup>
#include <KLineEdit>
#include <KLocalizedString>

#include <QHBoxLayout>
#include <QStandardPaths>

FreeBusyEditWidget::FreeBusyEditWidget(QWidget *parent)
    : QWidget(parent)
    , mReadOnly(false)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    mURL = new KUrlRequester;
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
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + QStringLiteral("korganizer/freebusyurls");
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
