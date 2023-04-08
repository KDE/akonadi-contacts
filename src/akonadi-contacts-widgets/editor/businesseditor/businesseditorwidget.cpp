/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "businesseditorwidget.h"
#include "../utils/utils.h"

#include <KLineEdit>
#include <KLocalizedString>
#include <QGridLayout>
#include <QLabel>

#include "../widgets/imagewidget.h"
#include "freebusyeditwidget.h"

#include <KContacts/Addressee>

using namespace ContactEditor;

BusinessEditorWidget::BusinessEditorWidget(QWidget *parent)
    : QWidget(parent)
    , mOrganizationWidget(new KLineEdit(this))
    , mProfessionWidget(new KLineEdit(this))
    , mTitleWidget(new KLineEdit(this))
    , mDepartmentWidget(new KLineEdit(this))
    , mOfficeWidget(new KLineEdit(this))
    , mManagerWidget(new KLineEdit(this))
    , mAssistantWidget(new KLineEdit(this))
    , mFreeBusyWidget(new FreeBusyEditWidget(this))
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

    mOrganizationWidget->setTrapReturnKey(true);
    mOrganizationWidget->setPlaceholderText(i18n("Add organization's name"));
    label->setBuddy(mOrganizationWidget);
    generalLayout->addWidget(mOrganizationWidget, 1, 0);

    label = new QLabel(i18nc("@label The profession of a contact", "Profession:"), this);
    generalLayout->addWidget(label, 0, 1);

    mProfessionWidget->setPlaceholderText(i18n("Add profession"));
    mProfessionWidget->setTrapReturnKey(true);
    label->setBuddy(mProfessionWidget);
    generalLayout->addWidget(mProfessionWidget, 1, 1);

    label = new QLabel(i18nc("@label The title of a contact", "Title:"), this);
    generalLayout->addWidget(label, 3, 0);

    mTitleWidget->setPlaceholderText(i18n("Add the title"));
    mTitleWidget->setTrapReturnKey(true);
    label->setBuddy(mTitleWidget);
    generalLayout->addWidget(mTitleWidget, 4, 0);

    label = new QLabel(i18nc("@label The department of a contact", "Department:"), this);
    generalLayout->addWidget(label, 3, 1);

    mDepartmentWidget->setPlaceholderText(i18n("Add the department"));
    mDepartmentWidget->setTrapReturnKey(true);
    label->setBuddy(mDepartmentWidget);
    generalLayout->addWidget(mDepartmentWidget, 4, 1);

    label = new QLabel(i18nc("@label The office of a contact", "Office:"), this);
    generalLayout->addWidget(label, 5, 0);

    mOfficeWidget->setTrapReturnKey(true);
    mOfficeWidget->setPlaceholderText(i18n("Add the office"));

    label->setBuddy(mOfficeWidget);
    generalLayout->addWidget(mOfficeWidget, 6, 0);

    label = new QLabel(i18nc("@label The manager's name of a contact", "Manager's name:"), this);
    generalLayout->addWidget(label, 5, 1);

    mManagerWidget->setPlaceholderText(i18n("Add manager's name"));
    mManagerWidget->setTrapReturnKey(true);
    label->setBuddy(mManagerWidget);
    generalLayout->addWidget(mManagerWidget, 6, 1);

    label = new QLabel(i18nc("@label The assistant's name of a contact", "Assistant's name:"), this);
    generalLayout->addWidget(label, 7, 0);

    mAssistantWidget->setPlaceholderText(i18n("Add assistant's name"));
    mAssistantWidget->setTrapReturnKey(true);
    label->setBuddy(mAssistantWidget);
    generalLayout->addWidget(mAssistantWidget, 8, 0);

    // setup groupware group box
    label = new QLabel(i18nc("@label The free/busy information of a contact", "Free/Busy:"));
    generalLayout->addWidget(label, 7, 1);

    label->setBuddy(mFreeBusyWidget);
    generalLayout->addWidget(mFreeBusyWidget, 8, 1);
    generalLayout->setRowStretch(9, 1);
    connect(mOrganizationWidget, &KLineEdit::textChanged, this, &BusinessEditorWidget::organizationChanged);
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
