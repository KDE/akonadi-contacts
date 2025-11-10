/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "webwidget.h"
#include "editor/widgets/preferredlineeditwidget.h"
#include "webselecttypecombobox.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>
#include <QUrl>
using namespace Akonadi;

WebWidget::WebWidget(QWidget *parent)
    : QWidget(parent)
    , mWebSiteEdit(new PreferredLineEditWidget(this))
    , mAddButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
    , mWebType(new Akonadi::WebSelectTypeCombobox(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins({});

    KLineEditEventHandler::catchReturnKey(mWebSiteEdit);

    mWebSiteEdit->setPlaceholderText(i18nc("@info:placeholder", "Add a Web Site"));
    mWebSiteEdit->setObjectName(QLatin1StringView("website"));
    layout->addWidget(mWebSiteEdit);
    connect(mWebSiteEdit, &PreferredLineEditWidget::preferredChanged, this, &WebWidget::slotPreferredChanged);

    mWebType->setObjectName(QLatin1StringView("webtype"));
    layout->addWidget(mWebType);

    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setObjectName(QLatin1StringView("addbutton"));
    mAddButton->setToolTip(i18nc("@info:tooltip", "Add a Web Site"));
    connect(mAddButton, &QToolButton::clicked, this, &WebWidget::slotAddWeb);
    layout->addWidget(mAddButton);

    mRemoveButton->setObjectName(QLatin1StringView("removebutton"));
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setToolTip(i18nc("@info:tooltip", "Remove Web Site"));
    mRemoveButton->setEnabled(false);
    connect(mRemoveButton, &QToolButton::clicked, this, &WebWidget::slotRemoveWeb);
    layout->addWidget(mRemoveButton);
}

WebWidget::~WebWidget() = default;

void WebWidget::clearWidget()
{
    mWebSiteEdit->clear();
    mWebType->setCurrentIndex(0);
}

void WebWidget::updateAddRemoveButton(bool addButtonEnabled, bool removeButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
    mRemoveButton->setEnabled(removeButtonEnabled);
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

KContacts::ResourceLocatorUrl WebWidget::url()
{
    mUrl.setUrl(QUrl(mWebSiteEdit->text().trimmed()));
    mUrl.setPreferred(mWebSiteEdit->preferred());
    mUrl.setType(KContacts::ResourceLocatorUrl::Type(mWebType->currentData().toInt()));
    return mUrl;
}

void WebWidget::loadWebSite(const KContacts::ResourceLocatorUrl &url)
{
    mUrl = url;
    setPreferred(url.isPreferred());
    mWebType->setCurrentIndex(mWebType->findData((int)url.type()));
    mWebSiteEdit->setText(mUrl.url().toDisplayString());
}

void WebWidget::setReadOnly(bool readOnly)
{
    mWebSiteEdit->setReadOnly(readOnly);
    mAddButton->setEnabled(!readOnly);
    mRemoveButton->setEnabled(!readOnly);
    mWebType->setEnabled(!readOnly);
}

void WebWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}

#include "moc_webwidget.cpp"
