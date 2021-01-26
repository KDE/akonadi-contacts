/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "nicknamewidget.h"
#include <KContacts/Addressee>
#include <KLineEdit>
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
using namespace ContactEditor;

NicknameWidget::NicknameWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setObjectName(QStringLiteral("mainlayout"));
    QLabel *nickNameLabel = new QLabel(i18n("Nickname"), this);
    nickNameLabel->setObjectName(QStringLiteral("nicknamelabel"));
    topLayout->addWidget(nickNameLabel);

    mNickName = new KLineEdit(this);
    mNickName->setTrapReturnKey(true);
    mNickName->setPlaceholderText(i18n("Add a Nickname"));
    mNickName->setObjectName(QStringLiteral("nickname"));
    topLayout->addWidget(mNickName);
}

NicknameWidget::~NicknameWidget()
{
}

void NicknameWidget::loadContact(const KContacts::Addressee &contact)
{
    mNickName->setText(contact.nickName());
}

void NicknameWidget::storeContact(KContacts::Addressee &contact) const
{
    contact.setNickName(mNickName->text().trimmed());
}

void NicknameWidget::setReadOnly(bool readOnly)
{
    mNickName->setReadOnly(readOnly);
}
