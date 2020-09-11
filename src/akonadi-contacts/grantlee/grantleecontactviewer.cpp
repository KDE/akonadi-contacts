/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleecontactviewer.h"
#include "KaddressbookGrantlee/GrantleeContactFormatter"
#include <KSharedConfig>

#include <GrantleeTheme/GrantleeThemeManager>

using namespace KAddressBookGrantlee;

GrantleeContactViewer::GrantleeContactViewer(QWidget *parent)
    : Akonadi::ContactViewer(parent)
{
    mFormatter = new KAddressBookGrantlee::GrantleeContactFormatter;
    setContactFormatter(mFormatter);
    mFormatter->setAbsoluteThemePath(kaddressBookAbsoluteThemePath());
}

GrantleeContactViewer::~GrantleeContactViewer()
{
    delete mFormatter;
}

QString GrantleeContactViewer::kaddressBookAbsoluteThemePath()
{
    QString themeName = GrantleeTheme::ThemeManager::configuredThemeName(QStringLiteral("addressbook"));
    if (themeName.isEmpty()) {
        themeName = QStringLiteral("default");
    }
    const QString absolutePath = GrantleeTheme::ThemeManager::pathFromThemes(QStringLiteral("kaddressbook/viewertemplates/"), themeName, QStringLiteral("theme.desktop"));
    return absolutePath;
}

void GrantleeContactViewer::setForceDisableQRCode(bool b)
{
    if (b != mFormatter->forceDisableQRCode()) {
        mFormatter->setForceDisableQRCode(b);
        updateView();
    }
}
