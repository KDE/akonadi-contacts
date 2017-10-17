/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

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

#include "addresseslocationwidget.h"
#include "abstractaddresslocationwidget.h"
#include "contacteditor_debug.h"
#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
using namespace ContactEditor;

AddressesLocationWidget::AddressesLocationWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);


    KPluginLoader loader(QStringLiteral("contacteditor/addresslocationeditorplugin"));
    KPluginFactory *factory = loader.factory();
    if (factory) {
        mAbstractAddressLocationWidget = factory->create<ContactEditor::AbstractAddressLocationWidget>();
        mainLayout->addWidget(mAbstractAddressLocationWidget);
    } else {
        qCWarning(CONTACTEDITOR_LOG) << " error during loading contacteditor plugin : " << loader.errorString();
        QLabel *lab = new QLabel(i18n("Missing plugins. Please verify your installation"), this);
        QFont font = lab->font();
        font.setBold(true);
        lab->setFont(font);
        lab->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(lab);
    }
}

AddressesLocationWidget::~AddressesLocationWidget()
{
}

void AddressesLocationWidget::loadContact(const KContacts::Addressee &contact)
{
    if (mAbstractAddressLocationWidget) {
        mAbstractAddressLocationWidget->loadContact(contact);
    }
}

void AddressesLocationWidget::storeContact(KContacts::Addressee &contact) const
{
    if (mAbstractAddressLocationWidget) {
        mAbstractAddressLocationWidget->storeContact(contact);
    }
}

void AddressesLocationWidget::setReadOnly(bool readOnly)
{
    if (mAbstractAddressLocationWidget) {
        mAbstractAddressLocationWidget->setReadOnly(readOnly);
    }
}
