/*
    This file is part of Contact Editor.

    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "webselecttypecombobox.h"

#include <KContacts/ResourceLocatorUrl>

#include <KLocalizedString>

using namespace Akonadi;

WebSelectTypeCombobox::WebSelectTypeCombobox(QWidget *parent)
    : Akonadi::ContactEditorComboBox(parent)
{
    addItem(i18n("Select..."), QString());
    addItem(i18n("Home"), (int)KContacts::ResourceLocatorUrl::Home);
    addItem(i18n("Work"), (int)KContacts::ResourceLocatorUrl::Work);
    addItem(i18n("Profile"), (int)KContacts::ResourceLocatorUrl::Profile);
    addItem(i18n("Other"), (int)KContacts::ResourceLocatorUrl::Other);
}

WebSelectTypeCombobox::~WebSelectTypeCombobox() = default;

#include "moc_webselecttypecombobox.cpp"
