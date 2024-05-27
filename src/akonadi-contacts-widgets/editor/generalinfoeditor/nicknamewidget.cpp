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
using namespace Akonadi;

NicknameWidget::NicknameWidget(QWidget *parent)
    : QWidget(parent)
    , mNickName(new KLineEdit(this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins({});
    topLayout->setObjectName(QLatin1StringView("mainlayout"));
    auto nickNameLabel = new QLabel(i18nc("@label:textbox", "Nickname"), this);
    nickNameLabel->setObjectName(QLatin1StringView("nicknamelabel"));
    topLayout->addWidget(nickNameLabel);

    mNickName->setTrapReturnKey(true);
    mNickName->setPlaceholderText(i18n("Add a Nickname"));
    mNickName->setObjectName(QLatin1StringView("nickname"));
    topLayout->addWidget(mNickName);
}

NicknameWidget::~NicknameWidget() = default;

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

#include "moc_nicknamewidget.cpp"
