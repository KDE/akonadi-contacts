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

#include "businesseditorwidget.h"
#include "../utils/utils.h"

#include <KLineEdit>
#include <KLocalizedString>
#include <QGridLayout>
#include <QLabel>

#include "freebusyeditwidget.h"
#include <editor/imagewidget.h>

#include <KContacts/Addressee>

using namespace Akonadi;

BusinessEditorWidget::BusinessEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *generalLayout = new QGridLayout( this );
    generalLayout->setMargin(10);
    generalLayout->setSpacing(10);

    // setup general group box
    mLogoWidget = new ImageWidget( ImageWidget::Logo );
    generalLayout->addWidget( mLogoWidget, 0, 0, 9, 1, Qt::AlignTop );

    QLabel *label = new QLabel( i18nc( "@label The organization of a contact", "Organization:" ) );
    generalLayout->addWidget( label, 0, 1 );

    mOrganizationWidget = new KLineEdit;
    mOrganizationWidget->setTrapReturnKey(true);
    mOrganizationWidget->setPlaceholderText(i18n("Add organization's name"));
    label->setBuddy( mOrganizationWidget );
    generalLayout->addWidget( mOrganizationWidget, 1, 1 );

    label = new QLabel( i18nc( "@label The profession of a contact", "Profession:" ) );
    generalLayout->addWidget( label, 0, 2 );

    mProfessionWidget = new KLineEdit;
    mProfessionWidget->setPlaceholderText(i18n("Add profession"));
    mProfessionWidget->setTrapReturnKey(true);
    label->setBuddy( mProfessionWidget );
    generalLayout->addWidget( mProfessionWidget, 1, 2 );

    label = new QLabel( i18nc( "@label The title of a contact", "Title:" ) );
    generalLayout->addWidget( label, 3, 1 );

    mTitleWidget = new KLineEdit;
    mTitleWidget->setPlaceholderText(i18n("Add the title"));
    mTitleWidget->setTrapReturnKey(true);
    label->setBuddy( mTitleWidget );
    generalLayout->addWidget( mTitleWidget , 4, 1 );

    label = new QLabel( i18nc( "@label The department of a contact", "Department:" ) );
    generalLayout->addWidget( label, 3, 2 );

    mDepartmentWidget = new KLineEdit;
    mDepartmentWidget->setPlaceholderText(i18n("Add the department"));
    mDepartmentWidget->setTrapReturnKey(true);
    label->setBuddy( mDepartmentWidget );
    generalLayout->addWidget( mDepartmentWidget, 4, 2 );

    label = new QLabel( i18nc( "@label The office of a contact", "Office:" ) );
    generalLayout->addWidget( label, 5, 1 );

    mOfficeWidget = new KLineEdit;
    mOfficeWidget->setTrapReturnKey(true);
    mOfficeWidget->setPlaceholderText(i18n("Add the office"));

    label->setBuddy( mOfficeWidget );
    generalLayout->addWidget( mOfficeWidget, 6, 1 );

    label = new QLabel( i18nc( "@label The manager's name of a contact", "Manager's name:" ) );
    generalLayout->addWidget( label, 5, 2 );

    mManagerWidget = new KLineEdit;
    mManagerWidget->setPlaceholderText(i18n("Add manager's name"));
    mManagerWidget->setTrapReturnKey(true);
    label->setBuddy( mManagerWidget );
    generalLayout->addWidget( mManagerWidget, 6, 2 );

    label = new QLabel( i18nc( "@label The assistant's name of a contact", "Assistant's name:" ) );
    generalLayout->addWidget( label, 7, 1 );

    mAssistantWidget = new KLineEdit;
    mAssistantWidget->setPlaceholderText(i18n("Add assistant's name"));
    mAssistantWidget->setTrapReturnKey(true);
    label->setBuddy( mAssistantWidget );
    generalLayout->addWidget( mAssistantWidget, 8, 1 );

    // setup groupware group box
    label = new QLabel( i18nc( "@label The free/busy information of a contact", "Free/Busy:" ) );
    generalLayout->addWidget( label, 7, 2 );

    mFreeBusyWidget = new FreeBusyEditWidget;
    label->setBuddy( mFreeBusyWidget );
    generalLayout->addWidget( mFreeBusyWidget, 8, 2 );
    generalLayout->setRowStretch( 9, 1 );
    connect(mOrganizationWidget, &KLineEdit::textChanged, this, &BusinessEditorWidget::organizationChanged);
}

BusinessEditorWidget::~BusinessEditorWidget()
{

}

void BusinessEditorWidget::loadContact(const KContacts::Addressee &contact)
{
    mLogoWidget->loadContact(contact);
    mOrganizationWidget->setText(contact.organization());
    mProfessionWidget->setText(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-Profession")));
    mTitleWidget->setText(contact.title());
    mDepartmentWidget->setText(contact.department());
    mOfficeWidget->setText(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-Office")));
    mManagerWidget->setText(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-ManagersName")));
    mAssistantWidget->setText(Akonadi::Utils::loadCustom(contact, QStringLiteral("X-AssistantsName")));

    // groupware group
    mFreeBusyWidget->loadContact(contact);

}

void BusinessEditorWidget::storeContact(KContacts::Addressee &contact)
{
    // general group
    mLogoWidget->storeContact(contact);
    contact.setOrganization(mOrganizationWidget->text());
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-Profession"), mProfessionWidget->text().trimmed());
    contact.setTitle(mTitleWidget->text().trimmed());
    contact.setDepartment(mDepartmentWidget->text().trimmed());
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-Office"), mOfficeWidget->text().trimmed());
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-ManagersName"), mManagerWidget->text().trimmed());
    Akonadi::Utils::storeCustom(contact, QStringLiteral("X-AssistantsName"), mAssistantWidget->text().trimmed());

    // groupware group
    mFreeBusyWidget->storeContact(contact);
}

void BusinessEditorWidget::setReadOnly(bool readOnly)
{
    mLogoWidget->setReadOnly(readOnly);
    mOrganizationWidget->setReadOnly(readOnly);
    mProfessionWidget->setReadOnly(readOnly);
    mTitleWidget->setReadOnly(readOnly);
    mDepartmentWidget->setReadOnly(readOnly);
    mOfficeWidget->setReadOnly(readOnly);
    mManagerWidget->setReadOnly(readOnly);
    mAssistantWidget->setReadOnly(readOnly);

    // widgets from groupware group
    mFreeBusyWidget->setReadOnly(readOnly);

}
