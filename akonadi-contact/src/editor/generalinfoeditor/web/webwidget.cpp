/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#include "webwidget.h"
#include <QHBoxLayout>
#include <KLineEdit>
#include <QToolButton>
#include <KLocalizedString>
#include <editor/widgets/akonadicontactcombobox.h>
#include <editor/widgets/preferredlineeditwidget.h>
using namespace Akonadi;

WebWidget::WebWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    mWebSiteEdit = new PreferredLineEditWidget(this);
    mWebSiteEdit->setTrapReturnKey(true);
    mWebSiteEdit->setPlaceholderText(i18n("Add a web site"));
    mWebSiteEdit->setObjectName(QStringLiteral("website"));
    layout->addWidget(mWebSiteEdit);
    connect(mWebSiteEdit, &PreferredLineEditWidget::preferredChanged, this, &WebWidget::slotPreferredChanged);

    mWebType = new Akonadi::AkonadiContactComboBox(this);
    mWebType->setObjectName(QStringLiteral("webtype"));
    mWebType->addItem(i18n("Select..."), QString());
    mWebType->addItem(i18n("Home"), QStringLiteral("home"));
    mWebType->addItem(i18n("Work"), QStringLiteral("work"));
    layout->addWidget(mWebType);

    mAddButton = new QToolButton(this);
    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &WebWidget::slotAddWeb);
    layout->addWidget(mAddButton);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mRemoveButton, &QToolButton::clicked, this, &WebWidget::slotRemoveWeb);
    layout->addWidget(mRemoveButton);
}

WebWidget::~WebWidget()
{

}

void WebWidget::clearWidget()
{
    mWebSiteEdit->clear();
    mWebType->setCurrentIndex(0);
}

void WebWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

void WebWidget::slotAddWeb()
{
    Q_EMIT addWidget(this);
}

void WebWidget::slotRemoveWeb()
{
    Q_EMIT removeWidget(this);
}

void WebWidget::setPreferred(bool b)
{
    mWebSiteEdit->setPreferred(b);
}

void WebWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}
