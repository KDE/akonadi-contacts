/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "messagingwidget.h"
#include "../../widgets/contacteditorcombobox.h"
#include "editor/widgets/preferredlineeditwidget.h"

#include <KContacts/Impp>

#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>
#include <QUrl>

using namespace Akonadi;
MessagingWidget::MessagingWidget(QWidget *parent)
    : QWidget(parent)
    , mMessagingEdit(new PreferredLineEditWidget(this))
    , mAddButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
    , mProtocolCombo(new Akonadi::ContactEditorComboBox(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins({});

    mMessagingEdit->setTrapReturnKey(true);
    mMessagingEdit->setPlaceholderText(i18nc("@info:placeholder", "Add an identifier"));
    mMessagingEdit->setObjectName(QLatin1StringView("messaginglineedit"));
    connect(mMessagingEdit, &PreferredLineEditWidget::preferredChanged, this, &MessagingWidget::slotPreferredChanged);
    layout->addWidget(mMessagingEdit);

    mProtocolCombo->setObjectName(QLatin1StringView("protocol"));
    mProtocolCombo->addItem(i18nc("@item:inlistbox select from a list of IM protocols", "Select..."));
    layout->addWidget(mProtocolCombo);

    const auto protocols = KContacts::Impp::serviceTypes();
    for (const QString &protocol : protocols) {
        mProtocolCombo->addItem(QIcon::fromTheme(KContacts::Impp::serviceIcon(protocol)), KContacts::Impp::serviceLabel(protocol), protocol);
    }

    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QLatin1StringView("addbutton"));
    mAddButton->setToolTip(i18nc("@info:tooltip", "Add an IM"));
    connect(mAddButton, &QToolButton::clicked, this, &MessagingWidget::slotAddMessaging);
    layout->addWidget(mAddButton);

    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setObjectName(QLatin1StringView("removebutton"));
    mRemoveButton->setToolTip(i18nc("@info:tooltip", "Remove IM"));
    connect(mRemoveButton, &QToolButton::clicked, this, &MessagingWidget::slotRemoveMessaging);
    layout->addWidget(mRemoveButton);
}

MessagingWidget::~MessagingWidget() = default;

void MessagingWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}

void MessagingWidget::setIMAddress(const KContacts::Impp &address)
{
    const int idx = mProtocolCombo->findData(address.serviceType());
    if (idx >= 0) {
        mProtocolCombo->setCurrentIndex(idx);
    }
    mMessagingEdit->setText(address.address().path());
    mMessagingEdit->setPreferred(address.isPreferred());
}

void MessagingWidget::setPreferred(bool b)
{
    mMessagingEdit->setPreferred(b);
}

KContacts::Impp MessagingWidget::imAddress() const
{
    QUrl uri;
    uri.setScheme(mProtocolCombo->currentData().toString());
    uri.setPath(mMessagingEdit->text().trimmed());
    KContacts::Impp addr;
    addr.setAddress(uri);
    addr.setPreferred(mMessagingEdit->preferred());
    return addr;
}

void MessagingWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

void MessagingWidget::slotAddMessaging()
{
    Q_EMIT addWidget(this);
}

void MessagingWidget::slotRemoveMessaging()
{
    Q_EMIT removeWidget(this);
}

void MessagingWidget::clearWidget()
{
    mProtocolCombo->setCurrentIndex(0);
    mMessagingEdit->clear();
}

void MessagingWidget::setReadOnly(bool readOnly)
{
    mMessagingEdit->setReadOnly(readOnly);
    mAddButton->setEnabled(!readOnly);
    mRemoveButton->setEnabled(!readOnly);
    mProtocolCombo->setEnabled(!readOnly);
}

#include "moc_messagingwidget.cpp"
