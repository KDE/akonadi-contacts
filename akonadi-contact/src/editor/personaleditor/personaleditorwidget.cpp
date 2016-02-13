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


#include "personaleditorwidget.h"
#include "../utils/utils.h"

#include <KLocalizedString>
#include <KLineEdit>
#include <QGridLayout>
#include <QLabel>

#include <editor/dateeditwidget.h>

#include <KContacts/Addressee>

using namespace Akonadi;

PersonalEditorWidget::PersonalEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout( this );
    QLabel *label = new QLabel( i18nc( "@label The birthdate of a contact", "Birthdate:" ) );
    mainLayout->addWidget( label, 0, 0 );

    mBirthdateWidget = new DateEditWidget( DateEditWidget::Birthday );
    label->setBuddy( mBirthdateWidget );
    mainLayout->addWidget( mBirthdateWidget, 1, 0 );

    label = new QLabel( i18nc( "@label The wedding anniversary of a contact", "Anniversary:" ) );
    mainLayout->addWidget( label, 0, 1 );

    mAnniversaryWidget = new DateEditWidget( DateEditWidget::Anniversary );
    label->setBuddy( mAnniversaryWidget );
    mainLayout->addWidget( mAnniversaryWidget, 1, 1 );

    label = new QLabel( i18nc( "@label The partner's name of a contact", "Partner's name:" ) );
    mainLayout->addWidget( label, 0, 2 );

    mPartnerWidget = new KLineEdit;
    mPartnerWidget->setPlaceholderText(i18n("Add name"));
    mPartnerWidget->setTrapReturnKey(true);
    label->setBuddy( mPartnerWidget );
    mainLayout->addWidget( mPartnerWidget, 1, 2 );
    mainLayout->setColumnStretch( 1, 1 );
    mainLayout->setColumnStretch( 0, 1 );
    mainLayout->setColumnStretch( 2, 1 );

    mainLayout->setRowStretch( 2, 1 );
}

PersonalEditorWidget::~PersonalEditorWidget()
{

}

void PersonalEditorWidget::loadContact(const KContacts::Addressee &contact)
{
    mBirthdateWidget->setDate(contact.birthday().date());
    mAnniversaryWidget->setDate(QDate::fromString(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-Anniversary")),
                                   Qt::ISODate));
    // family group
    mPartnerWidget->setText(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-SpousesName")));
}

void PersonalEditorWidget::storeContact(KContacts::Addressee &contact)
{
    // dates group
    QDateTime birthday = QDateTime(mBirthdateWidget->date(), QTime(), contact.birthday().timeSpec());
    // This is needed because the constructor above sets the time component
    // of the QDateTime to midnight.  We want it to stay invalid.
    birthday.setTime(QTime());

    contact.setBirthday(birthday);
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-Anniversary"), mAnniversaryWidget->date().toString(Qt::ISODate));

    // family group
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-SpousesName"), mPartnerWidget->text().trimmed());
}

void PersonalEditorWidget::setReadOnly(bool readOnly)
{
    // widgets from dates group
    mBirthdateWidget->setReadOnly(readOnly);
    mAnniversaryWidget->setReadOnly(readOnly);

    // widgets from family group
    mPartnerWidget->setReadOnly(readOnly);
}
