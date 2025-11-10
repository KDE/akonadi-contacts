/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "businesseditorwidget.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "../widgets/imagewidget.h"
#include "freebusyeditwidget.h"

#include <KContacts/Addressee>

using namespace Akonadi;

BusinessEditorWidget::BusinessEditorWidget(QWidget *parent)
    : QWidget(parent)
    , mOrganizationWidget(new QLineEdit(this))
    , mProfessionWidget(new QLineEdit(this))
    , mTitleWidget(new QLineEdit(this))
    , mDepartmentWidget(new QLineEdit(this))
    , mOfficeWidget(new QLineEdit(this))
    , mManagerWidget(new QLineEdit(this))
    , mAssistantWidget(new QLineEdit(this))
    , mFreeBusyWidget(new Akonadi::FreeBusyEditWidget(this))
    , mLogoWidget(new ImageWidget(ImageWidget::Logo, this))
{
    auto topLayout = new QHBoxLayout(this);

    auto logoLayout = new QVBoxLayout;
    topLayout->addLayout(logoLayout);

    // setup general group box
    logoLayout->addWidget(mLogoWidget, Qt::AlignTop);
    logoLayout->addStretch(0);

    auto generalLayout = new QGridLayout;
    topLayout->addLayout(generalLayout);

    auto label = new QLabel(i18nc("@label The organization of a contact", "Organization:"), this);
    generalLayout->addWidget(label, 0, 0);

    KLineEditEventHandler::catchReturnKey(mOrganizationWidget);
    mOrganizationWidget->setPlaceholderText(i18nc("@info:placeholder", "Add organization's name"));
    label->setBuddy(mOrganizationWidget);
    generalLayout->addWidget(mOrganizationWidget, 1, 0);

    label = new QLabel(i18nc("@label The profession of a contact", "Profession:"), this);
    generalLayout->addWidget(label, 0, 1);

    mProfessionWidget->setPlaceholderText(i18nc("@info:placeholder", "Add profession"));
    KLineEditEventHandler::catchReturnKey(mProfessionWidget);
    label->setBuddy(mProfessionWidget);
    generalLayout->addWidget(mProfessionWidget, 1, 1);

    label = new QLabel(i18nc("@label The title of a contact", "Title:"), this);
    generalLayout->addWidget(label, 3, 0);

    mTitleWidget->setPlaceholderText(i18nc("@info:placeholder", "Add the title"));
    KLineEditEventHandler::catchReturnKey(mTitleWidget);
    label->setBuddy(mTitleWidget);
    generalLayout->addWidget(mTitleWidget, 4, 0);

    label = new QLabel(i18nc("@label The department of a contact", "Department:"), this);
    generalLayout->addWidget(label, 3, 1);

    mDepartmentWidget->setPlaceholderText(i18nc("@info:placeholder", "Add the department"));
    KLineEditEventHandler::catchReturnKey(mDepartmentWidget);
    label->setBuddy(mDepartmentWidget);
    generalLayout->addWidget(mDepartmentWidget, 4, 1);

    label = new QLabel(i18nc("@label The office of a contact", "Office:"), this);
    generalLayout->addWidget(label, 5, 0);

    KLineEditEventHandler::catchReturnKey(mOfficeWidget);
    mOfficeWidget->setPlaceholderText(i18nc("@info:placeholder", "Add the office"));

    label->setBuddy(mOfficeWidget);
    generalLayout->addWidget(mOfficeWidget, 6, 0);

    label = new QLabel(i18nc("@label The manager's name of a contact", "Manager's name:"), this);
    generalLayout->addWidget(label, 5, 1);

    mManagerWidget->setPlaceholderText(i18nc("@info:placeholder", "Add manager's name"));
    KLineEditEventHandler::catchReturnKey(mManagerWidget);
    label->setBuddy(mManagerWidget);
    generalLayout->addWidget(mManagerWidget, 6, 1);

    label = new QLabel(i18nc("@label The assistant's name of a contact", "Assistant's name:"), this);
    generalLayout->addWidget(label, 7, 0);

    mAssistantWidget->setPlaceholderText(i18nc("@info:placeholder", "Add assistant's name"));
    KLineEditEventHandler::catchReturnKey(mAssistantWidget);
    label->setBuddy(mAssistantWidget);
    generalLayout->addWidget(mAssistantWidget, 8, 0);

    // setup groupware group box
    label = new QLabel(i18nc("@label The free/busy information of a contact", "Free/Busy:"));
    generalLayout->addWidget(label, 7, 1);

    label->setBuddy(mFreeBusyWidget);
    generalLayout->addWidget(mFreeBusyWidget, 8, 1);
    generalLayout->setRowStretch(9, 1);
    connect(mOrganizationWidget, &QLineEdit::textChanged, this, &BusinessEditorWidget::organizationChanged);
}

BusinessEditorWidget::~BusinessEditorWidget() = default;

void BusinessEditorWidget::loadContact(const KContacts::Addressee &contact)
{
    mLogoWidget->loadContact(contact);
    mOrganizationWidget->setText(contact.organization());
    mProfessionWidget->setText(contact.profession());
    mTitleWidget->setText(contact.title());
    mDepartmentWidget->setText(contact.department());
    mOfficeWidget->setText(contact.office());
    mManagerWidget->setText(contact.managersName());
    mAssistantWidget->setText(contact.assistantsName());

    // groupware group
    mFreeBusyWidget->loadContact(contact);
}

void BusinessEditorWidget::storeContact(KContacts::Addressee &contact)
{
    // general group
    mLogoWidget->storeContact(contact);
    contact.setOrganization(mOrganizationWidget->text());
    contact.setProfession(mProfessionWidget->text().trimmed());
    contact.setTitle(mTitleWidget->text().trimmed());
    contact.setDepartment(mDepartmentWidget->text().trimmed());
    contact.setOffice(mOfficeWidget->text().trimmed());
    contact.setManagersName(mManagerWidget->text().trimmed());
    contact.setAssistantsName(mAssistantWidget->text().trimmed());

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

#include "moc_businesseditorwidget.cpp"
